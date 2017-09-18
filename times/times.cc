/**
 * @file
 * @brief  Brief description of file.
 * @author <stefanomunari.sm@gmail.com>
 *
 * Detailed description of file.
 */
#include "times.h"
#include "../src/core/ai.h"
#include "../src/core/io/json_reader.h"
#include "../src/core/search/utils/searchable_type.h"
#include "../src/core/graph/graph_observer.h"
#include <map>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <climits> // UINT_MAX
#include <experimental/filesystem>
#include <iostream>
#include <stdlib.h> // getenv
#include <stdexcept>
#include <fstream> // std::ifstream
#include <typeinfo>

#ifndef MSINT
#define MSINT
typedef long long int64; typedef unsigned long long uint64;
#endif

#ifndef TIMES_FILE
#define TIMES_FILE "/etc/times.conf"
#endif

#ifndef EXP_FS
namespace fs = std::experimental::filesystem;
#endif

static
void WriteResultToFile(
   std::map<path_finder::SearchableType, std::map<std::string, uint64>>
   tot_times,
   std::string file_path)
{
   std::string sep=",";
   std::ofstream file;
   file.open(file_path, std::fstream::out);

   if(!file.good())
      throw std::invalid_argument("WriteResultToFile - error in stream");

   file << "DATA"+sep+"ALGORITHM"+sep+"TIME\n";

   for(auto const & times : tot_times)
   {
      for(auto time_el : times.second)
      {
         file << time_el.first << sep << times.first
         << sep << time_el.second <<"\n";
      }
   }

   file.close();
}

static
const std::string GetFilename(const std::string & dir_path)
{
   std::string file_name = "";
   int max = -1;
   for(auto & p : fs::directory_iterator(dir_path))
   {
      std::string aux = (p.path()).string();
      int first = aux.rfind("/")+1;
      int last = aux.rfind(".");
      if(last-first <= first)
      {
         int i = atoi(aux.substr(first, last-first).c_str());
         if(i > max)
            max = i;
      }
   }
   if(max == -1)
      file_name = dir_path+"0.csv";
   else{
      ++max;
      file_name = dir_path+std::to_string(max)+".csv";
   }

   std::cout << file_name << std::endl;

   return file_name;
}

int main(int argc, char **argv){

   using path_finder::AI;
   using std::map;
   using std::vector;
   using std::string;
   using std::pair;
try
{
   char * c_prefix = getenv(PROJECT_ROOT);

   if(c_prefix == nullptr)
      throw std::invalid_argument("main - environment var not specified");

   /* initialize random seed: */
   srand (time(NULL));
   const string prefix = string(c_prefix);
   string data_path = "";
   std::vector<string> f_name_prefix = std::vector<string>();
   std::vector<string> sources = std::vector<string>();
   std::vector<string> destinations = std::vector<string>();
   string f_extension = "";
   string f_out_prefix = "";

   {
      std::ifstream configuration_stream =
         std::ifstream(prefix+TIMES_FILE, std::ifstream::in);
      string line;
      int par_type_counter = 0;
      while(
         configuration_stream.good()
         &&
         std::getline(configuration_stream, line))
      {

         if(line[0] != '#')// not a commented line
         {
            if(par_type_counter == 1)
               data_path = line;
            if(par_type_counter == 2)
               f_out_prefix = line;
            if(par_type_counter == 3)
               f_extension = line;
            if(par_type_counter == 4)
               f_name_prefix.push_back(line);
            if(par_type_counter == 5)
            {
               int value = atoi(line.c_str());
               int diff = rand()%61;
               sources.push_back(std::to_string(value+diff));
            }
            if(par_type_counter == 6)
            {
               int value = atoi(line.c_str());
               int diff = (rand()%61)-(rand()%17);
               if(value+diff > value+(value/2))
                  diff = 5;
               destinations.push_back(std::to_string(value+diff));
            }
         }else
            ++par_type_counter;
      }

      if(!configuration_stream.eof())
         throw std::invalid_argument(
            "main - configuration stream error : "+line);
      if(data_path.empty() || f_name_prefix.empty() || f_extension.empty())
         throw std::invalid_argument(
            "main - empty arguments from configuration stream");
   }

   const string output_path = prefix+f_out_prefix;

   std::map<path_finder::SearchableType, std::map<string, uint64>> times =
      std::map<path_finder::SearchableType, std::map<string, uint64>>();

   times.insert(
      std::pair<path_finder::SearchableType, std::map<string, uint64>>(
         path_finder::UNIFORM_COST, std::map<string, uint64>()));

   times.insert(
      std::pair<path_finder::SearchableType, std::map<string, uint64>>(
         path_finder::GREEDY, std::map<string, uint64>()));

   times.insert(
      std::pair<path_finder::SearchableType, std::map<string, uint64>>(
         path_finder::ASTAR, std::map<string, uint64>()));

   for(uint i=0; i < f_name_prefix.size(); ++i)
   {
      // read topology and costs graph
      std::map<std::string, std::vector<std::string>> * topology =
         new std::map<std::string, std::vector<std::string>>();
      std::map<std::string, std::vector<uint>> * costs =
         new std::map<std::string, std::vector<uint>>();

      path_finder::JSON_Reader::Read(
         prefix+data_path+f_name_prefix[i]+"-topology"+f_extension,
         topology);

      path_finder::JSON_Reader::Read(
         prefix+data_path+f_name_prefix[i]+"-costs"+f_extension,
         costs);

      // init AIs
      AI ai0 = AI(prefix+data_path, f_name_prefix[i], f_extension);
      AI ai1 = AI(prefix+data_path, f_name_prefix[i], f_extension);
      AI ai2 = AI(prefix+data_path, f_name_prefix[i], f_extension);

      // measure performances
      uint64 time_start = GetTimeMs64();
      auto result0 =
         ai0.FindPath<string>(sources[i], destinations[i],
            path_finder::UNIFORM_COST);
      uint64 time_end = GetTimeMs64();

      // get elapsed time
      uint64 elapsed = time_end - time_start;
      auto time_el = times[path_finder::UNIFORM_COST];
      time_el.insert(std::pair<string, uint64>(f_name_prefix[i],
         uint64(elapsed)));
      times[path_finder::UNIFORM_COST] = time_el;

      // measure performances
      time_start = GetTimeMs64();
      auto result1 =
         ai1.FindPath<string>(sources[i], destinations[i],
            path_finder::GREEDY);
      time_end = GetTimeMs64();

      // get elapsed time
      elapsed = time_end - time_start;
      time_el = times[path_finder::GREEDY];
      time_el.insert(std::pair<string, uint64>(f_name_prefix[i],
         uint64(elapsed)));
      times[path_finder::GREEDY] = time_el;

      // measure performances
      time_start = GetTimeMs64();
      auto result2 =
         ai2.FindPath<string>(sources[i], destinations[i],
            path_finder::ASTAR);
      time_end = GetTimeMs64();

      // get elapsed time
      elapsed = time_end - time_start;
      time_el = times[path_finder::ASTAR];
      time_el.insert(std::pair<string, uint64>(f_name_prefix[i],
         uint64(elapsed)));
      times[path_finder::ASTAR] = time_el;

      // free resources
      delete result0;
      if(result1)
         delete result1;
      delete result2;
      delete topology;
      delete costs;

   }

   WriteResultToFile(times, GetFilename(output_path));

   path_finder::GraphObserver::Instance().Finalize();

   return 0;
}
catch (const std::exception& exc)
{
   std::cerr << exc.what() << std::endl;
}
}
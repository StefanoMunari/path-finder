#include "json_reader.h"
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <fstream>
#include <utility>
#include <stdexcept>

namespace path_finder
{

void
JSON_Reader::Read(const std::string& file_path,
	std::map<std::string, std::vector<std::string>> * result)
{
	Json::Reader reader;
	Json::Value root;
	std::ifstream ifile(file_path);

	if(ifile.good() && reader.parse(ifile, root))
	{
		for(auto it = root.begin(); it != root.end(); ++it)
		{
			Json::Value jvalues = *it;
			std::vector<std::string> values = std::vector<std::string>();
			for(Json::ValueIterator jvit = jvalues.begin();
				jvit != jvalues.end(); ++jvit)
			{
				Json::Value value = *jvit;
				values.push_back(value.asString());
			}
			result->insert(
				std::pair<std::string, std::vector<std::string>>(
					it.key().asString(),values));
		}
	}

	if(!ifile.eof())
		throw std::invalid_argument(
			"JSON_Reader<string> - configuration stream error "+file_path);

	ifile.close();
}

void
JSON_Reader::Read(const std::string& file_path,
	std::map<std::string, std::vector<uint>> * result)
{
	Json::Reader reader;
	Json::Value root;
	std::ifstream ifile(file_path);

	if(ifile.good() && reader.parse(ifile, root))
	{
		for(auto it = root.begin(); it != root.end(); ++it)
		{
			Json::Value jvalues = *it;
			std::vector<uint> values = std::vector<uint>();
			for(Json::ValueIterator jvit = jvalues.begin();
				jvit != jvalues.end(); ++jvit)
			{
				Json::Value value = *jvit;
				values.push_back(value.asUInt());
			}
			result->insert(
				std::pair<std::string, std::vector<uint>>(
					it.key().asString(),values));
		}
	}

	if(!ifile.eof())
		throw std::invalid_argument(
			"JSON_Reader<uint> - configuration stream error "+file_path);

	ifile.close();
}

} // namespace path_finder
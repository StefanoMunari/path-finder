/**
 * @file
 * @brief Reader for JSON files.
 * @author <stefanomunari.sm@gmail.com>
 */
#ifndef JSON_READER_H
#define JSON_READER_H

#include "../utils/types.h"
#include <map>
#include <string>
#include <vector>
#include <jsoncpp/json/value.h>

namespace path_finder
{

class JSON_Reader {
   public:
      static
      void Read(const std::string&,
            std::map<std::string, std::vector<std::string>> *);
      static
      void Read(const std::string&,
            std::map<std::string, std::vector<uint>> *);
};

}
#endif /*JSON_READER_H*/
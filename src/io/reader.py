#!/usr/bin/env python
import json

def get_dictionary_from_file(file_path):
  dictionary = dict();
  file = open(file_path, "r");
  try:
    with file as json_data:
        json_data = json.load(json_data);
        for key in json_data.keys():
          dictionary[key] = list();
          for element in json_data[str(key)]:
            if isinstance(element, int):
              dictionary[key].append(int(element));
            else:
              dictionary[key].append(str(element));
  except Exception as e:
    print(traceback.format_exception(*sys.exc_info()));
  finally:
    file.close();
  return dictionary;
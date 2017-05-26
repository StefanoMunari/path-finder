#!/usr/bin/env python
import json

def get_dictionary_from_file(file_path):
  dictionary = dict();
  with open(file_path) as json_data:
      json_data = json.load(json_data);
      for key in json_data.keys():
        dictionary[key] = list();
        for element in json_data[str(key)]:
        	if isinstance(element, int):
	          dictionary[key].append(int(element));
        	else:
	          dictionary[key].append(element);
  return dictionary;
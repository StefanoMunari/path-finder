#!/usr/bin/env python
import json

def get_dictionary_from_file(file_path):
  dictionary=dict();
  with open(file_path) as json_data:
      json_data = json.load(json_data);
      for i in range(len(json_data.keys())):
        dictionary[i]=list();
        for element in json_data[str(i)]:
          dictionary[i].append(element);
  return dictionary;
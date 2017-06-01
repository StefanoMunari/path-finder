#!/bin/bash
service=${1:-}

if [ ! -f $PWD/docker-compose.$service.yml ]; then
   cp templates/$service.template docker-compose.$service.yml
   while read key_str; do
     if [[ ! ($key_str == *"#"*) ]];
     then
       IFS='='
       read -a key_array <<< "$key_str"
       sed -i "" -e "s~${key_array[0]}~${key_array[1]}~g" docker-compose.$service.yml
     fi
   done <keys.env
fi

docker-compose -p ai_ -f docker-compose.$service.yml build
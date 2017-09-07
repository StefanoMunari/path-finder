#!/bin/bash
service=${1:-}

function help
{
   echo "Usage: "$0" [service]"
   echo "   service :      the name of the service to build (e.g.\"path_finder\")"
   exit
}

if [ -z ${service} ];
then
   help
fi

if [ ! -f $PWD/docker-compose.$service.yml ];
then
	cp templates/$service.template docker-compose.$service.yml
	if [ -z ${PATH_FINDER_ROOT+x} ];
	then
		echo "PATH_FINDER_ROOT environment variable is unset" > /dev/null;
	else
		sed -i "" -e "s~K:PATH_FINDER_ROOT~${PATH_FINDER_ROOT}~g" docker-compose.$service.yml
	fi
fi

docker-compose -p ai_ -f docker-compose.$service.yml up
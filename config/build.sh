#!/bin/bash

service=${1:-}
mode=${2:-}

function help
{
	echo "Usage: "$0" [service] [mode]"
	echo "	service : 		the name of the service to build (e.g.\"path_finder\")"
	echo "	mode 	: 		the mode {\"d\" = dev, \"p\" = production}"
	exit
}

if [ -z ${service} ] || [ -z ${mode} ];
then
	help
fi

if [ -f $PWD/path_finder/Dockerfile ];
then
	rm $PWD/path_finder/Dockerfile
fi

if [ $mode = "d" ];
then
	# remove <PROD_MODE>
	sed -n '/<PROD_MODE>/{p; :a; N; /<\/PROD_MODE>/!ba; s/.*\n//}; p' $PWD/path_finder/Dockerfile.template > $PWD/path_finder/Dockerfile
elif [ $mode = "p" ];
then
	# remove <DEV_MODE>
	sed -n '/<DEV_MODE>/{p; :a; N; /<\/DEV_MODE>/!ba; s/.*\n//}; p' $PWD/path_finder/Dockerfile.template > $PWD/path_finder/Dockerfile
else
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

docker-compose -p ai_ -f docker-compose.$service.yml build
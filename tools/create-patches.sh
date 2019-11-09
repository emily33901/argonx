#!/bin/bash

pushd `dirname $0`
TOOLS_DIR=`pwd`

for directory in ../external/*; do
	if [ -d "${directory}" ]; then
		echo Creating patch for `basename ${directory}`
		
		pushd "${directory}"
			git diff > ${TOOLS_DIR}/patches/`basename ${directory}`.patch
		popd
	fi
done


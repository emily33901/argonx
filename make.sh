#!/bin/bash
# set cwd to script directory
cd "${0%/*}"

pushd `dirname $0`

./create_projects.sh

echo building...
cd premake/
make -j4

echo done.

popd

exit

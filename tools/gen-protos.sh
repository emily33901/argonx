#!/bin/bash

pushd `dirname $0`
TOOLS_DIR=`pwd`
echo "TOOLS_DIR is ${TOOLS_DIR}"
pushd ../external/SteamKit/Resources/Protobufs/steam/

for file in *.proto
do
    echo "${file}"
    protoc -I="." -I=".." -I="../steam" --cpp_out="${TOOLS_DIR}/../protogen/" "${file}"
done

popd
popd
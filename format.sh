#!/bin/bash

pushd `dirname $0`

files="`git ls-files **.hh **.cc`"
clang-format -i -style=file $files

popd

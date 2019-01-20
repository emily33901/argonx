#!/bin/bash

pushd `dirname $0`

for d in ../external/*
do
    echo "${d}"
    echo "$(basename ${d})"
    patchName="patches/$(basename ${d}).patch"
    if [ -a "$patchName" ]; then
        echo "Applying patch for ${d}"
        patchName="$(readlink -f $patchName)"
        echo "$patchName"
        pushd "$d"
        git apply "$patchName"
        popd
    fi

done

popd
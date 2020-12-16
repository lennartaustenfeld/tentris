#!/bin/bash

container_id=$(docker create $1)
docker cp ${container_id}:/tentris_server ./tentris_server
docker cp ${container_id}:/tentris_terminal ./tentris_terminal
docker cp ${container_id}:/rdf2ids ./rdf2ids
docker cp ${container_id}:/ids2hypertrie ./ids2hypertrie
tag=$(echo $GITHUB_REF | rev | cut -d'/' -f1 | rev)
zip benchmarktools_${tag}_clang9_libstdcxx9.zip rdf2ids ids2hypertrie
zip tentris_${tag}_clang9_libstdcxx9.zip tentris_server tentris_terminal

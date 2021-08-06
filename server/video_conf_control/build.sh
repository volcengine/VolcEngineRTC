#!/usr/bin/env bash
RUN_NAME="video_conf_control"

set -e
if [ -d "output" ]; then
  rm -rf output
  mkdir output
fi

if [ "$IS_SYSTEM_TEST_ENV" != "1" ]; then
    go build -o output/bin/${RUN_NAME} ./cmd
else
    go test -c -covermode=set -o output/bin/${RUN_NAME} -coverpkg=./...
fi

mkdir -p output/conf
cp conf/* output/conf
cp script/* output/
chmod +x output/bootstrap.sh


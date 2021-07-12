#!/usr/bin/env bash
RUN_NAME="bytertc.server.vc_control"

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

list="test prod"
for env in $list;
do
mkdir -p output/$env/conf
cp conf/$env/* output/$env/conf
cp script/$env/* output/$env/
chmod +x output/$env/bootstrap.sh
cp -r output/bin output/$env/
done

rm -r output/bin

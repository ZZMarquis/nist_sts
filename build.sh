#!/usr/bin/env bash

curr_path="$( cd "$( dirname "$0" )" && pwd)"
build_dir=${curr_path}/build

if [[ ! -d ${build_dir} ]]; then
  mkdir ${build_dir}
fi

cd ${build_dir}

#测试程序中用到了OPENSSL，根据自己实际情况调整
cmake -DOPENSSL_HOME_PATH=/usr/local/gmssl-g-1.3.0 \
      ..

make -j4
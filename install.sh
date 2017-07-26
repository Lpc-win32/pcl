#-------------------------------------------------
# FileName : install.sh
# Author   : Pengcheng Liu(Lpc-Win32)
# Date     : 2017-07-26
#------------------------------------------------

#!/bin/sh

set -x

cd `dirname $0`

# 使用CMake编译
rm -rf build
mkdir -p build
cd build
cmake ..
make && make install

cd ..
rm -rf build

echo "pcl install ok.."

#########################################################################
# File Name: build.sh
# Author: wnavy
# mail: whjwnavy@163.com
# Created Time: Fri 08 Sep 2017 04:45:25 PM CST
#########################################################################
#!/bin/bash
cd ./build/
#rm -rf *
cmake ..
make
rm -f ../server_qq
rm -f ../client_qq
cp ./qq_server/server_qq ../
cp ./qq_client/client_qq ../


#!/bin/sh
cd xtrautils
make
sudo sh -c "find . -type f ! -name '*.c' | grep -ve "Makefile" | xargs cp -vi --target-directory=/usr/bin/"
cd ..
sudo cp -vi dbghelp/* /usr/include
sudo cp -vi pwnutils/* /usr/bin/
echo "[+] Done"

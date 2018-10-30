echo "script will install binary in deploy folder"

if [ -d build ]; then
	echo "clearing previous build"
	rm -r build
fi

if [ -d deploy ]; then
	echo "removing deploy "
	rm -r deploy
fi

mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../deploy ..
make
make install

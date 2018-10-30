if [ -d build ]; then
	echo "clearing previous build"
	rm -r build
fi

mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../deploy ..
make
make install

rm -rf ./build
mkdir build
cd build
#export EMCC_DEBUG=1
emcmake cmake ../
emmake make

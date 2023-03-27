1、Windows
make-gui .
Configure (Choose for example Visual Studio generator)
Generate Launch the generated project in your favorite IDE and run it.

2、MacOS
mkdir build
cd build
cmake ..
./main

3、Web
  安装emscripten
  mkdir build_emscripten
  cd build_emscripten 
  CC=emcc CXX=em++ cmake ..
  make
  python -m SimpleHTTPServer 8000
  visit http://localhost:8000


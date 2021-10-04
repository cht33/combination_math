if [ ! -d "build" ]; then
  mkdir build
fi
g++ -O2 -o ./build/main main.cpp && ./build/main
if [ ! -d "build" ]; then
  mkdir build
fi
g++ -O3 -o ./build/main main.cpp && ./build/main $1
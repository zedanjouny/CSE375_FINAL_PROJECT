all:
	g++ -std=c++20 src/main.cpp -o main -Iinclude -lchess -Llib -L oneapi-tbb-2021.8.0/lib/intel64/gcc4.8 -ltbb
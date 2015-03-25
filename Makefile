default:
	mkdir -p bin
	g++ -g -std=c++11 src/asqg2afg.cpp src/reader.cpp src/overlap.cpp -o bin/asqg2afg

default:
	mkdir -p bin
	g++ -g -std=c++11 src/asqg2afg.cpp src/asqg/reader.cpp src/amos/overlap.cpp -o bin/asqg2afg

MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

all: run

run:
	g++ -std=c++17 -I"D:/ProgramPack/C++/SFML-2.6.1/include" -I"D:/ProgramPack/C++/boost_1_86_0" *.cpp -L"D:/ProgramPack/C++/SFML-2.6.1/lib" -L"D:/ProgramPack/C++/boost_1_86_0/stage/lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lws2_32 -lboost_system-mgw13-mt-s-x64-1_86 -lboost_filesystem-mgw13-mt-s-x64-1_86 -o newfile
	./newfile.exe

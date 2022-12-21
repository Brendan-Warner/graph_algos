output: graph visualization.o djFunc.o aStar.o gbfs.o breadth_depth.o
	g++ graph visualization.o djFunc.o aStar.o gbfs.o breadth_depth.o -o output

graph visualization.o: graph visualization.cpp
	g++ -std=c++11  -c graph visualization.cpp

djFunc.o: djFunc.cpp djFunc.h
	g++ -std=c++11 -c djFunc.cpp

aStar.o: aStar.cpp aStar.h
	g++ -std=c++11 -c aStar.cpp

gbfs.o: gbfs.cpp gbfs.h
	g++ -std=c++11 -c gbfs.cpp
	
breadth_depth.o: breadth_depth.cpp breadth_depth.h
	g++ -std=c++11 -c breadth_depth.cpp
clean:
	rm -rf *.o output

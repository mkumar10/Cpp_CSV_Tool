all : tool

tool : main.o csvtool.o csvcol.o
	clang++ -std=c++14 -stdlib=libc++ main.o csvtool.o csvcol.o -o tool

main.o : main.cpp CSVTOOL.h CSVCOL.h
	clang++ -std=c++14 -stdlib=libc++ -c main.cpp

csvtool.o : CSVTOOL.cpp CSVCOL.h
	clang++ -std=c++14 -stdlib=libc++ -c CSVTOOL.cpp

csvcol.o : CSVCOL.cpp
	clang++ -std=c++14 -stdlib=libc++ -c CSVCOL.cpp

clean :
	-rm -f *.o tool

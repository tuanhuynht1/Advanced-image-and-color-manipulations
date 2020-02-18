iptools: 
	g++ -std=c++11 -o app iptool.cpp utility.cpp image.cpp statistics.cpp

clean:
	rm -r *.exe *.out *.o
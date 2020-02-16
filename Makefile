
output: send.o receive.o
	#g++ send.o receive.o -o output

send.o: send.cpp
	g++ send.cpp -o send -L/usr/local/Cellar/boost/1.72.0/lib/ -lboost_serialization

receive.o: receive.cpp
	g++ receive.cpp -o receive -L/usr/local/Cellar/boost/1.72.0/lib/ -lboost_serialization

clean:
	rm *.o send receive

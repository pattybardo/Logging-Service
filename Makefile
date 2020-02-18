
output: send.o receive.o
	#g++ send.o receive.o -o output

send.o: send.cpp
	g++ -std=c++17 send.cpp LoggingClient.cpp -o send -L/usr/local/Cellar/boost/1.72.0/lib/ -lboost_serialization

receive.o: receive.cpp
	g++ -std=c++17 receive.cpp Log.cpp -o receive -L/usr/local/Cellar/boost/1.72.0/lib/ -lboost_serialization

clean:
	rm send receive

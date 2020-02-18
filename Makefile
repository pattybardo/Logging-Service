
output: LoggingClient receive.o
	#g++ send.o receive.o -o output

LoggingClient: LoggingClientMain.cpp
	g++ -std=c++17 LoggingClientMain.cpp LoggingClient.cpp -o LoggingClient -L/usr/local/Cellar/boost/1.72.0/lib/ -lboost_serialization

receive.o: receive.cpp
	g++ -std=c++17 receive.cpp LoggingService.cpp Log.cpp -o receive -L/usr/local/Cellar/boost/1.72.0/lib/ -lboost_serialization

clean:
	rm LoggingClient receive

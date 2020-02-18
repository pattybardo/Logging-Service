
output: LoggingClient LoggingService
	#g++ send.o receive.o -o output

LoggingClient: LoggingClientMain.cpp
	g++ -std=c++17 LoggingClientMain.cpp LoggingClient.cpp -o LoggingClient -L/usr/local/Cellar/boost/1.72.0/lib/ -lboost_serialization

LoggingService: LoggingServiceMain.cpp
	g++ -std=c++17 LoggingServiceMain.cpp LoggingService.cpp Log.cpp -o LoggingService -L/usr/local/Cellar/boost/1.72.0/lib/ -lboost_serialization

clean:
	rm LoggingClient LoggingService

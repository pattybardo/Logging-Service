LDIR = /usr/local/Cellar/boost/1.72.0/lib/
CC = g++

LIBS = -lboost_serialization

output: LoggingClient LoggingService UnitTest
	#g++ send.o receive.o -o output

LoggingClient: LoggingClientMain.cpp
	$(CC) -std=c++17 LoggingClientMain.cpp LoggingClient.cpp -o LoggingClient -L$(LDIR) $(LIBS)

LoggingService: LoggingServiceMain.cpp
	$(CC) -std=c++17 LoggingServiceMain.cpp LoggingService.cpp Log.cpp -o LoggingService -L$(LDIR) $(LIBS)

UnitTest: UnitTestLoggingService.cpp LoggingClient.cpp LoggingService.cpp
	$(CC) -std=c++17 UnitTest.cpp UnitTestLoggingService.cpp LoggingClient.cpp LoggingService.cpp Log.cpp -o UnitTest -L$(LDIR) $(LIBS)

clean:
	rm LoggingClient LoggingService UnitTest

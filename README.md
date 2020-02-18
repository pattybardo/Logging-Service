# Logging-Service
North Logging Service Challenge

## Build Instructions

After cloning this repository, it is important to have the boost C++ library installed. I did this using "brew install boost". Once this is installed, it is important to alter the Makefile. Replace the LDIR property with the location of the boost library. For reference, mine was installed in /usr/local/Cellar/boost/1.72.0/lib/.

This was compiled with g++ , Apple clang version 11.0.0 (clang-1100.0.33.17)

Once this is done, make can be run in terminal in the directory of this repo. This will generate 3 executables. LoggingService, LoggingClient, and UnitTest.

LoggingService must be executed first, and takes no arguments.

LoggingClient can be executed many times (multiple clients concurrently), and can take either 1 or no command line arguments. The command line argument is a .txt file that is formatted properly that has pre-written requests. More on this later. If no file is passed, the user will be prompted to input requests from stdin.

UnitTest can be executed to run the unit tests. Useful arguments include --reporter compact, and --success.

<code> make </code>

<code> ./LoggingService </code>

<code> ./LoggingClient test.txt </code>

<code> ./UnitTest --reporter compact --success </code>

It is important to note that the requests (log, dump, and clear) are requested as 0, 1, and 2. The log level is also designated as 0, 1, and 2 (info, warning, and error). This is important if you would like to alter test.txt to generate your own test cases, and when inputting into stdin for LoggingClient.

The test.txt file contains lines of request properties. Log requests take 4 lines, dump requests take 2 lines, clear requests take 1 line.

Log:<br>
1. Action = 0. If you would like to input a log, the first line is 0.
2. ClientID. This is a string that you can input to identify the client.
3. LogLevel = 0, 1, or 2. Corrresponds to info, warning, or error.
4. Message. This is a string with the log message.

Dump:<br>
1. Action = 1. If you would like to input a dump request, the first line is 1.
2. LogLevel = 0, 1, or 2. This is the minimum log level that will be dumped to stdout on the service side. (1 will show all warnings and errors)

Clear: <br>
1. Action = 2. If you would like to input a clear request, the first line is 2.

Currently the LoggingService runs indefinitely until it receives a log request with a message that is "exit()". This will terminate the program. Therefore you will see in the test.txt file the final request is:<br>

<code> 0 </code><br>
<code> Patrick </code><br>
<code> 0 </code><br>
<code> exit() </code><br>

If you would like to continue testing using the client and server, or run the test.txt with multiple clients, I suggest removing these last four lines.



## Assumptions

The first assumption is that there will be no incorrect inputs. Input error handling was not done for the sake of brevity.

Another assumption is that memory is not limited.

## Background

The methods I had considered for communication between the processes were shared memory, sockets, and a message queue. Socketting did not make sense for this challenge since I assumed that this is an interprocess problem occurring on the same machine. Since concurrent access to the service was highlighted in the requirements, I chose to use a message queue.

The drawbacks of the message queue are that there is more overhead than the shared memory, therefore the cost of memory usage may outweigh handling thread-safety for certain applications. Another drawback of the message queue is that the service receiving the message does not know beforehand what the message will be. This application has 3 different types of requests, and therefore a data structure that can encompass all three request types was used. This is inefficient because unnecessary memory is allocated for certain requests.

## Limitations

The message queue takes a maximum number of messages and a max message size. Therefore there is a limit on how large the messages can be, but this can be altered in the Request.hpp file. The amount of messages in the queue can also be changed.

## Next Steps

Given more time, here are a few things I would like to change.

1. I believe it is possible to send an integer and void pointer as a request across the message queue instead of a general structure. This void pointer can then be recast to the appropriate request data type on the receiving end depending on the value of the integer.

2. I would incorporate the writing to filesystem in the LoggingServiceMain.cpp. This would be done whenever a log request is sent, and the new log object is created. The information could then be appended to an output file using fstream so that the informaton persists past the lifetime of the service.

3. This is where I figured a bit too late the message queue may not be the best design choice if each client wanted the logs to be dumped back to them. Only when I started to really consider the bonus did I realize this, and it is because if the LoggingService is using a message queue to communicate with many concurrent clients, who the dump is for cannot be determined until after the message is taken from the queue. Therefore if the dump does not belong to them (they are still waiting for their dump request) they would have to requeue the message, and this seems highly inefficient. I may implement a shared memory block for returning the dump back to the users.

4. The dumpLogs function is currently not being unit tested and that is just because I am pressed for time to change it. What I would do is change the function definition to take a parameter for what stream to output to. The current issue is the function is dumping the logs to stdout, but for unit testing I would want that output to return to some stream that I can compare.

5. There is a lot of duplicated code on the client side (handling input from stdin vs handling input from a text file) and so I would like to consolidate this as much as possible.

6. Comment the code more.


## Overview

Log Client : DONE<br>
Log Service : DONE<br>
Unit Testing : DONE<br>
Circular Buffer : DONE<br>
Persistent logs : INCOMPLETE (for now)<br>
Dumps returned to client : INCOMPLETE (for now)<br>

If there are any questions at all about anything pertaining to this challenge, please feel free to ask. I have put a lot of time an effort into this, and I know I have probably left some information out.

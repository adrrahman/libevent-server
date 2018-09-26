make:
	g++ src/single_thread.cpp -o server -Wall -levent -levent_core -std=c++11

pre:
	g++ src/prethread.cpp -o pre_server -Wall -levent -levent_core -std=c++11 -pthread

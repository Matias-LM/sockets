g++ -std=c++11 -pthread -o Client echo_client_inet.c
g++ -std=c++11 -pthread -o servers/Server servers/echo_server_inet.c

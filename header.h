#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#define SOCK_PATH       "mi_socket"
#define MENSAJE_MAXIMO  1024
#define MAX_CLIENTS 10
#define BUF_SIZE 4096
#define MAX_COMMAND 20

#ifndef TRANSFER_FILE_TRANSFER_H
#define TRANSFER_FILE_TRANSFER_H

#define MAX_LINE 4096
#define LINSTENPORT 7788
#define SERVERPORT 8877
#define BUFFSIZE 4096

#endif //TRANSFER_FILE_TRANSFER_H

using namespace std;
int leer_de_socket(int s, char buf[]);
vector<string> split(const string& str, const string& delim);
void get_file(int s, const char *name, char buf[], const string& output_path);
void send_file(int s, const char *name, char buf[]);
struct Client {

    /* COMPLETAR */
};
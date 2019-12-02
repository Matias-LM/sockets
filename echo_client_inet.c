#include "header.h"

#define PORT 4000

ssize_t total=0;
FILE *fp;

void sendfile(char str[], int s) {

    int n; 
    char sendline[BUF_SIZE] = {0}; 
    str[strlen(str) - 1] = '\0';
    const char *filename = basename(str+2); 
    if (filename == NULL){

        perror("Can't get filename");
        return;

    }

    char buff[BUF_SIZE] = {0};
    strncpy(buff, filename, strlen(filename));
    if (send(s, buff, BUF_SIZE, 0) == -1){

        perror("Can't send filename");
        return;

    }

    fp = fopen(filename, "rb");
    if (fp == NULL) {

        perror("Can't open file");
        return;

    }

    n = recv(s, str, MENSAJE_MAXIMO, 0);
    if (n == 0) 
        return;
    if (n < 0) { 
        perror("recibiendo");
        return;
    }
    str[n] = '\0';

    while ((n = fread(sendline, sizeof(char), BUF_SIZE, fp)) > 0) {

	    total+=n;
        if (n != BUF_SIZE && ferror(fp))
        {
            perror("Read File Error");
            return;
        }
        
        if (send(s, sendline, n, 0) == -1)
        {
            perror("Can't send file");
            return;
        }
        memset(sendline, 0, BUF_SIZE);

    }
    exit(0);

}

int main(void){

    //Pruebo
    int socket_fd;
    int len;
    struct sockaddr_in  remote;
    struct hostent *hp;
    struct in_addr addr;
    char buf[MENSAJE_MAXIMO];

    /* Crear un socket de tipo UNIX con SOCK_STREAM */
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("creando socket");
        exit(1);
    }

    /* Establecer la dirección a la cual conectarse. */
    remote.sin_family = AF_INET;
    remote.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &(remote.sin_addr));

    /* Conectarse. */
    if (connect(socket_fd, (struct sockaddr *)&remote, sizeof(remote)) == -1) {
        perror("conectandose");
        exit(1);
    }
    
    do{

        printf("> ");
        fgets(buf, MENSAJE_MAXIMO, stdin);
        if (send(socket_fd, buf, strlen(buf), 0) == -1) {
            perror("enviando");
            exit(1);
        }
        if(buf[0] == '/'){

            if(fork() == 0) sendfile(buf, socket_fd);

        }

    }while(!feof(stdin));

    /* Cerrar el socket. */
    close(socket_fd);

    return 0;

}

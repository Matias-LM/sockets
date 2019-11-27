#include "header.h"

#define PORT 4000

int main(void)
{

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

    printf("a");
    cout<< "alto";
    /* Conectarse. */
    if (connect(socket_fd, (struct sockaddr *)&remote, sizeof(remote)) == -1) {
        perror("conectandose");
        exit(1);
    }
    cout << "alto";
    do{

        printf("> ");
        fgets(buf, MENSAJE_MAXIMO, stdin);
        if (send(socket_fd, buf, strlen(buf), 0) == -1) {
            perror("enviando");
            exit(1);
        }

    }while(!feof(stdin));

    /* Cerrar el socket. */
    close(socket_fd);

    return 0;

}

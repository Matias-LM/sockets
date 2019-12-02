#include "../header.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <wait.h>

#define MAX_MSG_LENGTH 1024
#define PORT 4004

char *aux;
ssize_t total=0;
struct sockaddr_in local;

void writefile(int sockfd, FILE *fp){

    ssize_t n;
    char buff[BUF_SIZE] = {0};
    while ((n = recv(sockfd, buff, BUF_SIZE, 0)) > 0) {

        if(buff == "complete") return;
	    total+=n;
        if (n == -1){

            perror("Receive File Error");
            return;

        }    
        if (fwrite(buff, sizeof(char), n, fp) != n){

            perror("Write File Error");
            return;

        } 
        memset(buff, 0, BUF_SIZE);

    }

}

void recibirArchivos(char arg[], int s){

    if (send(s, "sendOk", strlen("sendOk"), 0) == -1) {
        perror("enviando");
        return;
    }
    
    char filename[BUF_SIZE] = {0}; 
    if (recv(s, filename, BUF_SIZE, 0) == -1) 
    {
        perror("Can't receive filename");
        return;
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) 
    {
        perror("Can't open file");
        return;
    }
    
    char addr[INET_ADDRSTRLEN];
    printf("Start receive file: %s from %s\n", filename, inet_ntop(AF_INET, &local.sin_addr, addr, INET_ADDRSTRLEN));
    writefile(s, fp);
    printf("Receive Success, NumBytes = %ld\n", total);
    fclose(fp);
    
}


int leer_de_socket(char str[], int s) {

    int n;
    char aux2[MAX_MSG_LENGTH];
    n = recv(s, str, MENSAJE_MAXIMO, 0);
    if (n == 0) 
        return -1;
    if (n < 0) { 
        perror("recibiendo");
        exit(1);
    }
    str[n] = '\0';
    if(str[0] == '|'){

        system(str+2);           

    }else if (str[0] == '/') {

        recibirArchivos(str+2, s);

    }else printf("recibi: %s\n", str);
    return 0;

}

int main(void)
{
    int s, s1, t, len;
    struct sockaddr_in remote;
    char str[MENSAJE_MAXIMO];
    int n;

	/* Crear un socket de tipo PF_INET  con TCP (SOCK_STREAM). */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("creando socket");
        exit(1);
    }

	/* Definimos el puerto donde escuchar y el dominio, ahora AF_INET en lugar de UNIX_DOMAIN */

    local.sin_family = AF_INET;
    local.sin_port = htons(PORT);

    /* INADDR_ANY es una constante que permitira asignarle, como direccion, "multiples" direcciones.
       Esto se hace para que al hacer el bin, el servidor escuche, por ejemplo, en loopback (ej:127.0.0.1) y ethernet(ej 192.168.1.30) */
    local.sin_addr.s_addr = INADDR_ANY;

    /* Establecer la dirección a la cual conectarse para escuchar (especificada en el struct local) */
    if (bind(s, (struct sockaddr *)&local, sizeof(local)) < 0) {
        perror("haciendo bind");
        exit(1);
    }

	/* Escuchar en el socket y permitir 5 conexiones en espera. */
    if (listen(s, 5) == -1) {
        perror("escuchando");
        exit(1);
    }

    while(1) {

        /* Aceptar una conexión entrante. */
        t = sizeof(local);

        /* Los parametros que son NULL pueden cambiarse para obtener informacion de la direccion del cliente que se conectó */
        if ((s1 = accept(s,NULL, NULL)) == -1) {
            perror("aceptando la conexión entrante");
            exit(1);
        }
        int pid = fork();
        if(pid == 0){

            /* Mostrar en pantalla todo lo que recibimos. */
            while(1) {
                
                if(leer_de_socket(str,s1) == -1)
                    break;
            }

        }

    }

	/* Cerrar la conexión entrante. */
    close(s1);

	/* Cerrar la conexión que escucha. */
	close(s);
	
    return 0;
}



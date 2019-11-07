#include "header.h" 

/* Lee un mensaje del socket s y lo guarda en buf. Tener en cuenta que posiblemente sea necesario
   agregar el caracter de terminacion */
   
int leer_de_socket(int s, char buf[]) {
    /* COMPLETAR */
}

/* Dado un string y un delimitador como " ", devuelve un vector de strings donde los elementos son los tokens que
   resultan de la separación segun el delimitador. */

vector<string> split(const string& str, const string& delim)
{
     /* COMPLETAR */
}


/* Dado un socket, un nombre archivo y un buffer de tamano 4096 bytes, envia dicho archivo a traves del socket
   en bloques de 4096 bytes */

void send_file(int s, const char *name,  char buf[]){
    /* COMPLETAR */
}

/* Dado un socket, un nombre archivo y un buffer de tamano 4096 bytes, recibe dicho archivo a traves del socket
   en bloques de 4096 bytes y lo guarda en el output_path especificado con el nombre de name */

void get_file(int s, const char *name, char buf[], const string& output_path){
    /* COMPLETAR */
}
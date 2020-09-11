/*
 * Cliente con Transmission Control Protocol (TCP).
 * Fecha 28/09/2014
 * Lizandro Jose Ramirez Difo
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
 
#define SERVER_PORT 9999
#define BUFFER_LEN 1024
#define IP_SERVER "138.100.154.59" /*"138.100.154.34"8*/
/*138.100.154.59:9999*/

int main(int argc, char *argv[])
{
 
 int sockfd; /* descriptor a usar con el socket */
 struct sockaddr_in their_addr; /* almacenara la direccion IP y numero de puerto del servidor */
 struct hostent *he; /* para obtener nombre del host */
 int numbytes; /* conteo de bytes a escribir */
 char buf[BUFFER_LEN]; /* Buffer de recepción */	
 int addr_len;

if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	 perror("socket");
	 exit(1);
 }

/*htons me blinda la direccion para que no importe el tipo de maquina que use, agrega formato canonico*/
their_addr.sin_family = AF_INET; /* usa host byte order */
their_addr.sin_port = htons(SERVER_PORT); /* usa network byte order */
their_addr.sin_addr.s_addr= inet_addr(IP_SERVER);/**((struct in_addr *)he->h_addr);*/
 
 /*bzero(&(their_addr.sin_zero), 8); /* pone en cero el resto */
connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
/*connect devuelve -1 si no se ha conectado a nadad*/
write (sockfd,argv[1],strlen(argv[1]));
/*write me envia todo junto por una coneccion, osea si hago dos write con dos mensajes,
a quien lo envio lo vera como un solo mensaje, tengo que programar las barreras*/

int tot=strlen(argv[1]);
int n=0;
int rec;
/*una solucion para recibir y buscar sin saber el tamano, es leer de uno en uno*/
while(n<tot)
{
	printf("Esperando respuesta del servidor... \n");
	rec=read(sockfd,buf+n,tot-n);
	n+=rec;
}

buf[rec]='\0';
printf("recibido: %s\n",buf);
close(sockfd);
}

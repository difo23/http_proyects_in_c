/*
 * Cliente con datagramas (UDP).
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
 
#define SERVER_PORT 4525
#define BUFFER_LEN 1024
#define IP_SERVER "127.0.0.1"

 /* Direccion IP del Server 138.100.154.*/
 
int main(int argc, char *argv[])
{
 
 int sockfd; /* descriptor a usar con el socket */
 struct sockaddr_in their_addr; /* almacenara la direccion IP y numero de puerto del servidor */
 struct hostent *he; /* para obtener nombre del host */
 int numbytes; /* conteo de bytes a escribir */
 char buf[BUFFER_LEN]; /* Buffer de recepción */	
 int addr_len;

 /*if (argc != 3) {
 fprintf(stderr,"uso: cliente hostname mensaje\n");
 exit(1);
 }*/
 
 /* convertimos el hostname a su direccion IP */
 /*if ((he=gethostbyname(argv[1])) == NULL) {
 herror("gethostbyname");
 exit(1);
 }*/
 
 /* Creamos el socket */
 if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
 perror("socket");
 exit(1);
 }
 
 /* a donde mandar */
 their_addr.sin_family = AF_INET; /* usa host byte order */
 their_addr.sin_port = htons(SERVER_PORT); /* usa network byte order */
 their_addr.sin_addr.s_addr= inet_addr(IP_SERVER);/**((struct in_addr *)he->h_addr);*/
 
 /*bzero(&(their_addr.sin_zero), 8); /* pone en cero el resto */
 
 /* enviamos el mensaje */
 if ((numbytes=sendto(sockfd,argv[1],strlen(argv[1]),0,(struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) 
 {
 perror("sendto");
 exit(1);
 }

 printf("enviados %d bytes hacia %s\n",numbytes,inet_ntoa(their_addr.sin_addr));

 printf("Esperando datos ....\n");
 if ((numbytes=recvfrom(sockfd, buf, BUFFER_LEN, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
     perror("recvfrom");
     exit(1);
    }

 printf("paquete proveniente de : %s\n",inet_ntoa(their_addr.sin_addr));
 printf("longitud del paquete en bytes : %d\n",numbytes);
 buf[numbytes] = '\0';
 printf("el paquete contiene : %s\n", buf);
 /* cierro socket */
 close(sockfd);
 
 return 0;
}
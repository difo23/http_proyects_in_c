/*
 * Cliente con HiperText Transfer Protocol (HTTP).
 * Fecha 18/10/2014
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
#define BUFFER_LEN 200
#define IP_SERVER "127.0.0.1" /*"138.100.154.9" /*"154.9/138.100.154.34"8*/
/*138.100.154.59:9999*/
#define STRING_SEND 6



 void readlinehttp(int sockfd) /* Función donde se ejecuta la lógica del programa */
	{

	printf("Esperando respuesta del servidor... \n");	
	int rec=0;
	char bufrc[BUFFER_LEN];
	int x=0;
	printf("Recibo el head del servidor: \n\n");

		while(x==0)
			{
				if(rec=read(sockfd,bufrc,1)==0)
				{
					printf("\n\nNo recibo nada Me salgo!\n");
				 	x=1;
				}

				if(bufrc[rec]=='\n')
				{
					printf("\n");

					if(rec=read(sockfd,bufrc,1)==0)
						{
							printf("\nNo recibo nada Me salgo!\n");
						 	x=1;
						}
					if(bufrc[rec]=='\n')
						{
							printf("\nContinuo con el <body> de la pagina: \n");	
						}
				}
				
		 		bufrc[rec+1]='\0';
				printf("%s",bufrc);
			}
	return; /* sale de la función */
}
 
 int main(int argc, char *argv[])
{
 
 int sockfd; /* descriptor a usar con el socket */
 struct sockaddr_in their_addr; /* almacenara la direccion IP y numero de puerto del servidor */
 struct hostent *he; /* para obtener nombre del host */
 int numbytes; /* conteo de bytes a escribir */
 char buf[BUFFER_LEN]; /* Buffer de recepción */	
 int addr_len;

/*Crea Head solicitando pagina HTML en el servirdor*/
/*
Se envian 7 string
"GET /index.html HTTP/1.0\n"
"User-agent: Mozilla/4.75 [en] (Win98; U)\n"
"Host: www.eui.upm.es\n"
"Accept: text/html, image/gif, image/jpeg\n"
"Accept language:\n"
"Accept-language: en\n"
"\n"
*/
const char *bufstr[STRING_SEND];
bufstr[0]="GET /index.html HTTP/1.0\r\n";
bufstr[1]="User-agent: Mozilla/4.75 [en] (Win98; U)\r\n";
bufstr[2]="Host: www.eui.upm.es\r\n";
bufstr[3]="Accept: text/html, image/gif, image/jpeg\r\n";
bufstr[4]="Accept-language: en\r\n";
bufstr[5]="\r\n";


if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	 perror("socket");
	 exit(1);
 }

/*htons me blinda la dirrecion para que no importe el tipo de maquina que use, agrega formato canonico*/
their_addr.sin_family = AF_INET; /* usa host byte order */
their_addr.sin_port = htons(SERVER_PORT); /* usa network byte order */
their_addr.sin_addr.s_addr= inet_addr(IP_SERVER);/**((struct in_addr *)he->h_addr);*/
 
 /*bzero(&(their_addr.sin_zero), 8); /* pone en cero el resto */

	connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));

	int i;
	for(i=0;i<STRING_SEND;++i)
	{
		//CODIGO A EJECUTAR
		/*connect devuelve -1 si no se ha conectado a nadad*/

		strcpy(buf,bufstr[i]);

		if(write (sockfd,buf,strlen(buf))==-1)
		{
			printf("No escribe\n");
		}


		/*write me envia todo junto por una coneccion, osea si hago dos write con dos mensajes,
		a quien lo envio lo vera como un solo mensaje, tengo que programar las barreras*/
	}

		printf("Salgo del envio....\n");	
		readlinehttp(sockfd);



close(sockfd);
/*(int tot=BUFFER_LEN;
int n=0;
int rec;
/*una solucion para recibir y buscar sin saber el tamano, es leer de uno en uno*/



}



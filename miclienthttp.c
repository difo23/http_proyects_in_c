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
 
#define SERVER_PORT 80
#define BUFFER_LEN 200
#define IP_SERVER "138.100.154.9" /*"154.9/138.100.154.34"8*/
/*138.100.154.59:9999*/
#define STRING_SEND 5
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
bufstr[0]="GET /index.html HTTP/1.0\n";
bufstr[1]="User-agent: Mozilla/4.75 [en] (Win98; U)\n";
bufstr[2]="Host: www.eui.upm.es\n";
bufstr[3]="Accept: text/html, image/gif, image/jpeg\n";
bufstr[4]="Accept-language: en\n\n";


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
printf("i tiene el valor: %d\n",i);
strcpy(buf,bufstr[i]);
printf("esto es bufstr: %s\n",bufstr[i]);
printf("esto es buf: %s\n",buf);
if(write (sockfd,buf,strlen(buf))==-1)
{
	printf("No escribe\n");
}
printf("si escribe\n");

/*write me envia todo junto por una coneccion, osea si hago dos write con dos mensajes,
a quien lo envio lo vera como un solo mensaje, tengo que programar las barreras*/
}

printf("Salgo del envio\n");



/*(int tot=BUFFER_LEN;
int n=0;
int rec;
/*una solucion para recibir y buscar sin saber el tamano, es leer de uno en uno*/



int rec=0;
char bufrc[BUFFER_LEN];

for(i=0;i<=BUFFER_LEN;++i)
	{
		rec=read(sockfd,buf,2);
		bufrc[i]=buf[rec]='\0';
		if(bufrc[i]=='\n')
		{
			bufrc[i+1]='\0';
			printf("recibido bufrc: %s\n",bufrc);
		    i=0;
		}	

		printf("recibido buf: %s\n",buf);
			
	}	


close(sockfd);

}



void readlinehttp(void) /* Función donde se ejecuta la lógica del programa */
{

printf("Esperando respuesta del servidor... \n");
	

		
	return; /* sale de la función */
}
 

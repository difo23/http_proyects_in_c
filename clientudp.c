#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdio.h>


struct sockaddr_in dirServ;

char mensajeEnv[100];
char mensajeRec[200];

int rec;
int s;
socklen_t  sin_size;  

main (int argc, char *argv[])
{

		s=socket(AF_INET, SOCK_DGRAM, 0);

		dirServ.sin_family= AF_INET;
		dirServ.sin_addr.s_addr= inet_addr("127.0.0.1");
		dirServ.sin_port= htons(7); /* servidor de echo */

		strcpy(mensajeEnv,"hola amigo");
		sendto(s, mensajeEnv, strlen(mensajeEnv), 0, (struct sockaddr *) &dirServ, sizeof(dirServ));
		int tam= sizeof(dirServ);
		rec= recvfrom(s, mensajeRec, sizeof(mensajeRec), 0, (struct sockaddr *) &dirServ, &tam);
		mensajeRec[rec]='\0';
		printf("recibido :%s:\n",mensajeRec);

}
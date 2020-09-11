/*
 * Server con Transmission Control Protocol (TCP).
 * Lizandro jose Ramirez Difo
 * Fecha 28/09/2014
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
#define IP_SERVER "138.100.153.96"


main (int argc, char *argv[])
{

 int sockfd; /* descriptor para el socket */
 struct sockaddr_in my_addr; /* direccion IP y numero de puerto local */
 struct sockaddr_in their_addr; /* direccion IP y numero de puerto del cliente */
 int addr_len, numbytes;/* addr_len contendra el tamanio de la estructura sockadd_in y 
 *  numbytes el numero de bytes recibidos
 */
 int connect_d; 
 char a;/*Operando numeros de un digitio 0-9*/
 char operando;/*Operacion a realizar -,+,/,* */
 char b;/*Operando numeros de un digitio 0-9*/
 int resultado;

 char buf[BUFFER_LEN]; /* Buffer de recepción */
 char buf2[6];
 
 /* se crea el socket */
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		 perror("socket");
		 exit(1);
 }

 /* Se establece la estructura my_addr para luego llamar a bind() */
 my_addr.sin_family = AF_INET; /* usa host byte order */
 my_addr.sin_port = htons(SERVER_PORT); /* usa network byte order */
 my_addr.sin_addr.s_addr = inet_addr(IP_SERVER);/* INADDR_ANY; /*escuchamos en todas las IPs */
 /*bzero(&(my_addr.sin_zero), 8); *//* rellena con ceros el resto de la estructura */
/* Se le da un nombre al socket (se lo asocia al puerto e IPs) */
 
 printf("Creando socket ....\n");
 if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
		 perror("bind");
		 exit(1);
 }


/*	listen(sockfd,5);*/
 if (listen(sockfd, 10) == -1)
    {
    	perror("No listen nada");
    	exit(1);
    }


while (1) 
	{
		addr_len = sizeof(struct sockaddr);
		int connect_d = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
		if(connect_d == -1)
			{
				perror("No puedo conectarme con el cliente");
			}
		printf("Esperando datos ....\n");
		int n= read (connect_d,buf,BUFFER_LEN);
		printf("paquete proveniente de : %s\n",inet_ntoa(their_addr.sin_addr));	
		printf("longitud del paquete en bytes : %d\n",n);

		while ( n>0 ) 
			{
				buf[n]='\0';
				printf("He recibido el mensaje: %s\n", buf);
				if(n == 3)
					{
						a=buf[0];
						operando=buf[2];
						b=buf[1];

						printf("a es = %d\n", a-48);
						printf("b es = %d\n", b-48);		       

						switch(operando)
								{
									case 42:
											resultado=(a-48)*(b-48);
											printf("Resultado de la multiplicacion: %d\n", (a-48)*(b-48) );
											break;
									case 43:
											resultado=(a-48)+(b-48);
											printf("Resultado de la suma: %d\n", (a-48)+(b-48));
											break;
									case 45:
											resultado=(a-48)-(b-48);
											printf("Resultado de la resta: %d\n", (a-48)-(b-48));
											break;
									case 47:
											resultado=float((a-48))/float((b-48));
											printf("Resultado de la division: %f\n", float((a-48))/float((b-48)));
											break;
									defalut:
											printf("Ha ingresado un operando no valido\n");
											write (connect_d,"operando incorrecto!",BUFFER_LEN);
											break;

								}

						buf2[0]=resultado+'0';
						printf("Buf2 antes de enviar: %s\n",buf2);
						write (connect_d,buf2,BUFFER_LEN);

					}
				else
					{
						printf("Formato incorrecto : %s\n", buf);   
						write (connect_d,"formato incorrecto!",BUFFER_LEN);
					}

					n= read (connect_d,buf,BUFFER_LEN);
			}


	}

close (connect_d);
}


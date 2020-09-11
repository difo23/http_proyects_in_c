/*
 * Server con HiperText Transfer Protocol (HTTP).
 * Lizandro jose Ramirez Difo
 * Fecha 18/10/2014
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
#define STRING_SEND 7

 /*Recibo el head del servidor: 

HTTP/1.0 200 OK
Server: SimpleHTTP/0.6 Python/2.7.3
Date: Sat, 18 Oct 2014 21:05:47 GMT
Content-type: text/html
Content-Length: 63
Last-Modified: Sat, 18 Oct 2014 18:29:20 GMT

<html>
<head>
</head>

Continuo con el <body> de la pagina: 

<body>
Holaaa leon!</p>
</boby>
</html>
No recibo nada Me salgo!
*/

void sendhtml(int sockfd)
{

		char buf[BUFFER_LEN];
		const char *bufstr[STRING_SEND];
		bufstr[0]="HTTP/1.0 200 OK\r\n";
		bufstr[1]="Server: SimpleHTTPC/0.6 C/2.7.3\r\n";
		bufstr[2]="Date: Sat, 18 Oct 2014 21:05:47 GMT\r\n";
		bufstr[3]="Content-type: text/html\r\n";
		bufstr[4]="Content-Length: 149\r\n";
		bufstr[5]="Last-Modified: Sat, 18 Oct 2014 18:29:20 GMT\r\n";
		bufstr[6]="\r\n";
		/*bufstr[7]="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" ";
		bufstr[8]="\"http://www.w3.org/TR/html4/strict.dtd\">\n";
		bufstr[9]="<html>\n";
		bufstr[10]="<head>\n";
		bufstr[11]="</head>\n\n";
		bufstr[12]="<body>\r\n";
		bufstr[13]="Holaaa leon!</p>\n";
		bufstr[14]="</body>\r\n";
		bufstr[15]="</html>";
		*/

		int i;
		for(i=0;i<(7);++i)
		{
				strcpy(buf,bufstr[i]);

				if(write (sockfd,buf,strlen(buf))==-1)
				{
					printf("No escribe\n");
				}

		}

		return;

}

void sendfilehtml(int sockfd, char namefile[])
{

		FILE *fichero;
		char buffer[2048]; //buffer 
		int bytesleidos;
		fichero = fopen(namefile,"rb");
		const char *bufname[BUFFER_LEN];
		bufname[0]="</head>\n";
		bufname[1]="</head>\n\n";
        char buff[2048];
        char cadena[100];
        strcpy(buff,bufname[0]);

		if(!fichero)
		{
			printf(" El fichero  no puede ser leido\n");
			return;
		}

		
		//bucle de envio
		//while((bytesleidos=fread(buffer,1,2048,fichero)))
		//	if(write(sockfd, buffer, strlen(buffer))==-1)
		//	{
		//		printf("No envio nada del file\n");
		//	}
		
		int result;

		while(fgets(cadena,100,fichero)!= NULL)
		{
			result=strncmp(cadena,buff,8);
			if(result!=0)
			{
				    
					if(write(sockfd, cadena, strlen(cadena))==-1)
					{
							printf("No envio nada del file\n");
					}
			}
			else if(result==0)
			{
					strcpy(cadena,bufname[1]);
					if(write(sockfd, cadena, strlen(cadena))==-1)
					{
							printf("No envio nada del file\n");
					}
			}
		}

		fclose(fichero);
		return ;
}


void readlinehttp(int sockfd) /* Función donde se ejecuta la lógica del programa */
	{

	printf("Esperando pedido del cliente... \n");	
	int rec=0;
	char bufrc[BUFFER_LEN];
	const char *bufname[BUFFER_LEN];
	int x=0;
	char buf[BUFFER_LEN];
	char buf2[BUFFER_LEN];
	int get=0;
	int cont=0;


	printf("Recibo el head del cliente: \n\n");

		while(x==0)
			{
				if(rec=read(sockfd,bufrc,1)==0)
				{
					printf("\nNo recibo nada Me salgo!\n");
				 	x=1;
				}

				if(get==0)
				{
					buf[cont]=bufrc[rec];
					++cont;
				}

				if(bufrc[rec]=='\n')
				{
							get=1;
						
							printf("\n");
							if(rec=read(sockfd,bufrc,1)==0)
								{
									printf("\nNo recibo nada Me salgo!\n");
								 	x=1;
								}

								if(bufrc[rec]=='\r')
								{	
									if(rec=read(sockfd,bufrc,1)==0)
									{
										printf("\nNo recibo nada Me salgo!\n");
									 	x=1;
									}
									if(bufrc[rec]=='\n')
									{
										x=1;
									}
									
								}
						
							
				}
				
		 		bufrc[rec+1]='\0';
				printf("%s",bufrc);
			}

    //bufname[0]="pepe.html";
   // bufname[1]="index1.html";
    //bufname[2]="index2.html";
    //strcpy(buf,bufname[0]);
	
	int cont2=0;
	for(int i=0;i<=cont;++i)
	{
		if(buf[i]==' ')
		{
			buf[i]='.';
			buf[i+1]='/';
			//i+=2;
			for(int y=0;y<=cont;++y)
			{
				if(buf[i+y]==' ')
				{
					i=cont;
					y=cont;
				}
				buf2[cont2]=buf[i+y];
				++cont2;
			}
		}
		
	}

    buf2[cont2]='\0';
    printf("\nEsto es nombre del archivo enviado *%s*\n",buf2);
    sendhtml(sockfd);
    sendfilehtml(sockfd,buf2);			
	return; /* sale de la función */
}



main (int argc, char *argv[])
{

 int sockfd; /* descriptor para el socket */
 struct sockaddr_in my_addr; /* direccion IP y numero de puerto local */
 struct sockaddr_in their_addr; /* direccion IP y numero de puerto del cliente */
 int addr_len, numbytes;/* addr_len contendra el tamanio de la estructura sockadd_in y 
 *  numbytes el numero de bytes recibidos
 */
 int connect_d; 


char buf[BUFFER_LEN]; /* Buffer de recepción */



 
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

int conthijo=0;

while (1) 
	{
		addr_len = sizeof(struct sockaddr);
		int connect_d = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
		if(connect_d == -1)
			{
				perror("No puedo conectarme con el cliente");
			}
           
					int pid= fork();
					if(pid==0)
					{

							close(sockfd);
							printf("Esperando datos soy el hijo %d ....\n",conthijo);
							readlinehttp(connect_d);
							printf("paquete proveniente de : %s\n",inet_ntoa(their_addr.sin_addr));	
							//sendhtml(connect_d);
							usleep(2000000);
							close (connect_d);
							
							exit(1);
					}
					else
					{
						printf("Esperando datos soy el padre con tantos hijos %d ....\n",conthijo);
						close(connect_d);
						++conthijo;

					}

	}


}


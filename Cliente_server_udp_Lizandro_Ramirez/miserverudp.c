/*
 * Server con datagramas (UDP).
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
int main(int argc, char *argv[])
{

 int sockfd; /* descriptor para el socket */
 struct sockaddr_in my_addr; /* direccion IP y numero de puerto local */
 struct sockaddr_in their_addr; /* direccion IP y numero de puerto del cliente */
 int addr_len, numbytes;/* addr_len contendra el tamanio de la estructura sockadd_in y 
 *  numbytes el numero de bytes recibidos
 */
 char a;
 char operando;
 char b;
 int resultado;
 char buf[BUFFER_LEN]; /* Buffer de recepción */
 char buf2[5];
 /* se crea el socket */
 if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
 perror("socket");
 exit(1);
 }
 
 /* Se establece la estructura my_addr para luego llamar a bind() */
 my_addr.sin_family = AF_INET; /* usa host byte order */
 my_addr.sin_port = htons(SERVER_PORT); /* usa network byte order */
 my_addr.sin_addr.s_addr = /*inet_addr("138.100.154.96");*/ INADDR_ANY; /*escuchamos en todas las IPs */
 /*bzero(&(my_addr.sin_zero), 8); *//* rellena con ceros el resto de la estructura */
 

 /* Se le da un nombre al socket (se lo asocia al puerto e IPs) */
 printf("Creando socket ....\n");
 if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
 perror("bind");
 exit(1);
 }
 
 while(1)
 {
 /* Se reciben los datos (directamente, UDP no necesita conexión) */
     addr_len = sizeof(struct sockaddr);
     printf("Esperando datos ....\n");

     if ((numbytes=recvfrom(sockfd, buf, BUFFER_LEN, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
     perror("recvfrom");
     exit(1);
     }
 

 /* Se visualiza lo recibido */
     printf("paquete proveniente de : %s\n",inet_ntoa(their_addr.sin_addr));
 
     if(numbytes == 3)
     {
        printf("longitud del paquete en bytes : %d\n",numbytes);
        buf[numbytes] = '\0';
        a=buf[0];
        operando=buf[2];
        b=buf[1];

        printf("a es = %d\n", a-48);
        printf("b es = %d\n", b-48);
        printf("el paquete contiene : %s\n", buf);
        
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
                    break;

        }
    buf2[0]=resultado+'0';
  if ((numbytes=sendto(sockfd,buf2,6,0,(struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) 
     {
        perror("sendto");
        exit(1);
    }


     }
    else
    {
     printf("Formato incorrecto : %s\n", buf);   
    }
}
 /* cerramos descriptor del socket */
 close(sockfd);
 
 return 0;
}
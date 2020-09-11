#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

main(int argc, char *argv[]) 
{

if(argc!=2) {
		printf("Ha olvidado su nombre.\n"); 
		exit(1);
	} 
	printf("Hola %s \n", argv[1]);
}
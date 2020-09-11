
// copia.c: Copia de ficheros
// Uso: copia <fichero_origen> <fichero_destino>

#include <stdio.h>

int main(int argc, char **argv) {
    FILE *fe, *fs;
    unsigned char buffer[2048]; // Buffer de 2 Kbytes
    int bytesLeidos;

    if(argc != 3) {
       printf("Usar: copia <fichero_origen> <fichero_destino>\n");
       return 1;
    }

    // Abrir el fichero de entrada en lectura y binario
    fe = fopen(argv[1], "rb"); 
    if(!fe) {
       printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
       return 1;
    }
    // Crear o sobreescribir el fichero de salida en binario
    fs = fopen(argv[2], "wb"); 
    if(!fs) {
       printf("El fichero %s no puede ser creado.\n", argv[2]);
       fclose(fe);
       return 1;
    }
    // Bucle de copia:
    while((bytesLeidos = fread(buffer, 1, 2048, fe)))
       fwrite(buffer, 1, bytesLeidos, fs);
    // Cerrar ficheros:
    fclose(fe);
    fclose(fs);
    return 0;
}
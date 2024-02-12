/*tarea1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Probad tras la ejecución del programa: $>cat archivo y $> od -c archivo
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main(int argc, char *argv[])
    int fd;
if( (fd=open("archivo",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR))<0) {        printf("\nError %d en open",errno);
 perror("\nError en open");        
 exit(-1);
}

if(write(fd,buf1,10) != 10) {        
    perror("\nError en primer write");        
    exit(-1);
}

if(lseek(fd,40,SEEK_SET) < 0) {        
    perror("\nError en lseek");
    exit(-1);
}

if(write(fd,buf2,10) != 10) {        
    perror("\nError en segundo write");        
    exit(-1);
}

close(fd);

return 0;
}

/*
El programa comienza creando dos arrays, buf1 y buf2, que contienen 10 caracteres cada uno. A ontinuación, entra en el main y crea un entero, fd, al cual le asigna el valor de la llamada al sistema open del archivo "archivo", con los flags O_CREAT(se crea si no existe), O_TRUNC(si existe el fichero y tiene habilitada la escritura, lo sobreescribe a tamaño 0), O_WRONLY(decimos que solo se permite escritura), S_IRUSR(comprobamos que el usuario tiene permiso de lectura) y, por último, S_IWUSR(comprobamos que el usuario tiene permiso de escritura). 
Si existe algún error en la apertura, imprime los dos mensajes correspondientes por pantalla y, a continuación, acaba el programa, devolviendo -1

A continuación, escribe los 10 primeros caracteres, correspondientes a buf1. Si existe algún error(no se escriben los 10 caracteres) manda un mensaje de error y acaba el programa, devolviendo -1

Después, con lseek, ponemos el puntero del archivo en la posiión 40(bytes) desde SEEK_SET(inicio del fichero), de esta forma el puntero se situa despues de los caracteres escritos anteriormente. Además, manda un mensaje de error y hhubiera algún fallo y acaba el programa devolviendo -1

Por último, repite el mismo procedimiento de buf1, pero con buf2 y cierra el fichero

Acaba el programa retornando 0
*/

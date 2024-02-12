/*
tarea3.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Este programa fuente está pensado para que se cree primero un programa con la
parte de CREACION DE ARCHIVOS y se haga un ls -l para fijarnos en los permisos y
entender la llamada umask.
En segundo lugar (una vez creados los archivos) hay que crear un segundo programa
con la parte de CAMBIO DE PERMISOS para comprender el cambio de permisos relativo a los permisos que actualmente tiene un archivo frente a un establecimiento de
permisos absoluto.
*/
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>

int main(int argc, char *argv[])
{
	int fd1,fd2;
	struct stat atributos;
	//CREACION DE ARCHIVOS
	    
	// ----r-x--- 
	// S_IRGRP (00040)
	// S_IWGRP (00020)
	// S_IXGRP (00010)
	// modo & ~umask --> Que permiso que quieres tener
	// modo & umask  --> Permisos que no quieres tene
	// modo = suma las macros
	// máscara por defecto en el sistema es 00022
	// modo = 00070 & 00022 = umask   --> 00020
	// modo = 00070 & ~00022 = ~umask --> 00050  (00070-00020)

	if( (fd1=open("archivo1",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0)
	{
		printf("\nError %d en open(archivo1,...)",errno);
		perror("\nError en open");
		exit(-1);
	}
    
	// ----rwx---
	// Igual que el caso de arriba, pero la máscara vale 0
	// modo = 00070 & ~00000 = ~umask --> 00070

	umask(0);
	if( (fd2=open("archivo2",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0)
	{
		printf("\nError %d en open(archivo2,...)",errno);
		perror("\nError en open");
		exit(-1);
	}

	//CAMBIO DE PERMISOS

	if(stat("archivo1",&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de archivo1");
		perror("\nError en lstat");
		exit(-1);
	}
	if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
		perror("\nError en chmod para archivo1");
		exit(-1);
	}
	if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0) {
		perror("\nError en chmod para archivo2");
		exit(-1);
	}

	close(fd1);
	close(fd2);

	return 0;
}

/*
Lo que hace el programa es crear un archivo llamado archivo1 con permisos de lectura,
escritura y ejecución para el grupo, seguidamente pone la máscara a 0 con la orden
umask(0) y después crea otro archivo llamado archivo2, con los mismos permisos que el
archivo anterior.

Luego comprueba que se puede acceder a los atributos del primer archivo con la orden
stat.

Después con chmod cambiamos los permisos del primer archivo haciendo un AND lógico
del estado del archivo(accediendo al struct atributos) con el negado del permiso de
ejecución para el grupo, con lo que le quitamos el permiso de ejecución para el grupo.
También activamos la asignación del GID del propietario al GID efectivo del proceso que
ejecute el archivo.

Por último con chmod cambiamos los permisos del segundo archivo para que tenga
todos los permisos para el propio usuario, permiso de lectura y escritura para el grupo, y
lectura para el resto de usuarios.
*/

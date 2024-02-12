#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>

int main(int argc, char *argv[]){
	DIR *dir;
	struct dirent *entrada;
	struct stat atributos;
	int permisosNuevos, permisosAntiguos;
	char pathname[500];

	if(argc != 3){
		exit(-1);
	}

	dir = opendir(argv[1]);
	permisosNuevos = strtol(argv[2], NULL, 8);

	while((entrada = readdir(dir)) != 0){
		sprintf(pathname, "%s/%s", argv[1], entrada->d_name);
		lstat(pathname, &atributos);
		permisosAntiguos = atributos.st_mode;

		if(chmod(pathname, permisosNuevos) == 0){
			printf("%s: %o %o\n", entrada->d_name, permisosAntiguos, permisosNuevos);
		}else{
			printf("%s: %d %o", entrada->d_name, errno, permisosAntiguos);
		}
	}

	closedir(dir);

	return 0;
}

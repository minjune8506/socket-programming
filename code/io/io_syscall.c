#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage : %s [Filename] \n", argv[0]);
		return EXIT_FAILURE;
	}

	int fd, writeLen, readLen;
	char buff[BUFSIZ];

	readLen = read(0, buff, BUFSIZ - 1);
	if (readLen == -1) {
		fprintf(stderr, "Read Error\n");
		return EXIT_FAILURE;
	}
	printf("Total reading data : %d\n", readLen);
	buff[readLen] = '\0';

	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	if (fd == -1) {
		fprintf(stderr, "Open Error\n");
		return EXIT_FAILURE;
	}
	
	writeLen = write(fd, buff, readLen + 1);
	if (writeLen == -1) {
		fprintf(stderr, "Write Error\n");
		return EXIT_FAILURE;
	}
	printf("Total writing data : %d\n", writeLen);
	close(fd);
	return EXIT_SUCCESS;
}

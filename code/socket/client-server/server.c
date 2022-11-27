#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# define PORT 9001

int main() {
	int server_sd, client_sd;
	struct sockaddr_in server_addr, client_addr;
	int readLen;
	char rbuff[BUFSIZ];
	char wbuff[BUFSIZ] = "I am 25 years old.";

	server_sd = socket(PF_INET, SOCK_STREAM, 0);
	if (server_sd == -1) {
		fprintf(stderr, "Socket Creation Error\n");
		return -1;
	}
	printf("===== server program =====\n");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	if (bind(server_sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		fprintf(stderr, "Bind Error\n");
		return -1;
	}

	if (listen(server_sd, 2) == -1) {
		fprintf(stderr, "Listen Error\n");
		return -1;
	}
	
	socklen_t client_addr_len = sizeof(client_addr);
	client_sd = accept(server_sd, (struct sockaddr *)&client_addr, &client_addr_len);
	if (client_sd == -1) {
		fprintf(stderr, "Accept Error\n");
		return -1;
	}

	readLen = read(client_sd, rbuff, sizeof(rbuff));
	if (readLen == -1) {
		fprintf(stderr, "Read Error\n");
		return -1;
	}

	rbuff[readLen] = '\0';
	printf("Client : %s\n", rbuff);

	write(client_sd, wbuff, sizeof(wbuff));
	printf("Server : %s\n", wbuff);

	close(client_sd);
	close(server_sd);

	return 0;
}

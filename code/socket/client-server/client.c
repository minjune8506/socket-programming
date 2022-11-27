#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

# define PORT 9001

int main(void) {
	int client_sd;
	struct sockaddr_in server_addr;
	int client_addr_len, read_len;
	char wbuff[BUFSIZ] = "How old are you?";
	char rbuff[BUFSIZ];

	client_sd = socket(PF_INET, SOCK_STREAM, 0);
	if (client_sd < 0) {
		fprintf(stderr, "Socket Creation Error\n");
		return -1;
	}

	printf("===== client program =====\n");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(PORT);

	if (connect(client_sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		fprintf(stderr, "Connect Error\n");
		close(client_sd);
		return -1;
	}

	int write_len = write(client_sd, wbuff, sizeof(wbuff));
	if (write_len == -1) {
		fprintf(stderr, "Write Error\n");
		close(client_sd);
		return -1;
	}
	printf("Client : %s\n", wbuff);

	read_len = read(client_sd, rbuff, sizeof(rbuff));
	if (read_len == -1) {
		fprintf(stderr, "Read Error\n");
		close(client_sd);
		return -1;
	}

	rbuff[read_len] = '\0';
	printf("Server : %s\n", rbuff);
	close(client_sd);
	return 0;
}

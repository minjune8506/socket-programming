#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>


int main(void) {
	int tcp_sd, udp_sd;
	socklen_t opt_len;
	int opt_val;
	struct linger my_linger, res_linger;

	tcp_sd = socket(PF_INET, SOCK_STREAM, 0);
	udp_sd = socket(PF_INET, SOCK_DGRAM, 0);

	// SO_TYPE
	opt_len = sizeof(opt_val);
	getsockopt(tcp_sd, SOL_SOCKET, SO_TYPE, (void *)&opt_val, &opt_len);
	printf("SO_STYLE of tcp_sd : %d\n", opt_val);
	getsockopt(udp_sd, SOL_SOCKET, SO_TYPE, (void *)&opt_val, &opt_len);
	printf("SO_STYLE of udp_sd : %d\n", opt_val);

	// SO_DEBUG
	getsockopt(tcp_sd, SOL_SOCKET, SO_DEBUG, (void *)&opt_val, &opt_len);
	printf("SO_DEBUG of tcp_sd : %d\n", opt_val);
	opt_val = 1;
	setsockopt(tcp_sd, SOL_SOCKET, SO_DEBUG, (void *)&opt_val, opt_len);
	getsockopt(tcp_sd, SOL_SOCKET, SO_DEBUG, (void *)&opt_val, &opt_len);
	printf("SO_DEBUG of tcp_sd : %d\n", opt_val);

	// SO_LINGER
	my_linger.l_onoff = 1;
	my_linger.l_linger = 7;
	opt_len = sizeof(my_linger);
	getsockopt(tcp_sd, SOL_SOCKET, SO_LINGER, (void *)&res_linger, &opt_len);
	printf("SO_LINGER - l_onoff :  %d\n", res_linger.l_onoff);
	printf("SO_LINGER - l_linger :  %d\n", res_linger.l_linger);

	setsockopt(tcp_sd, SOL_SOCKET, SO_LINGER, (void *)&my_linger, opt_len);
	getsockopt(tcp_sd, SOL_SOCKET, SO_LINGER, (void *)&res_linger, &opt_len);
	printf("SO_LINGER - l_onoff :  %d\n", res_linger.l_onoff);
	printf("SO_LINGER - l_linger :  %d\n", res_linger.l_linger);

	close(tcp_sd);
	close(udp_sd);

	return 0;
}

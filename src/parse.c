/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:10:56 by rbourgea          #+#    #+#             */
/*   Updated: 2023/11/15 07:03:14 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_traceroute.h"

void print_help() {
	printf("Usage:\n  traceroute\nOptions:\n  --help                      Read this help and exit\n\nArguments:\n+     host          The host to traceroute to\n      packetlen     The full packet length (default is the length of an IP\n                    header plus 40). Can be ignored or increased to a minimal\n                    allowed value\n");
}

void	init_socket(int *sockfd) {
	struct timeval tv= {1,0};

	if ((*sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		dprintf(2, "ft_traceroute: error creating socket\n");
		exit(1);
	}
	if (setsockopt(*sockfd, IPPROTO_IP, IP_HDRINCL, (int[1]){1}, sizeof(int)) < 0)
	{
		close(*sockfd);
		exit(1);
	}
	if (setsockopt(*sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval)) < 0)
	{
		close(*sockfd);
		exit(1);
	}
}

void	resolve_destination() {
	struct addrinfo hints;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_flags = AI_CANONNAME;

	if ((getaddrinfo(g_trace.dest, 0, &hints, &g_trace.info))) {
		printf("%s: Name or service not known\n", g_trace.dest);
		printf("Cannot handle \"host\" cmdline arg `%s' on position 1 (argc 1)\n", g_trace.dest);
		exit(2);
	}

	init_socket(&g_trace.sockfd); // socket in
	init_socket(&g_trace.rsockfd); // socket out

	ft_bzero(&g_trace.ip, sizeof(g_trace.ip));
	ft_bzero(&g_trace.oldip, sizeof(g_trace.oldip));

	ft_strcpy(g_trace.ip, inet_ntoa(((const struct sockaddr_in *)g_trace.info->ai_addr)->sin_addr));
}

void	parse_arg(int ac, char **av) {
	char *arg;
	int i = 1;

	if (ac < 2) {
		print_help();
		exit(1);
	}

	while (i < ac) {
		arg = av[i];
		if (ac > 3) {
			printf("Extra arg `%c' (position 3, argc 3)\n", av[2][0]);
			exit(2);
		}
		else if (ft_strncmp(arg, "--help", 6) == 0) {
			print_help();
			exit(2);
		}
		else if (arg[0] == '-' && arg[1] == '-') {
			printf("Specify \"host\" missing argument.\n");
			exit(2);
		}
		else if (arg[0] == '-' && arg[1]) {
			printf("Bad option `-%c' (argc 1)\n", arg[1]);
			exit(2);
		}
		else {
			g_trace.dest = arg;
			resolve_destination();
		}
		i++;
	}
}
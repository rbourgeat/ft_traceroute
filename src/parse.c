/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:10:56 by rbourgea          #+#    #+#             */
/*   Updated: 2023/11/13 09:00:31 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_traceroute.h"

void print_help() {
	printf("Usage:\n  traceroute\nOptions:\n  --help                      Read this help and exit\n\nArguments:\n+     host          The host to traceroute to\n      packetlen     The full packet length (default is the length of an IP\n                    header plus 40). Can be ignored or increased to a minimal\n                    allowed value\n");
}

void parse_arg(int ac, char **av) {
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
			printf("%c: Name or service not known\n", arg[0]);
			printf("Cannot handle \"host\" cmdline arg `%c' on position 1 (argc 1)\n", arg[0]);
			exit(2);
		}
		i++;
	}
}
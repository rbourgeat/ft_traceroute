/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:10:47 by rbourgea          #+#    #+#             */
/*   Updated: 2023/11/13 08:43:02 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_traceroute.h"

int main(int ac, char **av) {

	if (getuid() != 0) {
        printf("You need to run it with sudo.\n");
		exit(1);
    }

    parse_arg(ac, av);
}
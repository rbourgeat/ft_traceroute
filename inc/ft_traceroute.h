/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:11:02 by rbourgea          #+#    #+#             */
/*   Updated: 2023/11/13 08:33:42 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

// libft.c
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// parse.c
void parse_arg(int ac, char **av);

#endif
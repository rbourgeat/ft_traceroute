/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:11:02 by rbourgea          #+#    #+#             */
/*   Updated: 2023/11/15 07:15:59 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/udp.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <errno.h>
# include <signal.h>

# define MAXHOPS		30
# define DATALEN		52
# define ICMP_PAYLOAD	1472
# define ICMP_HDRLEN	8
# define IPHDRLEN		20

typedef struct			s_tval
{
	long				tv;
	long				tv2;
	long				tv3;
}						t_tval;

typedef struct			s_trace
{
	int					sockfd;
	int					rsockfd;
	int					seq;
	int					ttl;
	int					hmax;
	pid_t				pid;
	char				*dest;
	char				packet[ICMP_PAYLOAD];
	char				rcvpacket[ICMP_PAYLOAD];
	char				ip[INET_ADDRSTRLEN];
	char				oldip[INET_ADDRSTRLEN];
	char				addr[INET_ADDRSTRLEN];
	int					len_packet;
	t_tval				tv_in;
	t_tval				tv_out;
	struct addrinfo		*info;
}						t_trace;

t_trace					g_trace;

// main.c
t_tval	gettimestamp_ms();
void	endtraceroute(int sig);

// libft.c
int     ft_strncmp(const char *s1, const char *s2, size_t n);
void    *ft_memcpy(void *destination, const void *source, size_t size);
void    ft_strcpy(char *dest, const char *src);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

// parse.c
void    parse_arg(int ac, char **av);

// packets.c
void    createpackets();
int		readpackets();

// probes.c
void	sendprobe();
void	printprobe(int nprobe);
void	checkprobe(int len, int nprobe);

#endif
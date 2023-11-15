/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:10:47 by rbourgea          #+#    #+#             */
/*   Updated: 2023/11/15 07:12:51 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_traceroute.h"

void	endtraceroute(int sig) {
	(void)sig;
	printf("\n");
	close(g_trace.sockfd);
	close(g_trace.rsockfd);
	exit(1);
}

t_tval	gettimestamp_ms() {
	struct timeval	te;
	t_tval          tv;
	long			mm;

	gettimeofday(&te, NULL);
	ft_bzero(&tv, sizeof(t_tval));
	tv.tv = te.tv_sec * 1000LL + te.tv_usec / 1000;
	mm = te.tv_sec * 10LL + te.tv_usec / 10;
	tv.tv3 = mm % 1000;
	tv.tv2 = mm % 100;
	return (tv);
}

void	traceroute() {
	ssize_t	responsesize;
	int		nprobes;
	
	responsesize = 0;
	nprobes = 4;
	while (--nprobes)
	{
		sendprobe();
	}
	nprobes = 4;
	while (--nprobes)
	{
		responsesize = readpackets();
		if (responsesize < 1)
		{
			if (nprobes == 3)
				printf("%2d  ", g_trace.ttl);
			printf("* ");
		}
		else
			checkprobe(responsesize, nprobes);
	}
	printf("\n");
}

int		main(int ac, char **av) {
	int		i;

	if (getuid() != 0) {
		printf("You need to run it with sudo.\n");
		exit(1);
	}

	signal(SIGINT, endtraceroute);
	ft_bzero(&g_trace, sizeof(g_trace));
	g_trace.pid = getpid();
	g_trace.hmax = MAXHOPS;
	g_trace.ttl = 1;
	g_trace.seq = 0;
	g_trace.len_packet = DATALEN + sizeof(struct udphdr);
	parse_arg(ac, av);

	printf("ft_traceroute to %s (%s), %d hops max, %d byte packets\n",
		g_trace.dest, g_trace.ip, g_trace.hmax, g_trace.len_packet);

	i = -1;
	while (++i < g_trace.hmax)
	{
		traceroute();
		g_trace.ttl += 1;
	}
}
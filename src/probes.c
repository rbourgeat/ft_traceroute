/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   probes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:31:35 by rbourgea          #+#    #+#             */
/*   Updated: 2023/11/15 07:22:55 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_traceroute.h"

void	checkprobe(int len, int nprobe) {
	if (((struct icmp*)(g_trace.rcvpacket + IPHDRLEN))->icmp_type != ICMP_TIME_EXCEEDED || len == -1)
		printprobe(nprobe);
	else
	{
		if (((struct icmp*)(g_trace.rcvpacket + 48))->icmp_id != g_trace.pid)
			return;
		else
		{
			g_trace.tv_out = gettimestamp_ms();
			if (nprobe == 3 || (nprobe != 3 && ft_strcmp(g_trace.oldip, g_trace.ip) > 0))
				printf("%2d  %s",g_trace.ttl, g_trace.ip);
			if ((g_trace.tv_out.tv3 - g_trace.tv_in.tv3) > 0)
				printf(" %ld.%ld ms ", g_trace.tv_out.tv - g_trace.tv_in.tv, g_trace.tv_out.tv3 - g_trace.tv_in.tv3);
			else if ((g_trace.tv_out.tv2 - g_trace.tv_in.tv2) > 0)
				printf(" %ld.%ld ms ", g_trace.tv_out.tv - g_trace.tv_in.tv, g_trace.tv_out.tv2 - g_trace.tv_in.tv2);
			else
				printf(" %ld ms ", g_trace.tv_out.tv - g_trace.tv_in.tv);
		}	
	}
}

void	sendprobe() {
	size_t len;

	createpackets();
	g_trace.tv_in = gettimestamp_ms();
	len = DATALEN + ICMP_HDRLEN + IPHDRLEN;
	if (sendto(g_trace.sockfd, g_trace.packet, len, 0, g_trace.info->ai_addr, g_trace.info->ai_addrlen) < 0)
	{
		close(g_trace.sockfd);
		exit(1);
	}
}

void	printprobe(int nprobe) {
	g_trace.tv_out = gettimestamp_ms();
	if (nprobe == 3 || (nprobe != 3 && ft_strcmp(g_trace.oldip, g_trace.ip) > 0))
		printf("%2d  %s",g_trace.ttl, g_trace.ip);
	if ((g_trace.tv_out.tv3 - g_trace.tv_in.tv3) > 0)
		printf(" %ld.%ld ms ", g_trace.tv_out.tv - g_trace.tv_in.tv, g_trace.tv_out.tv3 - g_trace.tv_in.tv3);
	else if ((g_trace.tv_out.tv2 - g_trace.tv_in.tv2) > 0)
		printf(" %ld.%ld ms ", g_trace.tv_out.tv - g_trace.tv_in.tv, g_trace.tv_out.tv2 - g_trace.tv_in.tv2);
	else
		printf(" %ld ms ", g_trace.tv_out.tv - g_trace.tv_in.tv);
	if (nprobe == 1)
	{
		endtraceroute(SIGINT);
		exit (0);
	}
}
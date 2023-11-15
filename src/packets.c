/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 04:46:33 by rbourgea          #+#    #+#             */
/*   Updated: 2023/11/15 07:03:11 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_traceroute.h"

unsigned short	checksum(unsigned short *addr, int len) {
	int				nleft;
	int				sum;
	unsigned short	*w;
	unsigned short	answer;

	nleft = len;
	sum = 0;
	w = addr;
	answer = 0;
	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1)
	{
		*(unsigned char*)(&answer) = *(unsigned char*)w;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}

void    init_msg(char *content) {
	ssize_t i;

	i = -1;
	while (++i < DATALEN)
		content[i] = 16 + i;
}

void    init_ip_hdr(struct ip *ip) {
	ip->ip_v = 4;
	ip->ip_hl = 5;
	ip->ip_tos = 0;
	ip->ip_len = IPHDRLEN + ICMP_HDRLEN;
	ip->ip_off = 0;
	ip->ip_ttl = g_trace.ttl;
	ip->ip_p = IPPROTO_ICMP;
	ip->ip_sum = 0;
	ip->ip_id = (uint16_t)g_trace.pid;
	ip->ip_dst = (struct in_addr)((struct sockaddr_in*)g_trace.info->ai_addr)->sin_addr;
}

void    init_icmp_hdr(struct icmp *icmp) {
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = (uint16_t)g_trace.pid;
	icmp->icmp_cksum = 0;
	icmp->icmp_seq = ++g_trace.seq;
	icmp->icmp_cksum = checksum((unsigned short*)icmp, DATALEN + ICMP_HDRLEN);
}

void    createpackets() {
	ft_bzero(&g_trace.packet, sizeof(g_trace.packet));
	init_msg((char*)(g_trace.packet + IPHDRLEN + ICMP_HDRLEN));
	init_ip_hdr((struct ip*)(g_trace.packet));
	init_icmp_hdr((struct icmp*)(g_trace.packet + IPHDRLEN));
}

int	readpackets() {
	struct sockaddr_in	sin;
	int					ans;
	unsigned int		addr_len;
	fd_set				fds;
	struct timeval		wait;

	FD_ZERO(&fds);
	FD_SET(g_trace.rsockfd, &fds);
	ans = -2;
	wait.tv_sec = 1;
	wait.tv_usec = 0;
	addr_len = sizeof(struct sockaddr);
	ft_bzero(&g_trace.rcvpacket, sizeof(g_trace.rcvpacket));
	if (select(g_trace.rsockfd+1, &fds, (fd_set*)0, (fd_set*)0, &wait) > 0)
		ans = recvfrom(g_trace.rsockfd, &g_trace.rcvpacket, sizeof(g_trace.rcvpacket), 0, (struct sockaddr*)&sin, &addr_len);
	ft_memcpy(g_trace.oldip, g_trace.ip, sizeof(g_trace.ip));
	ft_strcpy(g_trace.ip, inet_ntoa(sin.sin_addr));
	return (ans);
}

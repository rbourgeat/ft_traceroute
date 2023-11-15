/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:10:53 by rbourgea          #+#    #+#             */
/*   Updated: 2023/11/15 04:40:36 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_traceroute.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n--)
		((unsigned char *)s)[i++] = 0;
}

void	ft_strcpy(char *dest, const char *src) {
	if (dest == NULL || src == NULL) {
		return;
	}

	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
}

void	*ft_memcpy(void *destination, const void *source, size_t size) {
	unsigned	char			*str1;
	const	unsigned	char	*str2;

	str1 = (unsigned char *)destination;
	str2 = (unsigned char *)source;
	if (!size || destination == source)
		return (destination);
	while (size--)
		*str1++ = *str2++;
	return (destination);
}

int		ft_memcmp(const void *s1, const void *s2, size_t n) {
	size_t			i;
	const	char	*src1;
	const	char	*src2;

	if (s1 == NULL && s2 == NULL)
		return (0);
	src1 = s1;
	src2 = s2;
	i = 0;
	while (i < n)
	{
		if (src1[i] != src2[i])
			return ((unsigned char)src1[i] - (unsigned char)src2[i]);
		i++;
	}
	return (0);
}

int		ft_strlen(const char *str) {
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n) {
	if (n > (size_t)ft_strlen(s1))
		n = (size_t)ft_strlen(s1) + 1;
	if (n > (size_t)ft_strlen(s2))
		n = (size_t)ft_strlen(s2) + 1;
	return (ft_memcmp(s1, s2, n));
}

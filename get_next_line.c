/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:20:28 by saragar2          #+#    #+#             */
/*   Updated: 2023/11/08 19:08:42 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (*s != '\0')
	{
		cont ++;
		s ++;
	}
	return (cont);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dstsize == 0)
		return (src_len);
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	int			i;
	char		*aux;

	i = 0;
	if (!buf)
	{
		buf = malloc(BUFFER_SIZE);
		read(fd, buf, BUFFER_SIZE);
	}
	while (*(buf++) != '\n')
		i++;
	i++;
	buf -= i;
	aux = malloc(ft_strlen(buf) * sizeof(char));
	ft_strlcpy(aux, buf, i + 1);
	buf += i;
	return (aux);
}

int	main()
{
	int fd = open("prueba.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}

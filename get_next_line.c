/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:20:28 by saragar2          #+#    #+#             */
/*   Updated: 2023/10/25 21:35:07 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


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

char *get_next_line(int fd)
{
	char					buf[BUFFER_SIZE];
	static unsigned long	i;
	char					*aux;

	i = 0;
	read(fd, buf, sizeof(buf) + i);
	// ------CALCULO DE LA LONGITUD DE LA LINEA
	while (buf[i] != '\n')
	{
		while (i <= sizeof(buf) && buf[i] != '\n')
			i++;
		if (buf[i] != '\n')
			read(fd, buf, sizeof(buf) + i);
	}
	// ------COPIA DE LA STRING EN AUX
	aux = malloc(sizeof(char) * i);
	if (!aux)
		return (NULL);
	ft_strlcpy(aux, buf, i);
	return (aux);
}

int	main()
{
	int fd = open("prueba.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}

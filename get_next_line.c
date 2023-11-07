/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:20:28 by saragar2          #+#    #+#             */
/*   Updated: 2023/10/30 20:53:40 by saragar2         ###   ########.fr       */
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


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = malloc(size);
	if (!newstr)
		return (NULL);
	while (*s1 != '\0')
		*newstr++ = *s1++;
	while (*s2 != '\0')
		*newstr++ = *s2++;
	*newstr = '\0';
	newstr -= (size - 1);
	return (newstr);
}

char *get_next_line(int fd)
{
	static char	*buf;
	int			i;
	//int			j;
	char		*aux;
	//char		*bufaux;

	if (!buf)
	{
		buf = malloc(BUFFER_SIZE);
		read(fd, buf, BUFFER_SIZE);
	}
	while (*(buf++) != '\n')
		i++;
	i++;
	buf -= i;
	ft_strlcpy(aux, buf, i);
	buf += i;
	return (aux);
	
}

int	main()
{
	int fd = open("prueba.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}

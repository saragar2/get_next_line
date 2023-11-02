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
	int			i; //si la i no es estatica, se va a iterar correctamente en las llamadas siguientes a la primera? y si en vez de utilizar arrays, utilizas punteros?
	int			j;
	char		*aux;
	char		*bufaux;

	i = 0;
	j = -2;
	bufaux = NULL;
	if (!buf)
	{
		buf = malloc(BUFFER_SIZE);
		j = read(fd, buf, BUFFER_SIZE);
	}
	if (j == 0)
		return (NULL);  //no funciona. hay que meterlo dentro del while d abajo. adivina donde.
	while (buf[i] != '\n' && j != 0) //y que pasa si buf está a la mitad? como se supone que va a operar eso si la i no es estática? hasta donde deberia iterar en caso de alcanzar buffer_size?
	{
		i++;
		if ((i == BUFFER_SIZE || i == j) && buf[i] != '\n')
		{
			bufaux = ft_strjoin(bufaux, buf); //no tengo muy claro que esto funcione. en la line 68 la he inicializado a nula pero sin aplicar un tamaño.
			i = 0;
			j = read(fd, buf, BUFFER_SIZE);
		}
	}
	aux = malloc(sizeof(char) * (i + 3));
	if (!aux)
		return (NULL);
	ft_strlcpy(aux, buf, i + 2);
	aux[++i] = '\0';
	return (aux);
}

int	main()
{
	int fd = open("prueba.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}

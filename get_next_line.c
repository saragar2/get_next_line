/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:50:29 by saragar2          #+#    #+#             */
/*   Updated: 2023/11/21 21:28:09 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*createbufaux(char *buf, int i, char *bufaux, int j)
{
	char	*subbuf;
	char	*aux;

	if (!bufaux)
		bufaux = ft_substr(buf, 0, i);
	else if (j > 0)
	{
		subbuf = ft_substr(buf, 0, i);
		aux = bufaux;
		bufaux = ft_strjoin(aux, subbuf);
		free(aux);
		free(subbuf);
		subbuf = NULL;
	}
	return (bufaux);
}

char	*newbuf(char *buf, int i, int j)
{
	int		k;
	char	*aux;

	k = 0;
	aux = malloc(ft_strlen(buf) + 1);
	if (!aux)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	while (buf[k] != '\0')
	{
		aux[k] = buf[k];
		k++;
	}
	aux[k] = '\0';
	free(buf);
	buf = NULL;
	buf = ft_substr(aux, i, j - i + 1);
	free(aux);
	aux = NULL;
	return (buf);
}

char	*bufauxfornull(char *bufaux, char *buf)
{
	char	*aux;

	if (!bufaux)
	{
		bufaux = malloc(BUFFER_SIZE);
		if (!bufaux)
		{
			free(buf);
			return (NULL);
		}
		bufaux[0] = '\0';
	}
	aux = bufaux;
	bufaux = ft_strjoin(aux, buf);
	free(aux);
	free(buf);
	return (bufaux);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	int			i;
	int			j;
	char		*bufaux;

	i = 0;
	bufaux = NULL;
	if (!buf || buf[i] == '\0')
	{
		if (buf && buf[i] == '\0')
			free(buf);
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		j = read(fd, buf, BUFFER_SIZE);
		if (j <= 0 || BUFFER_SIZE == 0)
		{
			free(buf);
			buf = NULL;
			return (NULL);
		}
		buf[j] = '\0';
	}
	else
		j = ft_strlen(buf);
	while (buf[i] != '\n' && buf[i] != '\0' && j > 0)
	{
		i++;
		if (buf[i] == '\0')
		{
			bufaux = bufauxfornull(bufaux, buf);
			buf = malloc(BUFFER_SIZE + 1);
			if (!buf)
				return (NULL);
			j = read(fd, buf, BUFFER_SIZE);
			if (j < 0)
			{
				free(buf);
				free(bufaux);
				buf = NULL;
				return (NULL);
			}
			buf[j] = '\0';
			i = 0;
		}
	}
	i++;
	bufaux = createbufaux(buf, i, bufaux, j);
	buf = newbuf(buf, i, j);
	return (bufaux);
}

/*void leaks()
{
	system("leaks -q a.out");
}

int main ()
{
	char	*s;
	int fd = open("multiple_line_with_nl.txt", O_RDONLY);
 
	s = get_next_line(fd);
	printf("%s", s);
	free (s);
 
	s = get_next_line(fd);
	printf("%s", s);
	free (s);
 
	s = get_next_line(fd);
	printf("%s", s);
	free (s);
 
	s = get_next_line(fd);
	printf("%s", s);
	free (s);
 
	s = get_next_line(fd);
	printf("%s", s);
	free (s);
 
	s = get_next_line(fd);
	printf("%s", s);
	free (s);
 
	s = get_next_line(fd);
	printf("%s", s);
	free (s);
 
	atexit(leaks);
	return (0);
}*/

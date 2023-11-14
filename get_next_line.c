/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:20:28 by saragar2          #+#    #+#             */
/*   Updated: 2023/11/14 21:07:49 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (*s != '\0') //-----LEAK
	{
		cont ++;
		s ++;
	}
	s -= cont;
	
	return (cont);
}

char	*ft_strdup(const char *s1)
{
	char	*aux;
	int		len;

	len = ft_strlen(s1);
	aux = malloc(len + 1);
	if (!aux)
		return (NULL);
	while (*s1 != '\0')
	{
		*aux = *s1;
		aux++;
		s1++;
	}
	*aux = '\0';
	while (len > 0)
	{
		len--;
		aux--;
	}
	return (aux);
}

char	*ft_strjoin(char *a, char *b)
{
	char	*newstr;
	int		size;
	char	*s1;
	char	*s2;

	s1 = a;
	s2 = b;
	size = ft_strlen(s1) + ft_strlen(s2) + 1; //-----LEAK
	newstr = malloc(size);
	if (!newstr)
		return (NULL);
	while (*s1 != '\0')
		*newstr++ = *s1++;
	while (*s2 != '\0')
		*newstr++ = *s2++;
	*newstr = '\0';
	newstr -= (size - 1);
	free(a);
	free(b);
	return (newstr);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*aux;
	size_t	cont;

	cont = 0;
	if (start < 0 || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		aux = malloc(ft_strlen(s) - start + 1); //-----LEAK
	else
		aux = malloc(len + 1);
	if (!aux)
		return (NULL);
	s += start;
	while (len > 0 && *s != '\0')
	{
		*(aux++) = *(s++);
		cont++;
		len--;
	}
	*aux = '\0';
	while (cont-- > 0)
		aux--;
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	int			i;
	int			j;
	char		*aux;
	char		*bufaux;

	i = 0;
	bufaux = NULL;
	if (!buf || buf[i] == '\0') //-----LEAK
	{
		if (!buf)
			buf = malloc(BUFFER_SIZE + 1); //----LEAK
		if (!buf)
			return  (NULL);
		j = read(fd, buf, BUFFER_SIZE);
		if (j <= 0 || BUFFER_SIZE == 0)
		{
			free(buf); //-----LEAK
			buf = 0;
			return (NULL);
		}
		buf[j] = '\0'; //-----LEAK
	}
	else
		j = ft_strlen(buf);
	while (buf[i] != '\n' && buf[i] != '\0' && j > 0)
	{
		i++;
		if (buf[i] == '\0')
		{
			if (!bufaux)
			{
				bufaux = malloc(BUFFER_SIZE); //-----LEAK
				if (!bufaux)
				{
					free(buf);
					buf = 0;
					return (NULL);
				}
			}
			bufaux = ft_strjoin(bufaux, buf); //-----LEAK
			j = read(fd, buf, BUFFER_SIZE);
			if (j == -1)
			{
				free(buf);
				buf = 0;
				return (NULL);
			}
			buf[j + 1] = '\0';
			i = 0;
		}
	}
	i++;
	if (!bufaux)
	{
		bufaux = malloc(i); //-----LEAK
		if (!bufaux)
		{
			free(buf);
			buf = 0;
			return (NULL);
		}
		bufaux = ft_substr(buf, 0, i);
	}
	else
	{
		char    *subbuf; //-----CAMBIA ESTO DE SITIO ZORRA
		subbuf = ft_substr(buf, 0, i);
		bufaux = ft_strjoin(bufaux, subbuf);
		free(subbuf);
		subbuf = 0;
	}
	int k = 0; //-----ESTO TAMBIEN
	aux = malloc(ft_strlen(buf) + 1);
	if (!aux)
	{
		free(buf);
		buf = 0;
		return (NULL);
	}
	while (buf[k] != '\0')
	{
		aux[k] = buf[k];
		k++;
	}
	aux[k]  = '\0';
	free(buf);
	buf = 0;
	buf = malloc(j - i + 1); //-----LEAK
	if (!buf)
		return (NULL);
	buf = ft_substr(aux, i, j - i + 1); //-----LEAK
	free(aux);
	aux = 0;
	return (bufaux);
}

void leaks()
{
	system("leaks -q a.out");
}

/*int	main()
{
	char	*s;
	int fd = open("pruebaDOS.txt", O_RDONLY);
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
	//printf("%s", get_next_line(fd));
	atexit(leaks);
	return (0);
}*/

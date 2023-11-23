/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:37:40 by saragar2          #+#    #+#             */
/*   Updated: 2023/11/23 18:30:55 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (*s != '\0')
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		size;

	if (!s2)
		return (NULL);
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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*aux;
	size_t	cont;

	cont = 0;
	if (start < 0 || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		aux = malloc(ft_strlen(s) - start + 1);
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

char	*createbuf(int fd, char *buf, int i)
{
	int	j;

	j = 0;
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
	return (buf);
}

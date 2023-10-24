#include <unistd.h>

ssize_t	len;
char	*buf[1024];
size_t	cont;
int	i;

cont = 1024;
i = 0;
len = read(fd, buf, cont);
while (buf[i] != '\n')
{
	while (i <= len && buf[i] != '\n')
		i++;
	if (buf[i] != '\n')
		len += read(fd, buf, cont);
}
strlcpy(aux, buf, i);

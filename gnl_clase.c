#include <unistd.h>
#include <string.h>

char *get_next_line(int fd)
{
	static ssize_t	len;
	char			buf[1024];
	static int		i;
	char			aux;

	len = 0;
	i = 0;
	len += read(fd, buf, sizeof(buf));
	// ------CALCULO DE LA LONGITUD DE LA LINEA
	while (buf[i] != '\n')
	{
		while (i <= len && buf[i] != '\n')
			i++;
		if (buf[i] != '\n')
			len += read(fd, buf, cont);
	}
	// ------COPIA DE LA STRING EN AUX
	aux = malloc(sizeof(char) * i);
	if (!aux)
		return (NULL);
	strlcpy(aux, buf, i);
	return (aux);
}

//---------POSIBLES CASOS DE ERROR
//--llega al final -> NULL
//--cualquier error -> NULL
//--se cambia en las llamadas el fd (sin haber terminado el archivo)-> error
//--archivo binario -> error

#include "struct_cub3d.h"

int	ft_err(char *errmsg)
{
	int	i;

	i = 0;
	while (errmsg[i])
	{
		write(2, &errmsg[i], 1);
		i++;
	}
	return (-1);
}


int	ft_tablength(char **tchoup)
{
	int	i;

	i = 0;
	if (!tchoup)
		return (-1);
	while (tchoup[i])
		i++;
	return (i);
}


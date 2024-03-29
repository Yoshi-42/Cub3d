/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:18:41 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 16:33:57 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_maxlen(char **map)
{
	int	l;
	int	i;

	l = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > l)
			l = ft_strlen(map[i]);
		i++;
	}
	return (l);
}

void	m_line(char **line, int fd, int *i)
{
	if (*line != NULL)
		free(*line);
	*line = NULL;
	*line = get_next_line(fd);
	*i = *i + 1;
}

void	m_line_map(char **line, int fd, int *i, char **map)
{
	map[*i] = ft_strdup(*line);
	m_line(line, fd, i);
}

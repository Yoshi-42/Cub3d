/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:07:42 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/23 15:30:32 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

int	ft_fill_infos2(char **placeholder, char *line)
{
	int		i;
	char	**temp;

	i = 0;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	temp = ft_split(line, ' ');
	if (*placeholder != NULL || !temp || ft_tablength(temp) == -1
		|| ft_tablength(temp) != 2)
		return (-1);
	*placeholder = ft_strdup(temp[1]);
	while (temp[i] != NULL)
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	return (0);
}

int	verif_parameters(char *line, t_map *map)
{
	int	err;

	err = 0;
	if (ft_strncmp(line, "NO", 2) == 0)
		err += ft_fill_infos2((&map->p_imgs[0]), line);
	else if (ft_strncmp(line, "SO", 2) == 0)
		err += ft_fill_infos2((&map->p_imgs[1]), line);
	else if (ft_strncmp(line, "WE", 2) == 0)
		err += ft_fill_infos2((&map->p_imgs[2]), line);
	else if (ft_strncmp(line, "EA", 2) == 0)
		err += ft_fill_infos2((&map->p_imgs[3]), line);
	else if (ft_strncmp(line, "F", 1) == 0)
		err += ft_fill_infos2((&map->p_imgs[4]), line);
	else if (ft_strncmp(line, "C", 1) == 0)
		err += ft_fill_infos2((&map->p_imgs[5]), line);
	if (err < 0)
		return (ft_err("error: Invalid config file\n"));
	return (0);
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

int	ft_check_startmap(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i] != '\n' && line [i] != '\0')
	{
		if ((line[i] != ' ') && (line[i] != '1') && (line[i] != '0'))
			return (-1);
		i++;
	}
	if (i == 0)
		return (-1);
	return (0);
}

int	first_parse(int fd, t_map *map, int nbline)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL && ft_check_startmap(line) == -1)
	{
		if (verif_parameters(line, map) < 0)
			return (-1);
		m_line(&line, fd, &i);
		while (line != NULL && line[0] == '\n')
			m_line(&line, fd, &i);
	}
	if (line != NULL)
		map->map = malloc(sizeof(char *) * (nbline - i + 1));
	else 
		return (-1);
	i = 0;
	while (line != NULL)
	{
		m_line_map(&line, fd, &i, map->map);
	}
	map->map[i] = NULL;
	return (0);
}

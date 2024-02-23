/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:59:17 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/23 11:04:40 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

int	ft_check_extension(char *map_name)
{
	int			i;
	int			j;
	static char	extension[] = {".cub"};

	i = 0;
	j = 0;
	if (!map_name || ft_strlen(map_name) < 4)
		return (-1);
	while (map_name[i] && i < (ft_strlen(map_name) - 4))
		i++;
	while (map_name[i] && extension[j])
	{
		if (map_name[i] != extension[j])
			return (-1);
		i++;
		j++;
	}
	return (0);
}

int	ft_nblines(char *file)
{
	int		i;
	int		fd;
	char	buff;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	while (read(fd, &buff, 1))
		if (buff == '\n')
			i++;
	i++;
	close(fd);
	return (i);
}

int	ft_init(t_map *map)
{
	int		i;

	i = 0;
	map->p_imgs = malloc(sizeof(char *) * 7);
	if (!map->p_imgs)
		return (-1);
	while (i < 6)
	{
		map->p_imgs[i] = NULL;
		i++;
	}
	map->p_imgs[i] = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	return (0);
}

int	ft_open_map(char *file)
{
	int	fd;

	fd = -1;
	if (ft_check_extension(file) == -1)
	{
		return (fd);
	}
	fd = open(file, O_RDONLY);
	return (fd);
}

int	ft_parsing(char *file, t_map *map)
{
	int	nbline;
	int	fd;

	if (ft_check_extension(file) == -1)
		return (ft_err("error: Invalid file extension\n"));
	nbline = ft_nblines(file);
	if (nbline <= 0)
		return (ft_err("error: Invalid file\n"));
	if (ft_init(map) == -1)
		return (ft_err("error: Failed initialisation\n"));
	fd = ft_open_map(file);
	if (fd < 0)
		return (ft_err("error\n"));
	if (first_parse(fd, map, nbline) == -1)
		return (ft_err("error: Cannot parse map\n"));
	close(fd);
	if (ft_split_colors(map) != 0)
		return (ft_err("error : Invalid file format\n"));
	return (0);
}

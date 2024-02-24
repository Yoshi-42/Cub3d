/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:02:39 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 16:02:02 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

char	**ft_squaremap(char **map, int maxline)
{
	char		**newmap;
	t_ipoint	ij;

	ij.i = 0;
	newmap = malloc(sizeof(char *) * (ft_tablength(map) + 1));
	if (!newmap)
		return (NULL);
	while (map[ij.i])
	{
		newmap[ij.i] = malloc(sizeof(char) * (maxline + 1));
		if (!newmap[ij.i])
			return (NULL);
		ij.j = 0;
		while (map[ij.i][ij.j])
		{
			newmap[ij.i][ij.j] = map[ij.i][ij.j];
			if (map[ij.i][ij.j] == ' ' || map[ij.i][ij.j] == '\n')
				newmap[ij.i][ij.j] = '8';
			ij.j++;
		}
		newmap[ij.i][ij.j] = '\0';
		ij.i++;
	}
	newmap[ij.i] = NULL;
	return (newmap);
}

int	ft_check_walls(char **map, int x, int y, int *isExit)
{
	if (*isExit > 0)
		return (-1);
	if (map[y][x] == '8' || map[y][x] == '\0' || map[y][x] == ' ')
	{
		*isExit = *isExit + 1;
		return (-1);
	}
	if (map[y][x] != '1' && map[y][x] != 'v')
	{
		map[y][x] = 'v';
		if (map[y + 1] != NULL)
			ft_check_walls(map, x, y + 1, isExit);
		else
			*isExit = *isExit + 1;
		ft_check_walls(map, x + 1, y, isExit);
		if (y > 0)
			ft_check_walls(map, x, y - 1, isExit);
		else
			*isExit = *isExit + 1;
		if (x > 0)
			ft_check_walls(map, x - 1, y, isExit);
		else
			*isExit = *isExit + 1;
	}
	return (0);
}

int	simple_map_check(t_map *map)
{
	if (map->imgN.img == NULL || map->imgS.img == NULL
		|| map->imgE.img == NULL || map->imgO.img == NULL)
		return (-1);
	if (map->floor_color < 0 || map->ceiling_color < 0)
		return (-1);
	if (map->map == NULL)
		return (-1);
	return (0);
}

int	checkmap_value(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != '8' &&
				map[i][j] != 'N' && map[i][j] != 'S' &&
				map[i][j] != 'E' && map[i][j] != 'O')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_map_vailable(t_map *map)
{
	char		**checkmap;
	int			is_exit;
	t_point		start_pos;

	if (simple_map_check(map) < 0)
		return (-1);
	checkmap = ft_squaremap(map->map, ft_maxlen(map->map));
	if (checkmap_value(checkmap) < 0)
		return (ft_err("error: Config map: Forbidden characters\n"));
	start_pos = find_player(checkmap);
	if (start_pos.x < 0)
	{
		free_array(checkmap);
		return (ft_err("error: Invalid player\n"));
	}
	is_exit = 0;
	ft_check_walls(checkmap, start_pos.y, start_pos.x, &is_exit);
	free_array(checkmap);
	if (is_exit > 0)
		return (ft_err("error: Map not closed by walls\n"));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:53 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 17:03:24 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	if (t < 0 || r < 0 || g < 0 || b < 0)
		return (-1);
	if (t > 255 || r > 255 || g > 255 || b > 255)
		return (-1);
	return (t << 24 | r << 16 | g << 8 | b);
}

int	char_to_rgb(int t, char *r, char *g, char *b)
{
	t_point	tr;
	t_point	gb;

	tr.y = ft_atoi(r);
	gb.x = ft_atoi(g);
	gb.y = ft_atoi(b);
	tr.x = t;
	if (tr.x < 0 || tr.y < 0 || gb.x < 0 || gb.y < 0)
		return (-1);
	if (tr.x > 255 || tr.y > 255 || gb.x > 255 || gb.y > 255)
		return (-1);
	return ((int)tr.x << 24 | (int)tr.y << 16 | (int)gb.x << 8 | (int)gb.y);
}

int	ft_split_colors(t_map *map)
{
	char	**f_temp;
	char	**c_temp;

	if (map->p_img_s[4] == NULL || map->p_img_s[5] == NULL)
		return (-1);
	f_temp = ft_split(map->p_img_s[4], ',');
	c_temp = ft_split(map->p_img_s[5], ',');
	if (f_temp == NULL || c_temp == NULL)
		return (-1);
	if (ft_tablength(f_temp) != 3 || ft_tablength(c_temp) != 3)
	{
		free_array(f_temp);
		free_array(c_temp);
		return (-1);
	}
	map->floor_color = char_to_rgb(1, f_temp[0], f_temp[1], f_temp[2]);
	map->ceiling_color = char_to_rgb(1, c_temp[0], c_temp[1], c_temp[2]);
	free_array(f_temp);
	free_array(c_temp);
	if (map->floor_color < 0 || map->ceiling_color < 0)
		return (-1);
	return (0);
}

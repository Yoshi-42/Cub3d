/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:15:56 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/23 11:18:28 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"
#include <string.h>
#include <stdio.h>

char	*texture_nord = "textures/eagle.xpm";
char	*texture_sud = "textures/greystone.xpm";
char	*texture_ouest = "textures/purplestone.xpm";
char	*texture_est = "textures/red.xpm";

int	one_tex(void *mlx, char *tex_text, t_data *img)
{
	img->img = mlx_xpm_file_to_image(mlx, tex_text, &img->width, &img->height);
	if (img->img ==NULL)
		return (-1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (0);
	
}

int    init_tex(t_vars *vars, char **tex_file)
{
	if (one_tex(vars->mlx, tex_file[0], &vars->m_map.imgN) == -1)
		return (-1);
	if (one_tex(vars->mlx, tex_file[1], &vars->m_map.imgS) == -1)
		return (-1);
	if (one_tex(vars->mlx, tex_file[2], &vars->m_map.imgO) == -1)
		return (-1);
	if (one_tex(vars->mlx, tex_file[3], &vars->m_map.imgE) == -1)
		return (-1);
	return (0);
}

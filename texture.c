/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:15:56 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 17:07:21 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"
#include <string.h>
#include <stdio.h>

int	one_tex(void *mlx, char *tex_text, t_data *img)
{
	img->img = mlx_xpm_file_to_image(mlx, tex_text, &img->width, &img->height);
	if (img->img == NULL)
		return (-1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (0);
}

int	init_tex(t_vars *vars, char **tex_file)
{
	if (one_tex(vars->mlx, tex_file[0], &vars->m_map.img_n) == -1)
		return (-1);
	if (one_tex(vars->mlx, tex_file[1], &vars->m_map.img_s) == -1)
		return (-1);
	if (one_tex(vars->mlx, tex_file[2], &vars->m_map.img_o) == -1)
		return (-1);
	if (one_tex(vars->mlx, tex_file[3], &vars->m_map.img_e) == -1)
		return (-1);
	return (0);
}

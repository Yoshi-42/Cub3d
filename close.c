/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:02:55 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/22 18:07:47 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

int	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (-1);
}

void	delete_img(t_vars *vars)
{
	if (vars->m_map.imgN.img != NULL)
		mlx_destroy_image(vars->mlx, vars->m_map.imgN.img);
	if (vars->m_map.imgS.img != NULL)
		mlx_destroy_image(vars->mlx, vars->m_map.imgS.img);
	if (vars->m_map.imgO.img != NULL)
		mlx_destroy_image(vars->mlx, vars->m_map.imgO.img);
	if (vars->m_map.imgE.img != NULL)
		mlx_destroy_image(vars->mlx, vars->m_map.imgE.img);
	if (vars->img->img != NULL)
		mlx_destroy_image(vars->mlx, vars->img->img);
	free(vars->img);
}

int	close_everything(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->m_map.p_imgs != NULL)
	{
		while (i < 7)
		{
			if (vars->m_map.p_imgs[i] != NULL)
				free(vars->m_map.p_imgs[i]);
			i++;
		}
	}
	free_array(vars->m_map.map);
	delete_img(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:02:55 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 17:07:21 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

int	free_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	return (-1);
}

void	delete_img(t_vars *vars)
{
	if (vars->m_map.p_img_s[0] != NULL && vars->m_map.img_n.img != NULL)
		mlx_destroy_image(vars->mlx, vars->m_map.img_n.img);
	if (vars->m_map.p_img_s[0] != NULL && vars->m_map.img_s.img != NULL)
		mlx_destroy_image(vars->mlx, vars->m_map.img_s.img);
	if (vars->m_map.p_img_s[0] != NULL && vars->m_map.img_o.img != NULL)
		mlx_destroy_image(vars->mlx, vars->m_map.img_o.img);
	if (vars->m_map.p_img_s[0] != NULL && vars->m_map.img_e.img != NULL)
		mlx_destroy_image(vars->mlx, vars->m_map.img_e.img);
	if (vars->m_map.p_img_s[0] != NULL && vars->img->img != NULL)
		mlx_destroy_image(vars->mlx, vars->img->img);
	free(vars->img);
}

int	close_everything(t_vars *vars)
{
	int	i;

	free_array(vars->m_map.map);
	delete_img(vars);
	i = 0;
	if (vars->m_map.p_img_s != NULL)
	{
		while (i < 7)
		{
			if (vars->m_map.p_img_s[i] != NULL)
				free(vars->m_map.p_img_s[i]);
			i++;
		}
	}
	free(vars->m_map.p_img_s);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	return (0);
}

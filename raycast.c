/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:19:21 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 17:02:37 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

//lance le raycasting jusqu'a tomber sur la target 
//(ce qui permet de definir le rayon)
//Args {game} toute les variable du jeu (notamment la map)
//Args {ray} rayon que l'on va initialiser lors de ce lancer
//Args {sx} la colonne sur laquelle le rayon est lancer
void	raycasting(t_vars *game, t_ray *ray, int sx, char target)
{
	int		hit;

	hit = 0;
	init_ray(game, ray, sx);
	while (hit == 0)
	{
		if (ray->side_dist_xy.x < ray->side_dist_xy.y)
		{
			ray->side_dist_xy.x += ray->delta_dist_xy.x;
			ray->map_xy.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_xy.y += ray->delta_dist_xy.y;
			ray->map_xy.y += ray->step.y;
			ray->side = 1;
		}
		if (game->m_map.map[(int)ray->map_xy.x][(int)ray->map_xy.y] == target)
			hit = 1;
	}
}

void	display_wall(t_vars *vars)
{
	int		sx;
	t_ray	ray;

	sx = 0;
	while (sx < WIDTH)
	{
		raycasting(vars, &ray, sx, '1');
		draw_wall_col(vars, sx, &ray);
		sx++;
	}
}

int	update(t_vars *vars)
{
	player_movement(vars);
	display_wall(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

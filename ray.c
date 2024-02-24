/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:15:20 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 17:08:12 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

t_point	init_delta(t_point ray_dir_xy)
{
	t_point	delta_dist;

	delta_dist.x = fabs(1 / ray_dir_xy.x);
	delta_dist.y = fabs(1 / ray_dir_xy.y);
	return (delta_dist);
}

//on initialise le step c'est a dire la direction vers la prochaine case
// et le cote par lequelle le rayon va toucher 
void	init_side(t_vars *vars, t_ray *ray)
{
	if (ray->ray_dir_xy.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist_xy.x = (vars->p.pos.x - ray->map_xy.x)
			* ray->delta_dist_xy.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist_xy.x = (ray->map_xy.x + 1.0 - vars->p.pos.x)
			* ray->delta_dist_xy.x;
	}
	if (ray->ray_dir_xy.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist_xy.y = (vars->p.pos.y - ray->map_xy.y)
			* ray->delta_dist_xy.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist_xy.y = (ray->map_xy.y + 1.0 - vars->p.pos.y)
			* ray->delta_dist_xy.y;
	}
}

void	init_ray(t_vars *vars, t_ray *ray, int sx)
{
	double	camera_x;

	camera_x = (2 * sx / (double)WIDTH - 1);
	define_point(&ray->ray_dir_xy,
		vars->p.dir.x + vars->p.p_screen.x * camera_x,
		vars->p.dir.y + vars->p.p_screen.y * camera_x);
	define_point(&ray->map_xy, trunc(vars->p.pos.x), trunc(vars->p.pos.y));
	ray->delta_dist_xy = init_delta(ray->ray_dir_xy);
	init_side(vars, ray);
}

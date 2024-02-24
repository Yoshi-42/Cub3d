/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:15:20 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 16:17:53 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

t_point	init_delta(t_point rayDirXY)
{
	t_point	delta_dist;

	delta_dist.x = fabs(1 / rayDirXY.x);
	delta_dist.y = fabs(1 / rayDirXY.y);
	return (delta_dist);
}

//on initialise le step c'est a dire la direction vers la prochaine case
// et le cote par lequelle le rayon va toucher 
void	init_side(t_vars *vars, t_ray *ray)
{
	if (ray->rayDirXY.x < 0)
	{
		ray->step.x = -1;
		ray->sideDistXY.x = (vars->p.pos.x - ray->mapXY.x) * ray->deltaDistXY.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDistXY.x = (ray->mapXY.x + 1.0 - vars->p.pos.x)
			* ray->deltaDistXY.x;
	}
	if (ray->rayDirXY.y < 0)
	{
		ray->step.y = -1;
		ray->sideDistXY.y = (vars->p.pos.y - ray->mapXY.y) * ray->deltaDistXY.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDistXY.y = (ray->mapXY.y + 1.0 - vars->p.pos.y)
			* ray->deltaDistXY.y;
	}
}

void	init_ray(t_vars *vars, t_ray *ray, int sx)
{
	double	camera_x;

	camera_x = (2 * sx / (double)WIDTH - 1);
	define_point(&ray->rayDirXY,
		vars->p.dir.x + vars->p.p_screen.x * camera_x,
		vars->p.dir.y + vars->p.p_screen.y * camera_x);
	define_point(&ray->mapXY, trunc(vars->p.pos.x), trunc(vars->p.pos.y));
	ray->deltaDistXY = init_delta(ray->rayDirXY);
	init_side(vars, ray);
}

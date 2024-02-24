/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:19:46 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 16:32:45 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (((unsigned int)y % HEIGHT)
			* data->line_length + ((unsigned int)x % WIDTH)
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	define_tex(t_vars *vars, t_tex *tex, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->rayDirXY.x < 0)
			tex->tex = &vars->m_map.imgN;
		else
			tex->tex = &vars->m_map.imgS;
	}
	else
	{
		if (ray->rayDirXY.y < 0)
			tex->tex = &vars->m_map.imgO;
		else
			tex->tex = &vars->m_map.imgE;
	}
}

t_tex	find_coord_tex(t_vars *vars, t_ray *ray, int lineH)
{
	t_tex	tex;
	double	wall_x;

	define_tex(vars, &tex, ray);
	wall_x = vars->p.pos.x + (ray->sideDistXY.y - ray->deltaDistXY.y)
		* ray->rayDirXY.x;
	if (ray->side == 0)
		wall_x = vars->p.pos.y + (ray->sideDistXY.x - ray->deltaDistXY.x)
			* ray->rayDirXY.y;
	wall_x -= floor(wall_x);
	tex.tex_xy.x = (int)(wall_x * (double)tex.tex->width);
	tex.step = 1.0 * tex.tex->height / lineH ;
	tex.tex_pos = ((-lineH / 2 + HEIGHT / 2) - HEIGHT / 2 + lineH / 2)
		* tex.step;
	if ((-lineH / 2 + HEIGHT / 2) < 0)
		tex.tex_pos = (-HEIGHT / 2 + lineH / 2) * tex.step;
	return (tex);
}

void	draw_wall_face(t_vars *vars, int _x, int _y, t_tex *tex)
{
	int	color;

	tex->tex_pos += tex->step;
	tex->tex_xy.y = (int)tex->tex_pos & (tex->tex->height - 1);
	color = *(int *)(tex->tex->addr + ((int)tex->tex_xy.y
				* tex->tex->line_length + (int)tex->tex_xy.x
				* (tex->tex->bits_per_pixel / 8)));
	my_mlx_pixel_put(vars->img, _x, _y, color);
}

void	draw_wall_col(t_vars *vars, int sx, t_ray *ray)
{
	int		line_h;
	t_point	draw;
	t_tex	tex;
	int		i;

	line_h = (int)(HEIGHT / (ray->sideDistXY.y - ray->deltaDistXY.y));
	if (ray->side == 0)
		line_h = (int)(HEIGHT / (ray->sideDistXY.x - ray->deltaDistXY.x));
	define_point(&draw, -line_h / 2 + HEIGHT / 2, line_h / 2 + HEIGHT / 2);
	i = 0;
	tex = find_coord_tex(vars, ray, line_h);
	while (i < HEIGHT)
	{
		if (i < draw.x)
			my_mlx_pixel_put(vars->img, sx, i, vars->m_map.floor_color);
		else if (i > draw.y)
			my_mlx_pixel_put(vars->img, sx, i, vars->m_map.ceiling_color);
		else
			draw_wall_face(vars, sx, i, &tex);
		i++;
	}
}

int	update(t_vars *vars)
{
	player_movement(vars);
	display_wall(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

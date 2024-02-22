#include "struct_cub3d.h"

typedef struct s_texture
{
	t_data	*tex;
	t_point	texXY;
	double	texPos;
	double	step; 
}	t_tex;

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
	if (ray->side == 0) //NS
		if (ray->rayDirXY.x < 0)
			tex->tex = &vars->m_map.imgN;
		else
			tex->tex = &vars->m_map.imgS;
	else
		if (ray->rayDirXY.y < 0)
			tex->tex = &vars->m_map.imgO;
		else
			tex->tex = &vars->m_map.imgE;
}

t_tex	find_coord_tex(t_vars *vars, t_ray *ray, int lineH)
{
	t_tex	tex;
	double	wallX;

	define_tex(vars, &tex, ray);
	wallX = vars->p.pos.x + (ray->sideDistXY.y - ray->deltaDistXY.y) * ray->rayDirXY.x;
	if(ray->side == 0)
		wallX = vars->p.pos.y + (ray->sideDistXY.x - ray->deltaDistXY.x) * ray->rayDirXY.y;
	wallX -= floor(wallX);
	tex.texXY.x = (int)(wallX * (double)tex.tex->width);
	if ((ray->side == 0 && ray->rayDirXY.x > 0) || (ray->side == 1 && ray->rayDirXY.y < 0))
		tex.texXY.x = tex.tex->width - tex.texXY.x -1;
	tex.step = 1.0 * tex.tex->height / lineH;
	tex.texPos = ((-lineH / 2 + HEIGHT / 2) - HEIGHT / 2 + lineH / 2) * tex.step;
	return (tex);
}

void	draw_wall_face(t_vars *vars, int _x, int _y, t_tex *tex)
{
	int	color;
	tex->texXY.y = (int)tex->texPos & (tex->tex->height - 1);
	tex->texPos += tex->step;
	color = *(int*)(tex->tex->addr + ((int)tex->texXY.y * tex->tex->line_length + (int)tex->texXY.x * (tex->tex->bits_per_pixel / 8)));
	my_mlx_pixel_put(vars->img, _x, _y, color);
}

void	draw_wall_col(t_vars *vars, int sx, t_ray *ray)
{
	int		lineH;
	t_point	draw;
	t_tex	tex;
	int		i;

	lineH = (int) (HEIGHT / (ray->sideDistXY.y - ray->deltaDistXY.y));
	if (ray->side == 0)
		lineH = (int) (HEIGHT / (ray->sideDistXY.x - ray->deltaDistXY.x));
	define_point(&draw, -lineH / 2 + HEIGHT / 2, lineH / 2 + HEIGHT / 2);
	i = 0;
	tex = find_coord_tex(vars, ray, lineH);
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
	//mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	
	return (0);
}

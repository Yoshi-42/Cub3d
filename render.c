#include "struct_cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (((unsigned int)y % HEIGHT)
			* data->line_length + ((unsigned int)x % WIDTH)
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall_face(t_vars *vars, t_ray *ray, t_point XY)
{
	if (ray->side == 0) //NS
		if(ray->rayDirXY.x < 0)
			my_mlx_pixel_put(vars->img, XY.x, XY.y, create_trgb(0, 0, 204, 203));//N
		else
			my_mlx_pixel_put(vars->img, XY.x, XY.y, create_trgb(0, 115, 194, 251));//S
	else //EW
		if(ray->rayDirXY.y < 0)
			my_mlx_pixel_put(vars->img, XY.x, XY.y, create_trgb(0, 96, 80, 220));//O
		else
			my_mlx_pixel_put(vars->img, XY.x, XY.y, create_trgb(0, 0, 255 ,255));//E
}

void	draw_wall_col(t_vars *vars, int sx, t_ray *ray)
{
	int	lineH;
	t_point	draw;
	t_point XY;
	int	i;

	lineH = (int) (HEIGHT / (ray->sideDistXY.y - ray->deltaDistXY.y));
	if (ray->side == 0)
		lineH = (int) (HEIGHT / (ray->sideDistXY.x - ray->deltaDistXY.x));
	define_point(&draw, -lineH / 2 + HEIGHT / 2, lineH / 2 + HEIGHT / 2);
	i = 0;
	while (i < HEIGHT)
	{
		define_point(&XY, sx, i);
		if (i < draw.x)
			my_mlx_pixel_put(vars->img, sx, i, create_trgb(0, 255, 0 ,0));
		else if (i > draw.y)
			my_mlx_pixel_put(vars->img, sx, i, create_trgb(0, 0, 255 ,0));
		else
			draw_wall_face(vars, ray, XY);
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

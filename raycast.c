#include "struct_cub3d.h"

//lance le raycasting jusqu'a tomber sur la target (ce qui permet de definir le rayon)
//Args {game} toute les variable du jeu (notamment la map)
//Args {ray} rayon que l'on va initialiser lors de ce lancer
//Args {sx} la colonne sur laquelle le rayon est lancer
void	raycasting(t_vars *game, t_ray *ray, int sx, char target)
{
	int		hit;

	hit = 0;
	init_ray(game, ray, sx); // on initialise la base du rayon
	while (hit == 0)
	{
		if (ray->sideDistXY.x < ray->sideDistXY.y)
		{
			ray->sideDistXY.x += ray->deltaDistXY.x;
			ray->mapXY.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sideDistXY.y += ray->deltaDistXY.y;
			ray->mapXY.y += ray->step.y;
			ray->side = 1;
		}
		if (game->map[(int)ray->mapXY.x][(int)ray->mapXY.y] == target)
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

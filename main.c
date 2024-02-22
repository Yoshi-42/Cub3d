#include "struct_cub3d.h"

/*char *_map[] = {
"1111111111111111111",
"1001001001001001001",
"1001001001001001001",
"1001001001001001001",
"1001001000001001001",
"100000000O000000001",
"1000011111111000001",
"1111000000000001111",
"1000000101010000001",
"1111111111111111111",
NULL
};*/

void define_point (t_point *p, double _x , double _y)
{
	p->x = _x;
	p->y = _y;
}

t_player initPlayer(char orientation, t_point position)
{
	t_player p;

	p.pos.x = position.x;
	p.pos.y = position.y;
	if(orientation == 'O')
	{
		define_point(&(p.dir), 0, -1);
		define_point(&(p.p_screen), -0.66, 0);
	}
	else if (orientation == 'E')
	{
		define_point(&(p.dir), 0, 1);
		define_point(&(p.p_screen), 0.66, 0);
	}
	else if (orientation == 'N')
	{
		define_point(&(p.dir), -1, 0);
		define_point(&(p.p_screen), 0, 0.66);
	}
	else if (orientation == 'S')
	{
		define_point(&(p.dir), 1, 0);
		define_point(&(p.p_screen), 0, -0.66);
	}	
	define_point(&p.move, 0, 0);
	p.rotate = 0;
	return (p);
}

void print_player(t_player p)
{
	printf("le player :\n");
	printf("pos : %fx %fy\n",p.pos.x, p.pos.y);
	printf("dir : %fx %fy\n",p.dir.x, p.dir.y);
	printf("screen : %fx %fy\n",p.p_screen.x, p.p_screen.y);
}

t_point find_player(char **map)
{
	int		i;
	int		j;
	t_point pt;

	i = 0;
	define_point(&pt, -1 ,-1);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != 0)
		{
			if((map[i][j] == 'N' || map[i][j] == 'S') || map[i][j] == 'O' || map[i][j] == 'E')
			{
				if (pt.x < 0)
					define_point(&pt, i, j);
				else
				{
					define_point(&pt, -1 ,-1);
					return (pt);
				}
			}
			j++;
		}
		i++;
	}
	return (pt);
}

char find_orientation(t_point position, char **map)
{
	return (map[(int)position.x][(int)position.y]);
}

void	set_img(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "CUB3D!");
	vars->img = malloc(sizeof(t_data));
	vars->img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&(vars->img->bits_per_pixel), &(vars->img->line_length),
			&(vars->img->endian));
}

int main(int argc, char *argv[])
{
	t_vars vars;

	if (argc == 2)
	{
		if(ft_parsing(argv[1], &vars.m_map) < 0)//on parse la map
			return (0);		
		set_img(&vars);
		if(init_tex(&vars, vars.m_map.p_imgs) < 0)
		{
			close_everything(&vars);
			return (ft_err("Fatal: Error loading textures\n"));
		}
		if (is_map_vailable(&vars.m_map) < 0 )
			return (close_everything(&vars));
		vars.p = initPlayer(find_orientation(find_player(vars.m_map.map), vars.m_map.map), find_player(vars.m_map.map));
		input_manag(&vars);
		mlx_loop_hook(vars.mlx, update, (void *)&vars);
		mlx_loop(vars.mlx);
	}
	return (0);
}


/*
int	main(int argc, char *argv[])
{
	t_vars	vars;

		// vars.map = get_map_3(argv[1]);
		// if (vars.map == NULL)
		// 	return (0);
		// vars.grid = grid_constructor(vars.map, 35, WIDTH, HEIGHT);
		// if (true_pts(&(vars.grid)) != 0)
		// 	return (close_everything(&vars));
		// isometric_projection(&(vars.grid));
		// center_grid(&(vars.grid));
		// vars.grid->origin = set_origin(vars.grid);
		// set_img(&vars);
		// vars.input = NULL;
		// input_manag(&vars);
		// mlx_loop_hook(vars.mlx, m_render, &vars);
		// mlx_loop(vars.mlx);
}
*/


// ./cub3D maps/bad/map_missing.cub   seg
// ./cub3D maps/bad/textures_missing.cub seg
// ./cub3D maps/bad/textures_none.cub seg
// ./cub3D maps/bad/map_too_small.cub seg
// 111
// 111
// maps/bad/wall_hole_north.cub seg auqnd on se retourne

// ./cub3D maps/bad/wall_hole_south.cub seg
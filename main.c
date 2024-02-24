/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:20:26 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 17:03:24 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

t_player	init_player(char orientation, t_point position)
{
	t_player	p;

	define_point(&p.pos, position.x, position.y);
	define_point(&p.dir, 0, 1);
	define_point(&p.p_screen, 0.66, 0);
	if (orientation == 'N' || orientation == 'S')
	{
		revers_pt(&p.dir);
		revers_pt(&p.p_screen);
	}
	if (orientation == 'N' || orientation == 'O')
		neg_pt(&p.dir);
	if (orientation == 'O' || orientation == 'S')
		neg_pt(&p.p_screen);
	define_point(&p.move, 0, 0);
	p.rotate = 0;
	return (p);
}
	/*if (orientation == 'O')
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
	}*/

t_point	find_player(char **map)
{
	int				i;
	int				j;
	t_point			pt;

	i = 0;
	define_point(&pt, -1, -1);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != 0)
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S') ||
				map[i][j] == 'O' || map[i][j] == 'E')
			{
				if (pt.x < 0)
					define_point(&pt, i, j);
				else
					return (create_point(-1, -1));
			}
			j++;
		}
		i++;
	}
	return (pt);
}

char	find_orientation(t_point position, char **map)
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

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc == 2)
	{
		if (ft_parsing(argv[1], &vars.m_map) < 0)
		{
			free_array(vars.m_map.p_img_s);
			free_array(vars.m_map.map);
			return (0);
		}
		set_img(&vars);
		if (init_tex(&vars, vars.m_map.p_img_s) < 0)
		{
			close_everything(&vars);
			return (ft_err("Fatal: Error loading textures\n"));
		}
		if (is_map_vailable(&vars.m_map) < 0)
			return (close_everything(&vars));
		vars.p = init_player(find_orientation(find_player(vars.m_map.map),
					vars.m_map.map), find_player(vars.m_map.map));
		input_manag(&vars);
		mlx_loop_hook(vars.mlx, update, (void *)&vars);
		mlx_loop(vars.mlx);
	}
	return (0);
}

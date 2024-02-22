/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:11:21 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/22 18:20:07 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

void	player_move(int keycode, t_vars *vars, double movement)
{
	if (keycode == KEY_Z)
		vars->p.move.y = movement;
	if (keycode == KEY_S)
		vars->p.move.y = movement * -1;
	if (keycode == KEY_A)
		vars->p.move.x = movement * -1;
	if (keycode == KEY_D)
		vars->p.move.x = movement;
}

void	player_rotation(int keycode, t_vars *vars, double movement)
{
	if (keycode == KEY_RIGHT)
		vars->p.rotate = movement * -1;
	if (keycode == KEY_LEFT)
		vars->p.rotate = movement;
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
	{
		close_everything(vars);
		exit(0);
	}
	player_move(keycode, vars, 1);
	player_rotation(keycode, vars, 1);
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	player_move(keycode, vars, 0);
	player_rotation(keycode, vars, 0);
	return (0);
}

int	input_manag(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1, &key_press, vars);
	mlx_hook(vars->win, 3, 10, &key_release, vars);
	return (0);
}

int	move_posible(t_vars *vars, t_point pos)
{
	t_point	n_pos_xy;

	n_pos_xy.x = trunc(pos.x);
	n_pos_xy.y = trunc(pos.y);
	if (vars->m_map.map[(int)n_pos_xy.x][(int)n_pos_xy.y] == '1')
		return (-1);
	return (0);
}

void	rotate(t_vars *vars, double speed)
{
	t_point	save_x;

	speed = speed * vars->p.rotate;
	save_x.x = vars->p.dir.x;
	vars->p.dir.x = vars->p.dir.x * cos(speed) - vars->p.dir.y * sin(speed);
	vars->p.dir.y = save_x.x * sin(speed) + vars->p.dir.y * cos(speed);
	save_x.y = vars->p.p_screen.x;
	vars->p.p_screen.x = vars->p.p_screen.x * cos(speed)
		- vars->p.p_screen.y * sin(speed);
	vars->p.p_screen.y = save_x.y * sin(speed)
		+ vars->p.p_screen.y * cos(speed);
}

void	player_movement(t_vars *vars)
{
	double	speed;
	t_point	old_pos;

	speed = 0.09;
	define_point(&old_pos, vars->p.pos.x, vars->p.pos.y);
	if (vars->p.move.y != 0)
		define_point(&vars->p.pos,
			vars->p.pos.x + vars->p.dir.x * vars->p.move.y * speed,
			vars->p.pos.y + vars->p.dir.y * vars->p.move.y * speed);
	if (move_posible(vars, vars->p.pos) == -1)
		define_point(&vars->p.pos, old_pos.x, old_pos.y);
	define_point(&old_pos, vars->p.pos.x, vars->p.pos.y);
	if (vars->p.move.x != 0)
		define_point(&vars->p.pos,
			vars->p.pos.x + vars->p.dir.y * vars->p.move.x * speed,
			vars->p.pos.y + vars->p.dir.x * -vars->p.move.x * speed);
	if (move_posible(vars, vars->p.pos) == -1)
		define_point(&vars->p.pos, old_pos.x, old_pos.y);
	if (vars->p.rotate != 0)
		rotate(vars, speed);
}

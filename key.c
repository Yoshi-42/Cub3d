/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:05:14 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 16:07:05 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

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

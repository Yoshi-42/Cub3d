/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:15:32 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 16:15:33 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

void	revers_pt(t_point *pt)
{
	double	_x;

	_x = pt->x;
	pt->x = pt->y;
	pt->y = _x;
}

void	neg_pt(t_point *pt)
{
	pt->x *= -1;
	pt->y *= -1;
}

void	define_point(t_point *p, double _x, double _y)
{
	p->x = _x;
	p->y = _y;
}

t_point	create_point(double _x, double _y)
{
	t_point	pt;

	pt.x = _x;
	pt.y = _y;
	return (pt);
}

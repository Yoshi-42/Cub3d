/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:04:20 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 16:04:39 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_cub3d.h"

void	print_player(t_player p)
{
	printf("le player :\n");
	printf("pos : %fx %fy\n", p.pos.x, p.pos.y);
	printf("dir : %fx %fy\n", p.dir.x, p.dir.y);
	printf("screen : %fx %fy\n", p.p_screen.x, p.p_screen.y);
}

void	ft_debug_map(char **map)
{
	int		i;

	i = 0;
	printf("\nMAMAAAAAP :\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	print_char_array(char **array)
{
	int	i;

	i = 0;
	printf("map:\n");
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
	printf("map Fin:\n");
}

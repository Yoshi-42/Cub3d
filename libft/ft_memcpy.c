/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:22:12 by bgonon            #+#    #+#             */
/*   Updated: 2023/03/08 11:20:26 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*destination;
	char	*source;

	if (!dest && !src)
		return (0);
	i = 0;
	destination = (char *) dest;
	source = (char *) src;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dest);
}

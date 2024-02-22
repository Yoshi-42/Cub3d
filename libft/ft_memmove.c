/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:11:39 by bgonon            #+#    #+#             */
/*   Updated: 2023/03/08 11:26:32 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *) dest;
	b = (unsigned char *) src;
	if (!dest && !src)
		return (0);
	if (a > b)
	{
		while (i < n)
		{
			a[n - 1] = b[n - 1];
			n--;
		}
	}
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dest);
}

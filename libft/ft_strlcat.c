/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:14:28 by bgonon            #+#    #+#             */
/*   Updated: 2023/03/08 10:57:06 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;

	if ((!dst || !src) && !size)
		return (0);
	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	dst_len = i;
	while (i + 1 < size && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (dst_len < size)
		dst[i] = '\0';
	return (dst_len + ft_strlen(src));
}

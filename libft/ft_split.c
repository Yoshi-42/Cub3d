/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 09:40:14 by bgonon            #+#    #+#             */
/*   Updated: 2023/09/14 12:10:28 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mallen(const char *src, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] != c && (i == 0 || src [i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	if (s && c)
		dest = (char **)malloc (sizeof(char *) * (ft_mallen(s, c) + 1));
	if (!dest || !s)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (start != i)
			dest[j++] = ft_substr(s, start, i - start);
	}
	dest[j] = 0;
	return (dest);
}

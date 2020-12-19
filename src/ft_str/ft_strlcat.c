/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:30:34 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/25 18:37:15 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static size_t	retlen(char *dst, size_t dstsize)
{
	size_t	dstlen;

	dstlen = 0;
	while (*dst && dstsize > 0)
	{
		dstlen++;
		dst++;
		dstsize--;
	}
	return (dstlen);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		iter;
	int		dstlen;
	size_t	dst_retlen;

	iter = 0;
	dstlen = (int)ft_strlen((const char*)dst);
	dst_retlen = retlen(dst, dstsize);
	while (src[iter] && iter + dstlen + 1 < (int)dstsize)
	{
		dst[dstlen + iter] = src[iter];
		iter++;
	}
	dst[dstlen + iter] = '\0';
	return (dst_retlen + ft_strlen(src));
}

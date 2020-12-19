/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:06:00 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/25 18:32:13 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*ptr;
	int		n;

	n = (int)len;
	ptr = dst;
	while (*src && n--)
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	while (n > 0)
	{
		*ptr = '\0';
		ptr++;
		n--;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:13:22 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/25 18:43:24 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char*)s;
	if (*str == (char)c)
		return (str);
	while (*str)
	{
		str++;
		if (*str == (char)c)
			return (str);
	}
	return (NULL);
}

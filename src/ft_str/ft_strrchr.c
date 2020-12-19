/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 23:35:50 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/25 18:45:16 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*beg_ptr;

	beg_ptr = (char*)s;
	while (*s)
		s++;
	if ((char)c == '\0' && *s == '\0')
		return ((char*)s);
	s--;
	while (*s && s >= beg_ptr)
	{
		if (*s == (char)c)
			return ((char*)s);
		s--;
	}
	return (NULL);
}

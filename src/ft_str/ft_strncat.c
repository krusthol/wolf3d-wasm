/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:25:50 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/25 18:35:59 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strncat(char *s1, char *s2, size_t n)
{
	char	*ret;
	int		iter;

	iter = (int)n;
	ret = s1;
	while (*s1)
		s1++;
	while (*s2 && iter--)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return (ret);
}

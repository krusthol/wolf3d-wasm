/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:50:01 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/24 19:39:15 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		len;
	int		iter;

	iter = 0;
	len = 0;
	while (s1[iter++])
		len++;
	if (!(dup = (char*)malloc(len + 1)))
		return (NULL);
	iter = 0;
	while (s1[iter])
	{
		dup[iter] = s1[iter];
		iter++;
	}
	dup[iter] = '\0';
	return (dup);
}

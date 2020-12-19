/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:45:25 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/24 00:21:37 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	togo;
	int		iter;

	iter = 0;
	togo = ft_strlen(s1);
	new = ft_strnew(togo + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	while (iter < (int)togo)
		new[iter++] = *s1++;
	togo = togo + ft_strlen(s2);
	while (iter < (int)togo)
		new[iter++] = *s2++;
	new[iter] = '\0';
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:29:31 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/23 23:22:52 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strnew(len + 1);
	if (!new)
		return (NULL);
	s = s + start;
	while (len--)
	{
		new[i] = *s;
		s++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:03:00 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/24 00:25:17 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	temp;
	char	*new;
	char	*ptr;
	int		togo;

	new = ft_strnew(ft_strlen(s));
	if (!new)
		return (NULL);
	ptr = (char*)s;
	togo = 0;
	while (*ptr)
	{
		temp = f(*ptr);
		new[togo] = temp;
		ptr++;
		togo++;
	}
	return (new);
}

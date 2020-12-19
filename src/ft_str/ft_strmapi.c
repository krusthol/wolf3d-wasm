/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 23:54:45 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/24 00:25:05 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	char	*ptr;
	int		togo;
	char	temp;

	new = ft_strnew(ft_strlen(s));
	if (!new)
		return (NULL);
	ptr = (char*)s;
	togo = 0;
	while (ptr[togo])
	{
		temp = f(togo, ptr[togo]);
		new[togo] = temp;
		togo++;
	}
	return (new);
}

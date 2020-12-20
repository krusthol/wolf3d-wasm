/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edgeint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:04:16 by krusthol          #+#    #+#             */
/*   Updated: 2019/11/03 12:22:33 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static void	zero_equals(size_t equs[3])
{
	equs[0] = 0;
	equs[1] = 0;
	equs[2] = 0;
}

int			ft_edgeint(char const *s)
{
	char	*min;
	char	*max;
	size_t	equs[3];

	min = "min";
	max = "max";
	zero_equals(equs);
	while (*s && equs[0] < 4 && equs[1] < 3 && equs[2] < 3)
	{
		if (*s == *min++)
			equs[1]++;
		if (*s == *max++)
			equs[2]++;
		equs[0]++;
		s++;
	}
	if (equs[1] == 3)
		return (-2147483648);
	if (equs[2] == 3)
		return (2147483647);
	return (0);
}

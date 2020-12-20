/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:37:24 by krusthol          #+#    #+#             */
/*   Updated: 2019/11/03 12:58:27 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static char	*edge_itoa(int n)
{
	char *ret;

	if (n == 0)
	{
		if (!(ret = ft_strnew(1)))
			return (NULL);
		ret[0] = '0';
		return (ret);
	}
	if (!(ret = ft_strnew(11)))
		return (NULL);
	ft_strcpy(ret, "-2147483648");
	return (ret);
}

char		*ft_itoa(int n)
{
	char	*trim;
	char	a[12];
	int		index;

	if (n == 0 || n == ft_edgeint("min"))
		return (edge_itoa(n));
	index = 0;
	while (index < 12)
		a[index++] = ' ';
	if (n < 0 && (n = n * (-1)))
		a[0] = '-';
	a[11] = '\0';
	index = 10;
	while (n > 9)
	{
		a[index--] = (n % 10) + '0';
		n = n / 10;
	}
	if (n != 0)
		a[index--] = n + '0';
	if (index > 0 && a[0] == '-')
		a[index] = '-';
	if (!(trim = ft_strtrim(&(a[index]))))
		return (NULL);
	return (trim);
}

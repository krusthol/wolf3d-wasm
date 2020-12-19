/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:47:03 by krusthol          #+#    #+#             */
/*   Updated: 2019/11/03 13:01:33 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strnew(size_t size)
{
	char	*new;

	if (!(new = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (size--)
		new[size] = '\0';
	return (new);
}

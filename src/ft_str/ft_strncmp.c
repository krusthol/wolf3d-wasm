/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:44:10 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/25 18:52:27 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	int				iter;

	iter = (int)n;
	s1_ptr = (unsigned char*)s1;
	s2_ptr = (unsigned char*)s2;
	while ((*s1_ptr || *s2_ptr) && iter--)
	{
		if (*s1_ptr != *s2_ptr)
			return ((int)*s1_ptr - *s2_ptr);
		s1_ptr++;
		s2_ptr++;
	}
	return (0);
}

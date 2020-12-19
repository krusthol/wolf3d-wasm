/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:57:04 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/22 12:24:12 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *s1_ptr;
	unsigned char *s2_ptr;

	s1_ptr = (unsigned char*)s1;
	s2_ptr = (unsigned char*)s2;
	while (*s1_ptr || *s2_ptr)
	{
		if (*s1_ptr != *s2_ptr)
		{
			return ((int)(*s1_ptr - *s2_ptr));
		}
		s1_ptr++;
		s2_ptr++;
	}
	return (0);
}

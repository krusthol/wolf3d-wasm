/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:51:32 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/23 19:50:54 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int	ft_words(char const *s, char c)
{
	int	toggle;
	int words;

	toggle = 0;
	words = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s == c && toggle == 0)
		{
			toggle++;
			words++;
		}
		if (*s != c && toggle == 1)
			toggle--;
		s++;
	}
	if (*(s - 1) != c)
		words++;
	return (words);
}
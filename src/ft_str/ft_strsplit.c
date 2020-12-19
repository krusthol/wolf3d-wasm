/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:36:34 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/24 20:12:23 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static void	set_indices(int *index, int *len, char const *s, char c)
{
	int	words;
	int	index_iter;
	int	len_count;

	words = ft_words(s, c);
	index_iter = 0;
	len_count = 0;
	while (words > 0)
	{
		while (*s && *s == c)
		{
			index_iter++;
			s++;
		}
		*index++ = index_iter;
		while (*s && *s != c)
		{
			index_iter++;
			s++;
			len_count++;
		}
		*len++ = len_count;
		len_count = 0;
		words--;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	int		words;
	int		*index;
	int		*len;
	char	**tab;

	words = ft_words(s, c);
	index = (int*)malloc(sizeof(int) * (words));
	len = (int*)malloc(sizeof(int) * (words));
	if (!index || !len)
		return (NULL);
	set_indices(index, len, s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	index = index + words;
	len = len + words;
	tab[words] = NULL;
	while (words--)
		tab[words] = ft_strsub(s, (unsigned int)*(--index), (size_t)*(--len));
	free(index);
	free(len);
	return (tab);
}

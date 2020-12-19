/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:20:46 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/22 12:23:59 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static void	zero_locs(int locs[2])
{
	locs[0] = 0;
	locs[1] = 0;
}

static void	plus_locs(int locs[2])
{
	locs[0]++;
	locs[1]++;
}

static char	*check_str(char *hay, char *ndl, int locs[2], const char *hs)
{
	if (*ndl == '\0')
		return (hay);
	while (*hay)
	{
		if (*ndl == *hay)
		{
			while (*hay == *ndl)
			{
				hay++;
				ndl++;
				plus_locs(locs);
				if (!*ndl)
					return ((char*)(hs + locs[0] - locs[1]));
			}
			ndl = ndl - locs[1];
			locs[1] = 0;
		}
		hay++;
		locs[0]++;
	}
	return (NULL);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	int		locs[2];

	zero_locs(locs);
	return (check_str((char*)haystack, (char*)needle, locs, haystack));
}

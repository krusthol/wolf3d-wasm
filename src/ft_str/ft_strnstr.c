/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:50:17 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/22 12:24:01 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static void	zero_locs(int locs[3])
{
	locs[0] = 0;
	locs[1] = 0;
}

static void	plus_locs(int locs[3])
{
	locs[0]++;
	locs[1]++;
}

static char	*check_str(char *hay, char *ndl, int locs[3], const char *hs)
{
	while (*hay && locs[2] > 0)
	{
		if (*ndl == *hay)
		{
			while (*hay == *ndl && locs[2] > 0)
			{
				hay++;
				ndl++;
				plus_locs(locs);
				locs[2]--;
				if (!*ndl)
					return ((char*)(hs + locs[0] - locs[1]));
			}
			ndl = ndl - locs[1];
			locs[1] = 0;
		}
		hay++;
		locs[0]++;
		locs[2]--;
	}
	return (NULL);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		locs[3];

	zero_locs(locs);
	locs[2] = (int)len;
	if (*needle == '\0')
		return ((char*)haystack);
	return (check_str((char*)haystack, (char*)needle, locs, haystack));
}

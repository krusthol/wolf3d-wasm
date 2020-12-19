/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:00:48 by krusthol          #+#    #+#             */
/*   Updated: 2019/10/24 00:25:40 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

static int	is_ws(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char		*snub;
	int			ws_beg;
	int			ws_end;
	int			len;

	snub = (char*)s;
	ws_beg = 0;
	ws_end = 0;
	len = (int)ft_strlen(s);
	while (*s && is_ws(*s++))
		ws_beg++;
	while (*s)
		s++;
	s--;
	while (is_ws(*s--))
		ws_end++;
	len = len - ws_beg - ws_end;
	if (len > 0)
		snub = ft_strsub(snub, (unsigned int)ws_beg, (size_t)len);
	else if (ws_beg || ws_end)
		snub = ft_strjoin("", "");
	else
		return (NULL);
	snub[len] = '\0';
	return (snub);
}

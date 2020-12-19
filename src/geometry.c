/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:35:40 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/12 16:16:47 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				sin_distance(int res, int p, long double rad)
{
	int dist;

	dist = fabs((p - res) / sin(rad));
	if (dist < 2)
		return (2);
	return (dist);
}

int				cos_distance(int res, int p, long double rad)
{
	int dist;

	dist = fabs((p - res) / cos(rad));
	if (dist < 2)
		return (2);
	return (dist);
}

int				pick_closer(t_player *p, int vert[2], int horz[2], int res[2])
{
	int vert_dx;
	int vert_dy;
	int horz_dx;
	int horz_dy;

	vert_dx = abs(p->x - vert[0]);
	vert_dy = abs(p->y - vert[1]);
	horz_dx = abs(p->x - horz[0]);
	horz_dy = abs(p->y - horz[1]);
	if ((vert_dx + vert_dy) > (horz_dx + horz_dy))
	{
		res[0] = horz[0];
		res[1] = horz[1];
		p->ray_dist = sin_distance(res[1], p->y, p->rad);
		return (0);
	}
	else
	{
		res[0] = vert[0];
		res[1] = vert[1];
		p->ray_dist = cos_distance(res[0], p->x, p->rad);
		return (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:56:09 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/13 17:56:11 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	no_result(int result[2])
{
	result[0] = 0;
	result[1] = 0;
	return (-1);
}

static void	increment_vert(long double *is, long double *add, int xy[2], int i)
{
	*(is) += *(add);
	xy[0] += i;
	xy[1] = *(is);
}

static void	increment_horz(long double *is, long double *add, int xy[2], int i)
{
	*(is) += *(add);
	xy[0] = *(is);
	xy[1] += i;
}

int			check_vert_intersect(t_grid *grid, t_player *p, int res_xy[2],
	long double *tans)
{
	int			xy[2];
	int			wall_hit;
	int			xa;
	long double	ya;
	long double isy;

	xa = p->is_down ? -256 : 256;
	xy[0] = p->is_down ?
		floor(p->x >> 8) * 256 - 1 : floor(p->x >> 8) * 256 + 256;
	if (p->r_index != 1920 && p->r_index != 5760)
	{
		ya = 256.0 * tans[p->r_index];
		ya = p->is_down ? ya : ya * -1.0;
		xy[1] = p->y + ((long double)(p->x - xy[0]) * tans[p->r_index]);
	}
	else
		return (no_result(res_xy));
	isy = xy[1];
	while (!(wall_hit = hits_wall(grid, xy[0], xy[1])))
		increment_vert(&isy, &ya, xy, xa);
	if (wall_hit == -1)
		return (no_result(res_xy));
	res_xy[0] = xy[0];
	res_xy[1] = xy[1];
	return (xa > 0 ? WEST : EAST);
}

int			check_horz_intersect(t_grid *grid, t_player *p, int res_xy[2],
	long double *tans)
{
	int			xy[2];
	int			wall_hit;
	long double xa;
	int			ya;
	long double isx;

	ya = p->is_right ? -256 : 256;
	xy[1] = p->is_right ?
		floor(p->y >> 8) * 256 - 1 : floor(p->y >> 8) * 256 + 256;
	if (p->r_index != 0 && p->r_index != 3840)
	{
		xa = 256.0 / tans[p->r_index];
		xa = p->is_right ? xa : xa * -1.0;
		xy[0] = p->x + ((long double)(p->y - xy[1]) / tans[p->r_index]);
	}
	else
		return (no_result(res_xy));
	isx = xy[0];
	while (!(wall_hit = hits_wall(grid, xy[0], xy[1])))
		increment_horz(&isx, &xa, xy, ya);
	if (wall_hit == -1)
		return (no_result(res_xy));
	res_xy[0] = xy[0];
	res_xy[1] = xy[1];
	return (ya > 0 ? NORTH : SOUTH);
}

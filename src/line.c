/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:47:22 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/07 18:51:27 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_line	*quad(int quad_mode, t_line *l)
{
	l->fx = l->x1;
	l->fy = l->y1;
	l->px = l->x2;
	l->py = -1;
	if (quad_mode == 1)
	{
		l->fx = l->x2;
		l->fy = l->y2;
		l->px = l->x1;
		l->py = -1;
	}
	else if (quad_mode == 2)
	{
		l->px = -1;
		l->py = l->y2;
	}
	else if (quad_mode == 3)
	{
		l->fx = l->x2;
		l->fy = l->y2;
		l->px = -1;
		l->py = l->y1;
	}
	return (l);
}

static void		line_draw(t_line *l, t_view *v, int delta_x, int delta_y)
{
	int				abs_deltas[2];
	int				kx;
	unsigned int	*buffer;

	buffer = v->pix;
	abs_deltas[0] = abs(delta_x);
	abs_deltas[1] = abs(delta_y);
	kx = 2 * abs_deltas[1] - abs_deltas[0];
	pixel_to_img(buffer, l->fx, l->fy, l->color);
	while (l->fx < l->px)
	{
		l->fx++;
		if (kx < 0)
			kx += 2 * abs_deltas[1];
		else
		{
			if ((delta_x < 0 && delta_y < 0) || (delta_x > 0 && delta_y > 0))
				l->fy++;
			else
				l->fy--;
			kx += 2 * (abs_deltas[1] - abs_deltas[0]);
		}
		pixel_to_img(buffer, l->fx, l->fy, l->color);
	}
}

static void		line_mirror(t_line *l, t_view *v, int delta_x, int delta_y)
{
	int				abs_deltas[2];
	int				ky;
	unsigned int	*buffer;

	buffer = v->pix;
	abs_deltas[0] = abs(delta_x);
	abs_deltas[1] = abs(delta_y);
	ky = 2 * abs_deltas[0] - abs_deltas[1];
	pixel_to_img(buffer, l->fx, l->fy, l->color);
	while (l->fy < l->py)
	{
		l->fy++;
		if (ky <= 0)
			ky += 2 * abs_deltas[0];
		else
		{
			if ((delta_x < 0 && delta_y < 0) || (delta_x > 0 && delta_y > 0))
				l->fx++;
			else
				l->fx--;
			ky += 2 * (abs_deltas[0] - abs_deltas[1]);
		}
		pixel_to_img(buffer, l->fx, l->fy, l->color);
	}
}

void			offset_line(int x, int y, t_line *line)
{
	line->x1 -= x;
	line->x2 -= x;
	line->y1 -= y;
	line->y2 -= y;
}

void			line(t_line *l, t_view *v)
{
	int delta_x;
	int	delta_y;

	delta_x = l->x2 - l->x1;
	delta_y = l->y2 - l->y1;
	if (abs(delta_y) <= abs(delta_x))
	{
		if (delta_x >= 0)
			l = quad(0, l);
		else
			l = quad(1, l);
		line_draw(l, v, delta_x, delta_y);
	}
	else
	{
		if (delta_y >= 0)
			l = quad(2, l);
		else
			l = quad(3, l);
		line_mirror(l, v, delta_x, delta_y);
	}
}

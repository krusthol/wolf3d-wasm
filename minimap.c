/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:05:23 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/12 16:26:27 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3dheader"

static void	draw_arrow(t_view *view, t_line arrow, t_line r_wing, t_line l_wing)
{
	int		off_xy[2];

	off_xy[0] = view->p->x;
	off_xy[1] = view->p->y;
	if (off_xy[0] < 1280 && off_xy[1] < 1280)
	{
		offset_line((1280 - off_xy[0]) >> 2, (1280 - off_xy[1]) >> 2, &arrow);
		offset_line((1280 - off_xy[0]) >> 2, (1280 - off_xy[1]) >> 2, &r_wing);
		offset_line((1280 - off_xy[0]) >> 2, (1280 - off_xy[1]) >> 2, &l_wing);
	}
	else if (off_xy[0] < 1280)
	{
		offset_line((1280 - off_xy[0]) >> 2, 0, &arrow);
		offset_line((1280 - off_xy[0]) >> 2, 0, &r_wing);
		offset_line((1280 - off_xy[0]) >> 2, 0, &l_wing);
	}
	else if (off_xy[1] < 1280)
	{
		offset_line(0, (1280 - off_xy[1]) >> 2, &arrow);
		offset_line(0, (1280 - off_xy[1]) >> 2, &r_wing);
		offset_line(0, (1280 - off_xy[1]) >> 2, &l_wing);
	}
	line(&arrow, view);
	line(&r_wing, view);
	line(&l_wing, view);
}

static void	arrow_geometry(t_line arrow[3], int off_xy[2], int d_xy2[4],
	int *sin_cos_10_25)
{
	arrow[0].x1 = 640 - (off_xy[0] - d_xy2[0]);
	arrow[0].x2 = 640 + (off_xy[0] - d_xy2[0]);
	arrow[0].y1 = 400 - (off_xy[1] - d_xy2[1]);
	arrow[0].y2 = 400 + (off_xy[1] - d_xy2[1]);
	arrow[0].color = 0xFF00FF;
	d_xy2[0] = d_xy2[0] + sin_cos_10_25[5];
	d_xy2[1] = d_xy2[1] - sin_cos_10_25[4];
	arrow[1].x1 = 640 - (off_xy[0] - d_xy2[0]);
	arrow[1].x2 = 640 - (off_xy[0] - d_xy2[2]);
	arrow[1].y1 = 400 - (off_xy[1] - d_xy2[1]);
	arrow[1].y2 = 400 - (off_xy[1] - d_xy2[3]);
	arrow[1].color = 0xFF00FF;
	d_xy2[0] = (off_xy[0] + sin_cos_10_25[1] + sin_cos_10_25[7]);
	d_xy2[1] = (off_xy[1] - sin_cos_10_25[0] - sin_cos_10_25[6]);
	arrow[2].x1 = 640 - (off_xy[0] - d_xy2[0]);
	arrow[2].x2 = 640 - (off_xy[0] - d_xy2[2]);
	arrow[2].y1 = 400 - (off_xy[1] - d_xy2[1]);
	arrow[2].y2 = 400 - (off_xy[1] - d_xy2[3]);
	arrow[2].color = 0xFF00FF;
}

static void	minimap_player(t_view *view, t_player *p, int *sin_cos_10_25)
{
	t_line	arrow[3];
	int		off_xy[2];
	int		d_xy2[4];

	off_xy[0] = p->x;
	off_xy[1] = p->y;
	d_xy2[0] = off_xy[0] + sin_cos_10_25[1];
	d_xy2[1] = off_xy[1] - sin_cos_10_25[0];
	d_xy2[2] = off_xy[0] + sin_cos_10_25[3];
	d_xy2[3] = off_xy[1] - sin_cos_10_25[2];
	arrow_geometry(arrow, off_xy, d_xy2, sin_cos_10_25);
	draw_arrow(view, arrow[0], arrow[1], arrow[2]);
}

static void	minimap_grid(t_view *view, int x, int y, int lim_xy[2])
{
	int xy[2];
	int grid[2];
	int off_xy[2];
	int	*buffer;

	buffer = view->idp->int_buffer;
	off_xy[0] = view->p->x;
	off_xy[1] = view->p->y;
	while (y++ < 641)
	{
		xy[1] = off_xy[1] > 1280 ? y + ((off_xy[1] - 1280) >> 2) : y;
		grid[1] = (xy[1] >> 6) < lim_xy[1] ? xy[1] >> 6 : (lim_xy[1] - 1);
		while (x++ < 641)
		{
			xy[0] = off_xy[0] > 1280 ? x + ((off_xy[0] - 1280) >> 2) : x;
			grid[0] = (xy[0] >> 6) < lim_xy[0] ? xy[0] >> 6 : (lim_xy[0] - 1);
			if ((x == 641 || y == 0 || y == 641 || x == 0)
				|| (((xy[1] & 15) == 0 || (xy[0] & 15) == 0)
				&& view->g->grid[grid[1]][grid[0]] == 'W'))
				pixel_to_img(buffer, x + 320, y + 80, 0xFF00FF);
			if (((xy[1] & 63) == 0 || (xy[0] & 63) == 0))
				pixel_to_img(buffer, x + 320, y + 80, 0x00FF00);
		}
		x = -1;
	}
}

void		draw_minimap(t_view *view)
{
	int		lim_xy[2];
	int		sin_cos_10_25[8];

	lim_xy[0] = view->g->cols;
	lim_xy[1] = view->g->rows;
	sin_cos_10_25[0] = (int)(sin(view->p->rad) * 10);
	sin_cos_10_25[1] = (int)(cos(view->p->rad) * 10);
	sin_cos_10_25[2] = (int)(sin(view->p->rad) * 25);
	sin_cos_10_25[3] = (int)(cos(view->p->rad) * 25);
	sin_cos_10_25[4] = (int)(sin(view->p->rad + 1) * 10);
	sin_cos_10_25[5] = (int)(cos(view->p->rad + 1) * 10);
	sin_cos_10_25[6] = (int)(sin(view->p->rad - 1) * 10);
	sin_cos_10_25[7] = (int)(cos(view->p->rad - 1) * 10);
	minimap_grid(view, -1, -1, lim_xy);
	minimap_player(view, view->p, sin_cos_10_25);
}

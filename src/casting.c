/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 21:54:15 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/12 17:12:27 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	abandon_result(int result[2], int face, t_grid *grid)
{
	int gx;
	int gy;

	gx = result[0] >> 8;
	gy = result[1] >> 8;
	if (gx < 0 || gx >= grid->cols || gy < 0 || gy >= grid->rows)
		return (1);
	if ((face == 3 && gx > 0) && (grid->grid[gy][gx - 1] == 'W'))
		return (1);
	if ((face == 2 && gy + 1 < grid->rows) && (grid->grid[gy + 1][gx] == 'W'))
		return (1);
	if ((face == 1 && gx + 1 < grid->cols) && (grid->grid[gy][gx + 1] == 'W'))
		return (1);
	if ((face == 0 && gy > 0) && (grid->grid[gy - 1][gx] == 'W'))
		return (1);
	return (0);
}

static int	assign_result(int result[2], int assignment[2], int face)
{
	result[0] = assignment[0];
	result[1] = assignment[1];
	return (face);
}

static int	find_wall(t_grid *grid, t_player *p, int wall_xy_result[2],
	long double *tan_table)
{
	int res_vert[2];
	int res_horz[2];
	int	face_vert;
	int face_horz;

	face_vert = check_vert_intersect(grid, p, res_vert, tan_table);
	face_horz = check_horz_intersect(grid, p, res_horz, tan_table);
	if (face_vert == -1)
	{
		p->ray_dist = sin_distance(wall_xy_result[1], p->y, p->rad);
		return (assign_result(wall_xy_result, res_horz, face_horz));
	}
	if (face_horz == -1 || abandon_result(res_horz, face_horz, grid))
	{
		p->ray_dist = cos_distance(wall_xy_result[0], p->x, p->rad);
		return (assign_result(wall_xy_result, res_vert, face_vert));
	}
	if (abandon_result(res_vert, face_vert, grid))
	{
		p->ray_dist = sin_distance(wall_xy_result[1], p->y, p->rad);
		return (assign_result(wall_xy_result, res_horz, face_horz));
	}
	return (pick_closer(p, res_vert, res_horz, wall_xy_result) ?
		face_vert : face_horz);
}

static void	set_radian_index(t_player *p, t_view *view)
{
	p->r_index = p->move_look > 29 ? (p->move_look - 30.0) * 21.333333 :
		(359.0 - (30.0 - p->move_look)) * 21.333333;
	p->is_down = (p->r_index >= 1920 && p->r_index <= 5760);
	p->is_right = (p->r_index >= 0 && p->r_index <= 3840);
	p->rad = view->rads7680[p->r_index];
}

void		cast_walls(int i, t_grid *grid, t_player *p, t_view *view)
{
	int		walls[1280];
	int		facing[1280];
	int		txt_offset[1280];

	set_radian_index(p, view);
	while (i++ < 1279)
	{
		facing[i] = find_wall(grid, p, p->ray_xy, view->tans7680);
		txt_offset[i] = facing[i] == NORTH || facing[i] == SOUTH ?
			p->ray_xy[0] & 255 : p->ray_xy[1] & 255;
		walls[i] = view->fisheye1280[i] * p->ray_dist;
		p->r_index++;
		if (p->r_index > 7679)
			p->r_index = 0;
		p->is_down = (p->r_index >= 1920 && p->r_index <= 5760);
		p->is_right = (p->r_index >= 0 && p->r_index <= 3840);
		p->rad = view->rads7680[p->r_index];
	}
	p->rad = view->rads360[(p->move_look)];
	p->move_facing = facing[639];
	//draw_walls(walls, facing, txt_offset, view);
}

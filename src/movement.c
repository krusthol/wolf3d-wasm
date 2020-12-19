/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:02:28 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/12 15:36:59 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	coast_rotate(t_player *p, const long double *rads360)
{
	if (p->rotation_velo > 8 || p->rotation_velo < -8)
		p->rotation_velo = p->rotation_velo > 0 ? p->rotation_velo - 8: p->rotation_velo + 8;
	else
		p->rotation_velo = 0;
	p->move_look += p->rotation_velo >> 6;
	if (p->move_look < 0)
		p->move_look = 359 + p->move_look;
	if (p->move_look > 359)
		p->move_look = 0 + (p->move_look - 359);
	p->rad = rads360[(p->move_look)];
}

static void	coast_step(t_player *p, t_grid *grid)
{
	int dir;
	int dx;
	int dy;
	int cy;
	int cx;

	dir = p->stepping_velo > 0 ? 1 : 0;
	if (dir)
		assign_clip_values(&cx, &cy, p->move_facing);
	p->stepping_velo = p->stepping_velo > 0 ? p->stepping_velo - 2
											: p->stepping_velo + 2;
	if (abs(p->stepping_velo) < 2)
		p->stepping_velo = 0;
	dx = p->x + (int)(cos(p->rad) * p->stepping_velo);
	dy = p->y - (int)(sin(p->rad) * p->stepping_velo);
	if ((dx > 256 && dy > 256) && (dx < (grid->cols - 1) * 256
								   && dy < (grid->rows - 1) * 256))
	{
		if (dir && !(grid->grid[(dy + cy) >> 8][(dx + cx) >> 8] == '.'))
			return (stop_velocity(p));
		else if (!dir && !(grid->grid[(dy) >> 8][(dx) >> 8] == '.'))
			return (stop_velocity(p));
		p->x = dx;
		p->y = dy;
	}
}

static void	step_player(t_player *p, t_grid *grid, int dir)
{
	int dx;
	int dy;
	int cy;
	int cx;

	assign_clip_values(&cx, &cy, p->move_facing);
	p->stepping_velo = p->stepping_velo + dir * 3;
	if (p->stepping_velo > 24 || p->stepping_velo < -24)
		p->stepping_velo = p->stepping_velo > 0 ? 24 : -24;
	dx = p->x + (int)(cos(p->rad) * p->stepping_velo);
	dy = p->y - (int)(sin(p->rad) * p->stepping_velo);
	if ((dx > 256 && dy > 256) && (dx < (grid->cols - 1) * 256
								   && dy < (grid->rows - 1) * 256))
	{
		if (dir == 1 && !(grid->grid[(dy + cy) >> 8][(dx + cx) >> 8] == '.'))
			return (stop_velocity(p));
		else if (dir == -1 && !(grid->grid[(dy) >> 8][(dx) >> 8] == '.'))
			return (stop_velocity(p));
		p->x = dx;
		p->y = dy;
	}
}

static void	rotate_player(t_player *p, long double *rads360, int direction)
{
	p->rotation_velo = p->rotation_velo + (direction * 12);
	if (p->rotation_velo > 192 || p->rotation_velo < -192)
		p->rotation_velo = p->rotation_velo > 0 ? 192 : -192;
	if (direction == -1)
	{
		p->move_look += p->rotation_velo >> 6;
		if (p->move_look < 0)
			p->move_look = 359 + p->move_look;
		p->rad = rads360[(p->move_look)];
	}
	else if (direction == 1)
	{
		p->move_look += p->rotation_velo >> 6;
		if (p->move_look > 359)
			p->move_look = 0 + (p->move_look - 359);
		p->rad = rads360[(p->move_look)];
	}
}

void		calc_movements(t_view *view)
{
	//Rotation difference between left, right, debug stack
	//Propably bugged because of int division not being symmetrical
	static int	rotted_0 = 0;
	static int	rotted_1 = 0;
	static int	peak = 0;
	static int	valley = 0;
	static int 	delta_move = 0;
	static int 	begin_move = 0;

	// Rotation stack
	if (view->p->rotating[0] && view->p->rotating[1])
	{
		//puts("Both rotation keys pressed!");
		coast_rotate(view->p, view->rads360);
	}
	else if (view->p->rotating[0])
	{
		//puts("Rotation[0] key pressed!");
		if (!begin_move)
		{
			begin_move = 1;
			delta_move = view->p->move_look;
		}
		rotate_player(view->p, view->rads360, view->p->rotating[0]);
		rotted_0++;
		if (view->p->rotation_velo > peak)
			peak = view->p->rotation_velo;
		if (view->p->rotation_velo < valley)
			valley = view->p->rotation_velo;


	}
	else if (view->p->rotating[1])
	{
		//puts("Rotation[1] key pressed!");
		if (!begin_move)
		{
			begin_move = 1;
			delta_move = view->p->move_look;
		}
		rotate_player(view->p, view->rads360, view->p->rotating[1]);
		rotted_1++;
		if (view->p->rotation_velo > peak)
			peak = view->p->rotation_velo;
		if (view->p->rotation_velo < valley)
			valley = view->p->rotation_velo;
	}
	else if (view->p->rotation_velo != 0)
	{
		//puts("Remnant rotation, while no rotation keys are pressed!");
		coast_rotate(view->p, view->rads360);
	}
	else if (view->p->rotation_velo == 0 && (peak != 0 || valley != 0))
	{
		//puts("Rotation stopped!");
		//printf("DELTA = % d | Rotted_0 = %d | Rotted_1 = %d | Peak = %d | Valley = %d\n", abs(delta_move - view->p->move_look), rotted_0, rotted_1, peak, valley);
		rotted_0 = 0;
		rotted_1 = 0;
		peak = 0;
		valley = 0;
		begin_move = 0;
	}
	// Forward and backwards movement stack
	if (view->p->stepping[0] && view->p->stepping[1])
		coast_step(view->p, view->g);
	else if (view->p->stepping[0])
		step_player(view->p, view->g, view->p->stepping[0]);
	else if (view->p->stepping[1])
		step_player(view->p, view->g, view->p->stepping[1]);
	else if (view->p->stepping_velo != 0)
		coast_step(view->p, view->g);
	if (view->p->rotation_velo != 0 || view->p->stepping_velo != 0)
		cast_walls(-1, view->g, view->p, view);
}

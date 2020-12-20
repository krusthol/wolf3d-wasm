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

static void notify_fps(t_view *view, int *frames, const double stopwatch, int draw)
{
	double	seconds;
	int 	fps;

	seconds = (time_ms_double() - stopwatch);
	seconds *= 0.001;
	fps = (int)((double)*frames / seconds);
	if (view->fps_on)
	{
		SDL_FreeSurface(view->font_surf);
		view->font_surf = TTF_RenderText_Solid(view->ibm_font, ft_itoa(fps), view->color_white);
		if (!view->font_surf)
			quit_error("Fatal Error: TTF_RenderText_Solid failed.");
	}
	//else
	//	printf("%d FPS {%d frames per %f seconds}\n", fps, *frames, seconds);
	*frames = 0;
	cast_walls(-1, view->g, view->p, view);
}

static void draw_changes(t_view *view, int *frames, double *stopwatch)
{
	if (!(*frames))
		*stopwatch = time_ms_double();
	(*frames)++;
	if (*frames > 60)
		notify_fps(view, frames, *stopwatch, 0);
	cast_walls(-1, view->g, view->p, view);
}

void		calc_movements(t_view *view)
{
	static int		frames;
	static double	stopwatch;
	static double 	dt_watch;
	static double 	dt_count;
	double 			dt;

	dt = time_ms_double() - dt_watch;
	dt_watch = time_ms_double();
	dt_count += dt;
	if (dt_count < 16 && (view->p->rotation_velo != 0 || view->p->stepping_velo != 0))
		return (draw_changes(view, &frames, &stopwatch));
	else if (dt_count < 16)
	{
		if (frames)
			notify_fps(view, &frames, stopwatch, 1);
		return ;
	}
	if (dt_count > 16)
		dt_count = dt_count > 48 ? 32 : dt_count - 16;
	rotate_and_step(view);
	if (view->p->rotation_velo != 0 || view->p->stepping_velo != 0)
		return (draw_changes(view, &frames, &stopwatch));
	else if (frames)
		notify_fps(view, &frames, stopwatch, 1);
}

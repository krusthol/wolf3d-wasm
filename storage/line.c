/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:47:22 by krusthol          #+#    #+#             */
/*   Updated: 2020/09/15 15:31:27 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "delta-2d.h"

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

static void		line_quick_draw(t_line *l, int delta_x, int delta_y)
{
	int				abs_deltas[2];
	int				kx;
	int				loc;
	int				line_width;
	int				i = 0;
	uint32_t		col;
	uint32_t		*pixels;
	uint32_t		*src_pix;

	pixels = l->buff->pixels;
	line_width = l->buff->w;
	col = l->color;
	abs_deltas[0] = abs(delta_x);
	abs_deltas[1] = abs(delta_y);
	kx = 2 * abs_deltas[1] - abs_deltas[0];
	loc = l->fx + (l->fy * line_width);
	if (l->blit)
	{
		pixels = l->dst->pixels;
		src_pix = l->src->pixels;
		col = src_pix[loc];
	}
	if (!l->rope)
		pixels[loc] = col;
	while (l->fx < l->px)
	{
		loc++;
		l->fx++;
		if (kx < 0)
			kx += 2 * abs_deltas[1];
		else
		{
			if ((delta_x < 0 && delta_y < 0) || (delta_x > 0 && delta_y > 0))
				loc += line_width;
			else
				loc -= line_width;
			kx += 2 * (abs_deltas[1] - abs_deltas[0]);
		}
		if (!l->blit && !l->rope)
			pixels[loc] = col;
		else if (l->rope && ((i++ % (l->segment + l->empty)) >= l->empty))
			pixels[loc] = col;
		else if (l->blit)
			pixels[loc] = src_pix[loc];
	}
}

static void 	line_quick_mirror(t_line *l, int delta_x, int delta_y)
{
	int			abs_deltas[2];
	int			ky;
	int			loc;
	int			line_width;
	int			i = 0;
	uint32_t	col;
	uint32_t	*pixels;
	uint32_t	*src_pix;

	pixels = l->buff->pixels;
	line_width = l->buff->w;
	col = l->color;
	abs_deltas[0] = abs(delta_x);
	abs_deltas[1] = abs(delta_y);
	ky = 2 * abs_deltas[0] - abs_deltas[1];
	loc = l->fx + (l->fy * line_width);
	if (l->blit)
	{
		pixels = l->dst->pixels;
		src_pix = l->src->pixels;
		col = src_pix[loc];
	}
	if (!l->rope)
		pixels[loc] = col;
	while (l->fy < l->py)
	{
		loc += line_width;
		l->fy++;
		if (ky <= 0)
			ky += 2 * abs_deltas[0];
		else
		{
			if ((delta_x < 0 && delta_y < 0) || (delta_x > 0 && delta_y > 0))
				loc++;
			else
				loc--;
			ky += 2 * (abs_deltas[0] - abs_deltas[1]);
		}
		if (!l->blit && !l->rope)
			pixels[loc] = col;
		else if (l->rope && ((i++ % (l->segment + l->empty)) >= l->empty))
			pixels[loc] = col;
		else if (l->blit)
			pixels[loc] = src_pix[loc];
	}
}

/*
 * Bresenham's line algorithm, calculated with integer values.
 */

void			render_line(t_line *l)
{
	int delta_x;
	int	delta_y;

	delta_x = l->x2 - l->x1;
	delta_y = l->y2 - l->y1;
	l->blit = 0;
	if (abs(delta_y) <= abs(delta_x))
	{
		if (delta_x >= 0)
			l = quad(0, l);
		else
			l = quad(1, l);
		line_quick_draw(l, delta_x, delta_y);
	}
	else
	{
		if (delta_y >= 0)
			l = quad(2, l);
		else
			l = quad(3, l);
		line_quick_mirror(l, delta_x, delta_y);
	}
}

static void		blit_line(t_line *l, SDL_Surface *blit_src, SDL_Surface *blit_dst)
{
	int delta_x;
	int	delta_y;

	delta_x = l->x2 - l->x1;
	delta_y = l->y2 - l->y1;
	l->blit = 1;
	l->src = blit_src;
	l->dst = blit_dst;	
	if (abs(delta_y) <= abs(delta_x))
	{
		if (delta_x >= 0)
			l = quad(0, l);
		else
			l = quad(1, l);
		line_quick_draw(l, delta_x, delta_y);
	}
	else
	{
		if (delta_y >= 0)
			l = quad(2, l);
		else
			l = quad(3, l);
		line_quick_mirror(l, delta_x, delta_y);
	}
}

static SDL_Surface	*delta_rgb_surface_rgb888(int width, int height)
{
	int rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
	amask = 0;
#else
    rmask = 0x00ff0000;
    gmask = 0x0000ff00;
    bmask = 0x000000ff;
	amask = 0;
#endif
	return (SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask));
}

static inline void	blit_rope(t_line *line, SDL_Surface *blit_src, SDL_Surface *blit_dst)
{
	blit_line(line, blit_src, blit_dst);
	line->y1++;
	line->y2++;
	blit_line(line, blit_src, blit_dst);
	line->y1++;
	line->y2++;
	blit_line(line, blit_src, blit_dst);
	line->y1 -= 2;
	line->y2 -= 2;
}

static inline void	render_rope(t_line *line)
{
	line->color = 0xff000000;
	line->rope = 1;
	render_line(line);
	line->y1++;
	line->y2++;
	line->color = 0xff964B00;
	render_line(line);
	line->y1++;
	line->y2++;
	line->color = 0xff000000;
	render_line(line);
	line->y1 -= 2;
	line->y2 -= 2;
	line->rope = 0;
}

void				delta2d_rope(t_line *line, SDL_Surface *blit_dst)
{
	static SDL_Surface	*prev_dst = NULL;
	static SDL_Surface	*d_surf = NULL;
	static t_line		d_line = { 0 };

	if (!d_surf || blit_dst != prev_dst)
	{
		d_surf = delta_rgb_surface_rgb888(blit_dst->w, blit_dst->h);
		if (!d_surf)
			error_exit("Fatal error: Could not allocate delta surface at delta2d_line", 1);
		SDL_BlitSurface(blit_dst, NULL, d_surf, NULL);	
		prev_dst = blit_dst;
		//printf("%s BLIT_DST | %s D_SURF\n", SDL_GetPixelFormatName(blit_dst->format->format), SDL_GetPixelFormatName(d_surf->format->format));
	}
	else
		blit_rope(&d_line, d_surf, blit_dst);
	render_rope(line);
	d_line.x1 = line->x1;
	d_line.x2 = line->x2;
	d_line.y1 = line->y1;
	d_line.y2 = line->y2;
	d_line.buff = line->buff;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:53:32 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/20 18:53:33 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		slice_colored(int t[4], int from_to[2], int facing,
	t_view *view)
{
	unsigned int	percent;
	int				y;
	unsigned int	*buffer;

	buffer = view->pix;
	y = 0;
	if (!view->shading_on)
		percent = 99;
	else
		percent = (((900 - from_to[0]) >> 3) - 13) > 99 ? 10 :
			(((900 - from_to[0]) >> 3) - 13);
	if (view->shading_on)
		shaded_roof(t[0], from_to[0], view);
	else
		while (y < from_to[0])
			pixel_to_img(buffer, t[0], y++, 0x484848);
	while (from_to[0] < from_to[1])
		pixel_to_img(buffer, t[0], from_to[0]++,
			view->wall_colors[(facing * 100) + percent]);
	if (view->shading_on)
		shaded_floor(t[0], from_to[1], view);
	else
		while (from_to[1] < 800)
			pixel_to_img(buffer, t[0], from_to[1]++, 0x888888);
}

static void		draw_colored_walls(int *walls, int *facing, int *txt_offset,
	t_view *view)
{
	double	height;
	int		from_to[2];
	int		i;
	int		t[4];

	i = 0;
	while (i < 1280)
	{
		height = 256.0 / walls[1279 - i] * 1024.0;
		t[3] = 0;
		if (height > 800)
		{
			t[3] = height - 800;
			height = 800;
		}
		from_to[0] = 400 - height / 2;
		from_to[1] = from_to[0] + height;
		t[0] = i;
		t[1] = i & 255;
		t[2] = txt_offset[1279 - i];
		slice_colored(t, from_to, facing[1279 - i], view);
		i++;
	}
}

void			draw_walls(int *walls, int *facing, int *txt_offset, t_view *view)
{
	prepare_gpu(view);
	SDL_FillRect(view->surf, NULL, 0x00000000);
	if (view->textures_on)
		draw_textured_walls(walls, facing, txt_offset, view);
	else
		draw_colored_walls(walls, facing, txt_offset, view);
	if (view->minimap_on)
		draw_minimap(view);
	if (view->fps_on)
	{
		SDL_BlitSurface(view->font_surf, NULL, view->surf, &view->font_rect);
		SDL_BlitSurface(view->fps_surf, NULL, view->surf, &view->fps_rect);
	}
	update_gpu(view);
}

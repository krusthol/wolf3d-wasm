/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 20:18:50 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/24 20:18:53 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	shaded_roof(int x, int from, t_view *view)
{
	int y;
	int	shade;
	unsigned int *roof_shades;
	unsigned int *buffer;

	buffer = view->pix;
	roof_shades = &(view->wall_colors[400]);
	shade = 75;
	y = 0;
	while (y < from)
	{
		pixel_to_img(buffer, x, y++, roof_shades[shade]);
		if (!(y & 7))
			shade--;
	}
}

void	shaded_floor(int x, int to, t_view *view)
{
	int y;
	int	shade;
	unsigned int *floor_shades;
	unsigned int *buffer;

	buffer = view->pix;
	y = 799;
	floor_shades = &(view->wall_colors[500]);
	shade = 85;
	while (y >= to)
	{
		pixel_to_img(buffer, x, y--, floor_shades[shade]);
		if (!(y & 7))
			shade--;
	}
}

unsigned int	color(unsigned int percent, unsigned int color)
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;

	if (percent > 99)
		return (color);
	blue = ((color & 0xFF) * percent) / 100;
	green = (((color >> 8) & 0xFF) * percent) / 100;
	red = (((color >> 16) & 0xFF) * percent) / 100;
	return ((red << 16) | (green << 8) | blue);
}

void	pixel_to_img(unsigned int *buffer, unsigned int x, unsigned int y, unsigned int color)
{
	size_t	pixel;

	pixel = (((y * 10) << 7) + x);
	if (pixel > 1023999)
		return ;
	buffer[pixel] = color;
}

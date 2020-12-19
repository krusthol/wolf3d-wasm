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

#include "wolf3dheader"

void	shaded_roof(int x, int from, t_view *view)
{
	int y;
	int	shade;
	int	*roof_shades;
	int	*buffer;

	buffer = view->idp->int_buffer;
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
	int	*floor_shades;
	int	*buffer;

	buffer = view->idp->int_buffer;
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

int		color(unsigned int percent, int color)
{
	int red;
	int green;
	int blue;

	if (percent > 99)
		return (color);
	blue = ((color & 0xFF) * percent) / 100;
	green = (((color >> 8) & 0xFF) * percent) / 100;
	red = (((color >> 16) & 0xFF) * percent) / 100;
	return ((red << 16) | (green << 8) | blue);
}

void	pixel_to_img(int *buffer, unsigned int x, unsigned int y, int color)
{
	size_t	pixel;

	pixel = (((y * 10) << 7) + x);
	if (pixel > 1023999)
		return ;
	buffer[pixel] = color;
}

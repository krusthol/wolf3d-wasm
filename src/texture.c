/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:23:44 by krusthol          #+#    #+#             */
/*   Updated: 2020/02/21 14:23:49 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
/*
static void		slice_shaded(int t[4], int from_to[2], int *txt_buffer,
	t_view *view)
{
	unsigned int	percent;
	int				i_txt;
	float			i_step;
	int				*buffer;

	buffer = view->idp->int_buffer;
	i_step = t[3] == 0 ? 256.0 / (from_to[1] - from_to[0]) : 256.0 /
		(from_to[1] + t[3] - from_to[0]);
	i_txt = t[3] == 0 ? 0 :
		((256 - (int)(256.0 * (800.0 / (800.0 + t[3])))) >> 1) / i_step;
	percent = (900 - from_to[0]) >> 3;
	percent = percent - 13;
	if (percent > 99)
		percent = 10;
	shaded_roof(t[0], from_to[0], view);
	while (from_to[0] < from_to[1])
	{
		pixel_to_img(buffer, t[0], from_to[0],
		color(percent, txt_buffer[((int)(i_step * i_txt++) << 8) + t[2]]));
		from_to[0]++;
	}
	shaded_floor(t[0], from_to[1], view);
}

static void		slice_raw(int t[4], int from_to[2], int facing,
	t_view *view)
{
	int				zero_y;
	int				i_txt;
	float			i_step;
	int				*buffer;

	buffer = view->idp->int_buffer;
	zero_y = 0;
	i_step = t[3] == 0 ? 256.0 / (from_to[1] - from_to[0]) : 256.0 /
		(from_to[1] + t[3] - from_to[0]);
	i_txt = t[3] == 0 ? 0 :
		((256 - (int)(256.0 * (800.0 / (800.0 + t[3])))) >> 1) / i_step;
	while (zero_y < from_to[0])
		pixel_to_img(buffer, t[0], zero_y++, 0x484848);
	while (from_to[0] < from_to[1])
	{
		pixel_to_img(buffer, t[0], from_to[0], view->nesw[facing]
			[((int)(i_step * i_txt++) << 8) + t[2]]);
		from_to[0]++;
	}
	while (from_to[1] < 800)
		pixel_to_img(buffer, t[0], from_to[1]++, 0x888888);
}

void			draw_textured_walls(int *walls, int *facing, int *txt_offset,
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
		t[3] = height > 800 ? height - 800 : 0;
		if (height > 800)
			height = 800;
		from_to[0] = 400 - height / 2;
		from_to[1] = from_to[0] + height;
		t[0] = i;
		t[1] = i & 255;
		t[2] = txt_offset[1279 - i];
		if (view->shading_on)
			slice_shaded(t, from_to, view->nesw[facing[1279 - i]], view);
		else
			slice_raw(t, from_to, facing[1279 - i], view);
		i++;
	}
}
*/
void			load_textures(t_view *view)
{
	char	*texture_filenames[4];
	int		i;

	i = -1;
	texture_filenames[0] = "assets/north.png";
	texture_filenames[1] = "assets/east.png";
	texture_filenames[2] = "assets/south.png";
	texture_filenames[3] = "assets/west.png";
	while (i++ < 3)
	{
		//if (!(view->txt_nesw[i] = mlx_xpm_file_to_image(view->mlx, texture_filenames[i], &ret_h, &ret_w)))
		if (!(view->txt_nesw[i] = IMG_Load(texture_filenames[i])))
			exit(print_error(TEXTURE_LOAD_FAILURE));
		if (view->txt_nesw[i]->w != 256 || view->txt_nesw[i]->h != 256)
			exit(print_error(INVALID_TEXTURE));
		/*view->img_data_nesw[i].buffer =
		mlx_get_data_addr(view->txt_nesw[i],
		&(view->img_data_nesw[i].bits_per_pixel),
		&(view->img_data_nesw[i].bytes_per_line),
		&(view->img_data_nesw[i].endianness));
		view->img_data_nesw[i].int_buffer = (int*)view->img_data_nesw[i].buffer;*/
		view->nesw[i] = view->txt_nesw[i]->pixels;
	}
}

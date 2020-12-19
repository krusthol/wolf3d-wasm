#include "delta-2d.h"

void	default_style(t_pro *pro)
{
	pro->pos.x = 0;
	pro->pos.y = 0;
	pro->sty.bg_color = 0xff00ff;
	pro->sty.fg_color = 0x000000;
	pro->sty.border_color = 0xffffff;
	pro->sty.border_size = 2;
	pro->sty.text_color = 0x00ffff;
	pro->sty.text_off_x = 0;
	pro->sty.text_off_y = 0;
	pro->sty.font = "assets/fonts/ibm_bios.ttf";
	pro->sty.font_size = 16;
	pro->sty.align = ALIGN_CENTER;
}

int 	cols2hx (int red, int green, int blue)
{
	return ((red & 0xFF) << 16 | (green & 0xFF) << 8 | (blue & 0xFF));
}

int		hx2col (int hex, int color)
{
	int red;
	int blue;
	int green;

	blue = (hex & 0xFF);
	green = (hex >> 8) & 0xFF;
	red = (hex >> 16) & 0xFF;
	if (color == RED)
		return (red);
	else if (color == GREEN)
		return (green);
	else if (color == BLUE)
		return (blue);
	return (-1);
}

int		center (int window_size, int element_size)
{
	return (window_size / 2 - (element_size / 2));
}

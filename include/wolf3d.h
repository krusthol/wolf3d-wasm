#ifndef WOLF3D_H
# define WOLF3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "wasm-sdl2.h"

/*struct s_img_data	img_data;
  	struct s_img_data	img_data_nesw[4];
	struct s_img_data	*idp;
	struct s_grid		grid;
	struct s_grid		*g;
	struct s_player		player;
	struct s_player		*p;*/

typedef struct			s_view
{
	void				*mlx;
	void				*window;
	void				*img;
	void				*txt_nesw[4];
	int					*nesw[4];
	int					minimap_on;
	int					textures_on;
	int					shading_on;
	int					threading_on;
	long double			fisheye1280[1280];
	long double			rads360[360];
	long double			rads7680[7680];
	long double			tans7680[7680];
	unsigned int		wall_colors[600];
}						t_view;

void		populate_color_tables(unsigned int wall_colors[600]);
void		populate_doubles_tables(long double rads360[360], long double
rads7680[7680], long double tans7680[7680], long double fisheye1280[1280]);
void		initialize_states(t_view *view);
void		initialize_view(t_view *view, char *title);

#endif

#ifndef WOLF3D_H
# define WOLF3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "ft_str.h"
# include "wasm-sdl2.h"

# define BUFF_SIZE 3200
# define MAPDATA "assets/1"

enum					e_err{MAP_CONTENT = 1, MAP_FILE, MAP_SIZE, MAP_SHAPE,
	INVALID_TEXTURE, MEMORY_ERROR, TEXTURE_LOAD_FAILURE, MAP_DIRECTORY};

/*	disabled from t_view
  	struct s_img_data	img_data;
  	struct s_img_data	img_data_nesw[4];
	struct s_img_data	*idp;
*/

typedef struct			s_player
{
	long double			rad;
	int					r_index;
	int					ray_xy[2];
	int					ray_dist;
	int					x;
	int					y;
	int					move_look;
	int					move_facing;
	int					is_down;
	int					is_right;
	int					rotating[2];
	int					rotation_velo;
	int					stepping[2];
	int					stepping_velo;
}						t_player;

typedef struct			s_grid
{
	char				**grid;
	int					rows;
	int					cols;
}						t_grid;

typedef struct			s_view
{
	//void				*mlx;
	//void				*window;
	//void				*img;

	struct SDL_Window	*win;
	struct SDL_Surface	*surf;
	struct SDL_Renderer *ren;
	struct SDL_Texture	*tex;

	uint32_t			*pix;
	int 				pix_limit;

	int 				quit;
	struct _TTF_Font	*ibm_font;
	struct SDL_Surface	*font_surf;
	SDL_Color 			color_white;
	SDL_Event 			event;

	struct SDL_Surface	*txt_nesw[4];
	unsigned int		*nesw[4];

	struct s_grid		grid;
	struct s_grid		*g;
	struct s_player		player;
	struct s_player		*p;

	int					minimap_on;
	int					textures_on;
	int					shading_on;

	long double			fisheye1280[1280];
	long double			rads360[360];
	long double			rads7680[7680];
	long double			tans7680[7680];
	unsigned int		wall_colors[600];
}						t_view;


/* from main.c */
void					populate_color_tables(unsigned int wall_colors[600]);
void					populate_doubles_tables(long double rads360[360], long double
rads7680[7680], long double tans7680[7680], long double fisheye1280[1280]);
void					initialize_states(t_view *view);
void					initialize_view(t_view *view, char *title);

/* from init.c */
void					init_systems(t_view *view);
void					init_memory(t_view *view);

/* from console.c */
int						print_error(int code);
void					close_and_exit(int fd_to_close, int code);
void					print_usage_and_exit(int code);
int						print_error(int code);
void					print_intro(char *file_arg);

// gnl.c
int						get_next_line(const int fd, char **line);

// grid.c
char					**grid_set(int rows, int columns, char *data);
void					assign_px_py(t_grid *grid, t_player *p);

// file.c
int						check_mapfile(char *file_arg, t_view *view);

/* from texture.c
void					draw_textured_walls(int *walls, int *facing, int *txt_offset, t_view *view);*/
void					load_textures(t_view *view);

#endif

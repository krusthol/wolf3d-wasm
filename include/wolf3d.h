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
enum					e_facing{NORTH, EAST, SOUTH, WEST};

/*	disabled from t_view
  	struct s_img_data	img_data;
  	struct s_img_data	img_data_nesw[4];
	struct s_img_data	*idp;
*/

typedef struct			s_line
{
	int					x1;
	int					x2;
	int					y1;
	int					y2;
	int					color;
	int					fx;
	int					fy;
	int					px;
	int					py;
}						t_line;

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

	unsigned int		*pix;
	unsigned int		pix_limit;

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
	int 				print_player_on;

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
void					print_keyhelp(void);
int						print_error(int code);
void					close_and_exit(int fd_to_close, int code);
void					print_intro(char *file_arg);

// gnl.c
int						get_next_line(const int fd, char **line);

// grid.c
int						hits_wall(t_grid *grid, int x, int y);
void					assign_clip_values(int *cx, int *cy, int move_facing);
void					stop_velocity(t_player *p);
char					**grid_set(int rows, int columns, char *data);
void					assign_px_py(t_grid *grid, t_player *p);

// file.c
int						check_mapfile(char *file_arg, t_view *view);

// texture.c
void					draw_textured_walls(const int *walls, int *facing, const int *txt_offset, t_view *view);
void					load_textures(t_view *view);

// geometry.c
int						cos_distance(int res, int p, long double rad);
int						sin_distance(int res, int p, long double rad);
int						pick_closer(t_player *p, int vert[2], int horz[2], int res[2]);

// intersect.c
int						check_vert_intersect(t_grid *grid, t_player *p, int res[2], long double tans[7680]);
int						check_horz_intersect(t_grid *grid, t_player *p, int res[2], long double tans[7680]);

// casting.c
void					cast_walls(int i, t_grid *grid, t_player *p, t_view *view);

// movement.c
int						calc_movements(t_view *view);

// input.c
void					process_input(t_view *view);

// pixel.c
unsigned int			color(unsigned int percent, unsigned int color);
void					pixel_to_img(unsigned int *buffer, unsigned int x, unsigned int y, unsigned int color);
void					shaded_roof(int x, int from, t_view *view);
void					shaded_floor(int x, int to, t_view *view);

// line.c
void					line(t_line *l, t_view *v);
void					offset_line(int x, int y, t_line *l);

// minimap.c
void					draw_minimap(t_view *view);

// wall_drawing.c
void					draw_walls(int *walls, int *facing, int *txt_offset, t_view *view);

#endif

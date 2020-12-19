#ifndef PROPERTIES_H
#define PROPERTIES_H

enum e_elem_types {BUTTON, PROGRESS_BAR, SLIDER, PALETTE};
enum e_align {ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT};
enum e_color {RED, GREEN, BLUE};
enum e_lock {UNLOCKED, LOCKED};
enum e_can {NO, YES};

typedef struct	s_can {
	int 				scroll;
	int 				click;
}				t_can;

typedef struct	s_style {
	int					fg_color;
	int 				bg_color;
	int 				border_color;
	int 				bar_color;
	int 				border_size;
	int 				text_color;
	int 				text_off_x;
	int 				text_off_y;
	char*				font;
	int 				font_size;
	int 				align;
}				t_style;

typedef struct	s_size {
	int					width;
	int					height;
}				t_size;

typedef struct	s_position {
	int 				x;
	int					y;
}				t_position;

typedef struct	s_pro {
	struct s_style		sty;
	struct s_size		siz;
	struct s_position	pos;
	struct s_can		can;
	int 				elem_type;
}				t_pro;

void					default_style(t_pro *pro);
int 					cols2hx (int red, int green, int blue);
int 					hx2col(int hex, int color);
int 					center(int window_size, int element_size);
#endif

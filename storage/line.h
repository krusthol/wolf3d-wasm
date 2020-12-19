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

typedef struct 			s_line
{
	int					x1;
	int 				x2;
	int 				y1;
	int 				y2;
	int 				fx;
	int 				fy;
	int 				px;
	int 				py;
	uint32_t 			color;
	struct SDL_Surface 	*buff;
    int                 blit;
    struct SDL_Surface  *src;
    struct SDL_Surface  *dst;
	int					segment;
	int					empty;
	int					rope;
}						t_line;

void                    render_line(t_line *l);
void	        		delta2d_rope(t_line *line, SDL_Surface *blit_dst);

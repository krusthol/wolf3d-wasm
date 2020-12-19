/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta-2d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusthol <krusthol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:55:41 by krusthol          #+#    #+#             */
/*   Updated: 2020/12/01 17:02:01 by krusthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELTA_2D_H
# define DELTA_2D_H

#if __EMSCRIPTEN__
# include       <emscripten/emscripten.h>
#endif

# include       "stdlib.h"
# include       "stdio.h"
# include       <SDL2/SDL.h>
# include       <SDL2/SDL_ttf.h>
# include       <SDL2/SDL_image.h>
# include       "properties.h"
# include       "wave.h"
# include       "line.h"

/* from main.c */
int		        error_exit(const char* error, int code);
double			time_now(void);

/* from game.c */
void	        spinning_init(void);
void	        spinning_loop(void);
void	        climb_init(void);
void	        climb_loop(void);

#endif
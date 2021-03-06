/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subrt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:22:15 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/18 21:25:32 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBRT_H
# define SUBRT_H

# include "SDL2/SDL.h"

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Renderer	*rend;
	SDL_Texture		*txt;
	void			*pxl;
	int				pitch;
	int				x;
	int				y;
}					t_window;

typedef struct		s_calc
{
	float			a;
	float			b;
	float			c;
	float			delta;
	float			sqt;
	float			t0;
	float			t1;
}					t_calc;

typedef struct		s_input
{
	SDL_Event		ev;
	unsigned char	*key;
	unsigned char	oldkey[282];
	int				x;
	int				y;
	int				button;
}					t_input;

typedef struct		s_camera
{
	t_vec			pos;
	t_point			sc;
	t_point			x;
	t_point			y;
}					t_camera;

typedef struct		s_object
{
	void			**item;
	t_light			*light;
	t_camera		*camera;
	int				nb_item;
	int				nb_light;
	int				nb_camera;
	char			**texture;
	char			**normal;
	int				nb_texture;
	int				nb_normal;
	int				index[3];
	int				type_index;
}					t_object;

typedef struct		s_ray
{
	t_vec			tmp;
	unsigned int	color[2];
	void			*obj;
	float			dist[2];
	int				bounce;
}					t_ray;

typedef struct		s_scene
{
	int				fd;
	unsigned int	error_line;
}					t_scene;

#endif

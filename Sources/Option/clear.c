/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:02:33 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/18 20:44:52 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		clear_texture(t_data *data, t_tga **tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_texture - 1 && (tofree))
		(tofree)[i] != NULL ? free_tga((tofree)[i]) : 0;
	if (tofree != NULL)
		free((tofree));
}

static void		clear_obj_item(t_data *data, t_object tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_item - 1 && (tofree).item)
		tofree.item[i] != NULL ? free(tofree.item[i]) : 0;
	if (tofree.item != NULL)
		free(tofree.item);
}

static void		clear_normal(t_data *data, t_tga **tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_normal - 1)
		(tofree)[i] != NULL ? free_tga((tofree)[i]) : 0;
	if (data->normal)
		free((tofree));
	i = -1;
	while (i++ < data->obj.nb_normal - 1)
		data->obj.normal[i] != NULL ? free(data->obj.normal[i]) : 0;
	if (data->obj.normal != NULL)
		free(data->obj.normal);
}

int				clear_memory(t_data *data)
{
	clear_texture(data, data->texture);
	clear_obj_item(data, data->obj);
	clear_normal(data, data->normal);
	data->obj.camera != NULL ? free(data->obj.camera) : 0;
	data->obj.light != NULL ? free(data->obj.light) : 0;
	SDL_DestroyTexture(data->window.txt);
	SDL_DestroyWindow(data->window.window);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:32:44 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/18 17:06:11 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		preset_cam(t_data *data, int index)
{
	float	coef;

	(data->obj.camera[index]).sc =
		add_vec((data->obj.camera[index]).pos.origin,
			fill_vec(-0.5, -0.5, 0.5));
	if (data->window.x >= data->window.y)
	{
		coef = (float)data->window.x / (float)data->window.y;
		(data->obj.camera[index]).x = fill_vec(coef / data->window.x, 0, 0);
		(data->obj.camera[index]).y = fill_vec(0, 1.0 / data->window.y, 0);
		(data->obj.camera[index]).sc = add_vec((data->obj.camera[index]).sc,
			fill_vec((1 - coef) / 2.0, 0, 0));
	}
	else
	{
		coef = (float)data->window.y / (float)data->window.x;
		(data->obj.camera[index]).x = fill_vec(1.0 / data->window.x, 0, 0);
		(data->obj.camera[index]).y = fill_vec(0, coef / data->window.y, 0);
		(data->obj.camera[index]).sc = add_vec((data->obj.camera[index]).sc,
			fill_vec(0, (1 - coef) / 2, 0));
	}
}

static void		apply_rot(t_data *data, t_point base,
	t_point direction, int index)
{
	if (direction.y != base.y && direction.z != base.z)
		rot_init_cam_x(data, &base, &direction, index);
	if (direction.x != base.x && direction.z != base.z)
		rot_init_cam_y(data, &base, &direction, index);
	if (direction.x != base.x && direction.y != base.y)
		rot_init_cam_z(data, &base, &direction, index);
}

int				initialize_cam(t_data *data)
{
	int			index;
	t_point		direction;
	t_point		base;

	index = 0;
	while (index < data->obj.nb_camera)
	{
		direction = normalize((data->obj.camera[index]).pos.direction);
		base = fill_vec(0, 0, 1);
		preset_cam(data, index);
		apply_rot(data, base, direction, index);
		index++;
	}
	return (0);
}

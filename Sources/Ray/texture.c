/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:32 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/18 17:49:13 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			find_size(t_data data, void *obj, int choose)
{
	int index;

	if (choose)
	{
		index = (((t_sphere *)obj)->effect.id_texture);
		return (((data.texture[index])->w << 16) + (data.texture[index])->h);
	}
	else
	{
		index = (((t_sphere *)obj)->effect.id_normal);
		return (((data.normal[index])->w << 16) + (data.normal[index])->h);
	}
}

t_point		texture_plan(t_data *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	t_point ontexture;
	t_point u;
	t_point v;

	wh = find_size(*data, obj, choose);
	u = fill_vec(((t_plan *)obj)->origin.direction.y,
		((t_plan *)obj)->origin.direction.z,
		-((t_plan *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_plan *)obj)->origin.direction);
	ontexture.y = dot_product(ray.origin, u) * (wh & 0xFFFF) +
		((wh & 0xFFFF) >> 1);
	ontexture.x = dot_product(ray.origin, v) * (wh >> 16) + ((wh >> 16) >> 1);
	while (ontexture.x < 0 || ontexture.x >= (wh >> 16))
		ontexture.x += (ontexture.x < 0 ? (wh >> 16) - 1 : -(wh >> 16) - 1);
	while (ontexture.y < 0 || ontexture.y >= (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ?
			(wh & 0xFFFF) - 1 : -(wh & 0xFFFF) - 1);
	return (ontexture);
}

t_point		texture_sphere(t_data *data, void *obj, t_vec ray, int choose)
{
	t_point	ontexture;
	int		wh;
	float	phi;
	float	theta;

	wh = find_size(*data, obj, choose);
	theta = acos(sub_vec(ray.origin,
		((t_sphere *)obj)->origin.origin).y / ((t_sphere *)obj)->rayon);
	phi = atan2(sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_sphere *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontexture.x = (int)((((wh & 0xFFFF0000) >> 16) - 1) * (phi / (2 * M_PI)));
	ontexture.y = (int)(((wh & 0xFFFF) - 1) * ((M_PI - theta) / (M_PI)));
	while (ontexture.x < 0 || ontexture.x > (wh & 0xFFFF0000) >> 16)
		ontexture.x += (ontexture.x < 0 ?
			(wh & 0xFFFF0000) >> 16 : -((wh & 0xFFFF0000) >> 16));
	while (ontexture.y < 0 || ontexture.y > (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) : -((wh & 0xFFFF)));
	ontexture.y = (wh & 0xFFFF) - ontexture.y;
	return (ontexture);
}

t_point		texture_cylinder(t_data *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	float	phi;
	t_point ontexture;
	t_point	u;
	t_point	v;

	wh = find_size(*data, obj, choose);
	u = fill_vec(((t_cylinder *)obj)->origin.direction.y,
		((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	v = cross_vec(u, ((t_base *)obj)->origin.direction);
	phi = atan2(sub_vec(ray.origin, ((t_base *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_base *)obj)->origin.origin).x);
	ontexture.x = (int)((((wh & 0xFFFF0000) >> 16) - 1) * (phi / (2 * M_PI)));
	ontexture.y = ((float)((int)ray.origin.y) - ray.origin.y) * (wh & 0xFFFF);
	while (ontexture.x < 0 || ontexture.x > (wh & 0xFFFF0000) >> 16)
		ontexture.x += (ontexture.x < 0 ? (wh & 0xFFFF0000) >> 16 :
			-((wh & 0xFFFF0000) >> 16));
	while (ontexture.y < 0 || ontexture.y > (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) : -((wh & 0xFFFF)));
	return (ontexture);
}

t_point		texture_cone(t_data *data, void *obj, t_vec ray, int choose)
{
	int		wh;
	t_point ontexture;
	t_point	u;
	float	phi;

	wh = find_size(*data, obj, choose);
	u = fill_vec(((t_cylinder *)obj)->origin.direction.y,
		((t_cylinder *)obj)->origin.direction.z,
		-((t_cylinder *)obj)->origin.direction.x);
	phi = atan2(sub_vec(ray.origin, ((t_cylinder *)obj)->origin.origin).z,
		sub_vec(ray.origin, ((t_cylinder *)obj)->origin.origin).x);
	while (phi < 0.0)
		phi += 2 * M_PI;
	ontexture.x = (int)((((wh & 0xFFFF0000) >> 16) - 1) * (phi / (2 * M_PI)));
	ontexture.y = ((float)((int)ray.origin.y) - ray.origin.y) * (wh & 0xFFFF);
	while (ontexture.x < 0 || ontexture.x > (wh & 0xFFFF0000) >> 16)
		ontexture.x += (ontexture.x < 0 ? (wh & 0xFFFF0000) >> 16 :
			-((wh & 0xFFFF0000) >> 16));
	while (ontexture.y < 0 || ontexture.y > (wh & 0xFFFF))
		ontexture.y += (ontexture.y < 0 ? (wh & 0xFFFF) : -((wh & 0xFFFF)));
	return (ontexture);
}

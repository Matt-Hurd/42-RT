/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 23:33:40 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/17 23:33:59 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_sphere(t_data *d, t_list *list)
{
	t_sphere	*sphere;
	t_list		*ret;

	sphere = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	parse_props(list, &sphere->props);
	if (!d->s)
		d->s = (t_scene *)ft_memalloc(sizeof(t_scene));
	while (list && !ft_strchr(list->content, '['))
	{
		set_radius(list, sphere, SPHERE);
		list = list->next;
	}
	ret = ft_lstnew(sphere, sizeof(t_sphere));
	ret->content_size = SPHERE;
	ft_lstadd(&d->s->objects, ret);
}

void	parse_plane(t_data *d, t_list *list)
{
	t_plane		*plane;
	t_list		*ret;
	float		global_matrix[4][4];
	t_vec3		n;

	n.x = 0;
	n.y = 0;
	n.z = -1;
	ft_make_identity_matrix(global_matrix);
	plane = (t_plane *)ft_memalloc(sizeof(t_plane));
	parse_props(list, &plane->props);
	ft_tr_rotate(global_matrix,
		plane->props.rot.x,
		plane->props.rot.y,
		plane->props.rot.z);
	ft_vec_mult_mat(&n, global_matrix, &plane->props.rot);
	ret = ft_lstnew(plane, sizeof(t_plane));
	ret->content_size = PLANE;
	ft_lstadd(&d->s->objects, ret);
}

void	parse_cylinder(t_data *d, t_list *list)
{
	t_cylinder	*cylinder;
	t_list		*ret;
	float		global_matrix[4][4];
	t_vec3		n;

	n.x = 0;
	n.y = -1;
	n.z = 0;
	cylinder = (t_cylinder *)ft_memalloc(sizeof(t_cylinder));
	parse_props(list, &cylinder->props);
	while (list && !ft_strchr(list->content, '['))
	{
		set_radius(list, cylinder, CYLINDER);
		list = list->next;
	}
	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix,
		cylinder->props.rot.x,
		cylinder->props.rot.y,
		cylinder->props.rot.z);
	ft_vec_mult_mat(&n, global_matrix, &cylinder->props.rot);
	ret = ft_lstnew(cylinder, sizeof(t_cylinder));
	ret->content_size = CYLINDER;
	ft_lstadd(&d->s->objects, ret);
}

void	parse_cone(t_data *d, t_list *list)
{
	t_cone		*cone;
	t_list		*ret;
	float		global_matrix[4][4];
	t_vec3		n;

	n.x = 0;
	n.y = -1;
	n.z = 0;
	cone = (t_cone *)ft_memalloc(sizeof(t_cone));
	parse_props(list, &cone->props);
	while (list && !ft_strchr(list->content, '['))
	{
		set_radius(list, cone, CONE);
		list = list->next;
	}
	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix,
		cone->props.rot.x,
		cone->props.rot.y,
		cone->props.rot.z);
	ft_vec_mult_mat(&n, global_matrix, &cone->props.rot);
	ret = ft_lstnew(cone, sizeof(t_cone));
	ret->content_size = CONE;
	ft_lstadd(&d->s->objects, ret);
}

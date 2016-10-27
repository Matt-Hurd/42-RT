/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/26 22:58:54 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_screen(t_data *d)
{
	int			z;
	t_ray		r;
	float		global_matrix[4][4];
	t_vec3		point;
	t_recurse	*recurse;

	recurse = (t_recurse *)ft_memalloc(sizeof(t_recurse));
	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix, d->s->cam_rot.x, d->s->cam_rot.y,
		d->s->cam_rot.z);
	ft_tr_translate(global_matrix, d->s->cam_pos.x, d->s->cam_pos.y,
		d->s->cam_pos.z);
	z = -1;
	while (++z < d->s->size.y * d->s->size.x)
	{
		clear_color(&recurse->color);
		scale_vector(1, &d->s->cam_pos, &r.start);
		point.x = (z % d->s->size.x) - d->s->size.x / 2;
		point.y = (z / d->s->size.x) - d->s->size.y / 2;
		point.z = d->s->fov * 10;
		ft_vec_mult_mat(&point, global_matrix, &point);
		sub_vect(&point, &r.start, &r.dir);
		normalize_vector(&r.dir);
		recurse->coef = 1.0;
		recurse->r = r;
		recurse->depth = 0;
		ray_trace(d, recurse);
		d->image[(z / d->s->size.x)][(z % d->s->size.x)] = recurse->color;
	}
}

void	draw_reload(t_data *d)
{
	d->expired = 0;
	draw_screen(d);
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	d->img =
		mlx_new_image(d->mlx, d->s->size.x + 100, d->s->size.y + 100);
	d->pixel_img =
		mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	post_process(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

int		expose_hook(t_data *d)
{
	if (d->img && !d->expired)
		mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	else
		draw_reload(d);
	return (0);
}

void	draw_everything(t_data *d)
{
	int y;

	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->s->size.x,
		d->s->size.y, d->s->name);
	d->image = ft_memalloc(sizeof(t_rgb) * d->s->size.y);
	y = -1;
	while (++y < d->s->size.y)
		d->image[y] = ft_memalloc(sizeof(t_rgb) * d->s->size.x);
	d->s->maxdepth = (d->s->maxdepth) ? d->s->maxdepth : 16;
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_hook(d->win, 2, 3, key_hook, d);
	mlx_loop(d->mlx);
}

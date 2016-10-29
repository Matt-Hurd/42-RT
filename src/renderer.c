/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/29 05:26:23 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*do_recurse(void *args)
{
	int			z;
	t_recurse	*rec;
	t_vec3		point;
	t_ray		r;
	t_args		*a;

	a = (t_args *)args;
	rec = (t_recurse *)ft_memalloc(sizeof(t_recurse));
	z = a->d->s->size.x * a->start.y + a->start.x;
	while (++z < a->d->s->size.x * a->end.y + a->end.x)
	{
		clear_color(&rec->color);
		scale_vector(1, &a->d->s->cam_pos, &r.start);
		point.x = (z % a->d->s->size.x) - a->d->s->size.x / 2;
		point.y = (z / a->d->s->size.x) - a->d->s->size.y / 2;
		point.z = a->d->s->fov * 10;
		ft_vec_mult_mat(&point, a->global, &point);
		sub_vect(&point, &r.start, &r.dir);
		normalize_vector(&r.dir);
		rec->coef = 1.0;
		rec->r = r;
		rec->depth = 0;
		ray_trace(a->d, rec);
		a->d->image[(z / a->d->s->size.x)][(z % a->d->s->size.x)] = rec->color;
	}
	free(args);
	return (NULL);
}

void	draw_screen(t_data *d)
{
	int		x;
	int		z;
	t_args	*a;

	x = -1;
	while (++x < 16)
	{
		a = (t_args *)ft_memalloc(sizeof(t_args));
		ft_make_identity_matrix(a->global);
		ft_tr_rotate(a->global, d->s->cam_rot.x, d->s->cam_rot.y,
			d->s->cam_rot.z);
		ft_tr_translate(a->global, d->s->cam_pos.x, d->s->cam_pos.y,
			d->s->cam_pos.z);
		z = d->s->size.x * d->s->size.y / 16;
		a->d = d;
		a->start.x = (x * z) % d->s->size.x - 1;
		a->start.y = (x * z) / d->s->size.x;
		a->end.x = ((x + 1) * z) % d->s->size.x;
		a->end.y = ((x + 1) * z) / d->s->size.x;
		if (pthread_create(&d->render_threads[x], NULL, do_recurse, a))
			ft_error("ERROR! Unable to create render thread.");
	}
}

void	draw_reload(t_data *d)
{
	int x;

	if (d->drawing)
		return ;
	d->drawing = 1;
	d->expired = 0;
	draw_screen(d);
	x = -1;
	while (++x < 16)
		pthread_join(d->render_threads[x], NULL);
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	d->img =
		mlx_new_image(d->mlx, d->s->size.x + 100, d->s->size.y + 100);
	d->pixel_img =
		mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	post_process(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	d->drawing = 0;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 08:20:47 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**TODO:
**	Check error handling for all input files
*/

void	*do_recurse(void *args)
{
	int			z;
	t_recurse	*rec;
	t_vec3		point;
	t_args		*a;

	a = (t_args *)args;
	rec = (t_recurse *)ft_memalloc(sizeof(t_recurse));
	z = a->d->s->size.x * a->start.y + a->start.x;
	while (++z < a->d->s->size.x * a->end.y + a->end.x)
	{
		clear_color(&rec->color);
		point.x = (z % a->d->s->size.x) - a->d->s->size.x / 2;
		point.y = (z / a->d->s->size.x) - a->d->s->size.y / 2;
		point.z = a->d->s->fov * 10;
		if (a->d->s->aa == 2)
			ssaa(a, point, rec, 1);
		else
			regular_pixel(a, point, rec);
		a->d->image[(z / a->d->s->size.x)][(z % a->d->s->size.x)] = rec->color;
		a->d->s->count++;
	}
	free(rec);
	free(args);
	return (NULL);
}

void	draw_screen(t_data *d)
{
	int		x;
	int		z;
	t_args	*a;

	x = -1;
	while (++x < d->thread_count)
	{
		a = (t_args *)ft_memalloc(sizeof(t_args));
		ft_make_identity_matrix(a->global);
		ft_tr_rotate(a->global, d->s->cam_rot.x, d->s->cam_rot.y,
			d->s->cam_rot.z);
		ft_tr_translate(a->global, d->s->cam_pos.x, d->s->cam_pos.y,
			d->s->cam_pos.z);
		z = d->s->size.x * d->s->size.y / d->thread_count;
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
	d->s->count = 0;
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	d->img =
		mlx_new_image(d->mlx, d->s->size.x + 100, d->s->size.y + 100);
	d->pixel_img =
		mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	draw_screen(d);
	x = -1;
	while (++x < d->thread_count)
		pthread_join(d->render_threads[x], NULL);
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

	init_perlin();
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->s->size.x,
		d->s->size.y, d->s->name);
	d->image = ft_memalloc(sizeof(t_rgb) * d->s->size.y);
	y = -1;
	while (++y < d->s->size.y)
		d->image[y] = ft_memalloc(sizeof(t_rgb) * d->s->size.x);
	d->s->maxdepth = (d->s->maxdepth) ? d->s->maxdepth : 16;
	d->thread_count = MIN(16, d->s->size.y * d->s->size.x);
	d->render_threads = (pthread_t *)ft_memalloc(sizeof(pthread_t)
		* d->thread_count);
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_hook(d->win, 2, 3, key_hook, d);
	mlx_loop(d->mlx);
}

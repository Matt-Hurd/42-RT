/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgfx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:42:11 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/29 08:27:06 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGFX_H
# define LIBGFX_H
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# define ABS(x) ((x > 0) ? x : x * -1)
# define SQ(x) (x * x)

typedef struct	s_rgb
{
	float	r;
	float	g;
	float	b;
}				t_rgb;

typedef struct	s_vec2
{
	short	x;
	short	y;
}				t_vec2;

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct	s_vertex
{
	t_vec3	*local;
	t_vec3	*world;
	t_vec3	*aligned;
}				t_vertex;

typedef struct	s_props
{
	t_vec3	pos;
	t_vec3	rot;
	float	density;
	t_rgb	color;
	float	reflect;
	float	radiance;
	float	trans;
	float	gloss;
}				t_props;

typedef struct	s_plane
{
	t_props props;
}				t_plane;

typedef struct	s_cylinder
{
	t_props	props;
	float	radius;
}				t_cylinder;

typedef struct	s_cone
{
	t_props	props;
	float	radius;
}				t_cone;

typedef struct	s_sphere
{
	t_props	props;
	float	radius;
}				t_sphere;

typedef struct	s_light
{
	t_props	props;
}				t_light;

typedef struct	s_ray
{
	t_vec3	start;
	t_vec3	dir;
	t_rgb	color;
}				t_ray;

typedef struct	s_recurse
{
	t_list	*closest;
	t_light	current_light;
	t_ray	light_ray;
	t_rgb	color;
	char	lit;
	float	coef;
	t_ray	r;
	t_vec3	n;
	int		depth;
	float	light;
}				t_recurse;

typedef struct	s_scene
{
	char	*name;
	float	fov;
	t_vec2	size;
	t_vec3	cam_pos;
	t_vec3	cam_rot;
	t_list	*objects;
	int		maxdepth;
	int		count;
	char	aa;
}				t_scene;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pixel_img;
	int			bpp;
	int			s_line;
	int			ed;
	char		expired;
	char		drawing;
	t_rgb		**image;
	t_scene		*s;
	pthread_t	*input_thread;
	pthread_t	render_threads[16];
}				t_data;

enum			e_object
{
	NONE,
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	LIGHT
};

void			ft_mat_copy(float source[4][4], float dest[4][4]);
void			ft_mat_mult(float m1[4][4], float m2[4][4], float d[4][4]);
void			ft_vec_mult_mat(t_vec3 *s, float mat[4][4], t_vec3 *d);
void			ft_tr_translate(float m[4][4], float tx, float ty, float tz);
void			ft_tr_scale(float matrix[4][4], float sx, float sy, float sz);
void			ft_tr_rotate(float matrix[4][4], float ax, float ay, float az);
void			ft_make_identity_matrix(float matrix[4][4]);
t_vec3			*ft_make_vec3(int x, int y, int z);
t_vertex		*ft_make_vertex(int x, int y, int z);
void			put_pixel(t_data *d, int x, int y, t_rgb color);
void			sub_vect(t_vec3 *v1, t_vec3 *v2, t_vec3 *d);
float			dot_vect(t_vec3 *v1, t_vec3 *v2);
void			scale_vector(float c, t_vec3 *v, t_vec3 *d);
void			add_vect(t_vec3 *v1, t_vec3 *v2, t_vec3 *d);
#endif

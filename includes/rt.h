/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:06:16 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/27 01:00:25 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "mlx.h"
# include "libft.h"
# include "libgfx.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>




#include <stdio.h>







/*
** KEYS
*/

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78

# define KEY_ROT_X_U 86
# define KEY_ROT_X_D 83
# define KEY_ROT_Y_U 87
# define KEY_ROT_Y_D 84
# define KEY_ROT_Z_U 88
# define KEY_ROT_Z_D 85

void		parse_file(t_data *d, char *filename);
void		draw_everything(t_data *d);
int			key_hook(int keycode, t_data *d);
void		draw_reload(t_data *d);
void		ft_exit(void);
void		ft_error(char *s);
void		ft_error_unknown(void);
void		parse_triple(char *triple, t_vec3 *ref);
void		parse_sphere(t_data *d, t_list *list);
void		parse_color(char *color, t_rgb *ref);
void		parse_cone(t_data *d, t_list *list);
void		parse_cylinder(t_data *d, t_list *list);
void		parse_plane(t_data *d, t_list *list);
void		parse_props(t_list *list, t_props *props);
void		parse_light(t_data *d, t_list *list);
void		normalize_vector(t_vec3 *v);
void		calc_light(t_data *d, t_recurse *rec, t_list *curr);
void		clear_color(t_rgb *color);
void		set_radius(t_list *list, void *obj, int type);
void		find_light(t_data *d, float t, t_recurse *rec);
void		color_point(t_recurse *rec);
void		post_process(t_data *d);
void		create_input_thread(t_data *d);
void		ray_trace(t_data *d, t_recurse *rec);
float		calc_blinn(t_recurse *rec);
void		handle_trans(t_data *d, t_recurse *rec);

int			intersect_shape(t_ray *r, void *s, int type, float *t);
int			intersect_cylinder(t_ray *r, t_cylinder *c, float *t);
int			intersect_plane(t_ray *r, t_plane *p, float *t);
int			intersect_cone(t_ray *r, t_cone *c, float *t);
int			intersect_sphere(t_ray *r, t_sphere *s, float *t);

void		normal_shape(t_ray *r, t_vec3 *n, t_list *s);
void		normal_sphere(t_ray *r, t_sphere *s, t_vec3 *n);
void		normal_plane(t_ray *r, t_plane *p, t_vec3 *n);
void		normal_cylinder(t_ray *r, t_cylinder *c, t_vec3 *n);
void		normal_cone(t_ray *r, t_cone *c, t_vec3 *n);

void		print_vec3(t_vec3 v, float scale);
void		print_scene_info(t_data *d);
void		print_RGB(t_rgb rgb);
void		print_properties(t_props p);
void		print_sphere_info(t_sphere *sphere);
void		print_plane_info(t_plane *plane);
void		print_cone_info(t_cone *cone);
void		print_cylinder_info(t_cylinder *cylinder);
void		print_light_info(t_light *light);
int			parse_misc(char **split, int c, t_data *d);
int			modify_object(char **s, int c, t_data *d);
int			add_object(char **s, t_data *d);
int			del_object(char **s, t_data *d);
t_list		*get_object(t_data *d, int num);
void		display_help(void);

#endif

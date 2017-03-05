/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:06:16 by mhurd             #+#    #+#             */
/*   Updated: 2017/03/05 14:56:30 by mhurd            ###   ########.fr       */
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

typedef struct	s_args
{
	t_data	*d;
	t_vec2	start;
	t_vec2	end;
	float	global[4][4];
	t_rgb	colors[4];
}				t_args;

void			draw_everything(t_data *d);
void			draw_reload(t_data *d);
int				key_hook(int keycode, t_data *d);
void			ft_exit(void);
void			ft_error(char *s);
void			ft_error_unknown(void);
void			normalize_vector(t_vec3 *v);
void			calc_light(t_data *d, t_recurse *rec, t_list *curr);
void			set_radius(t_list *list, void *obj, int type);
void			find_light(t_data *d, float t, t_recurse *rec);
void			color_point(t_recurse *rec);
void			post_process(t_data *d);
void			create_input_thread(t_data *d);
void			ray_trace(t_data *d, t_recurse *rec);
float			handle_trans(t_data *d, t_recurse *rec);
void			pass_through(t_data *d, t_recurse *r, float *o, t_list *c2);
void			ssaa(t_args *a, t_vec3 point, t_recurse *rec, int depth);
double			noise(double x, double y, double z);
void			init_perlin(void);
void			regular_pixel(t_args *a, t_vec3 point, t_recurse *rec);
int				color_to_int(t_rgb color);

void			parse_file(t_data *d, char *filename);
void			parse_triple(char *triple, t_vec3 *ref);
void			parse_sphere(t_data *d, t_list *list);
void			parse_color(char *color, t_rgb *ref);
void			parse_cone(t_data *d, t_list *list);
void			parse_cylinder(t_data *d, t_list *list);
void			parse_plane(t_data *d, t_list *list);
void			parse_props(t_list *list, t_props *props);
void			parse_light(t_data *d, t_list *list);
void			parse_model(t_data *d, t_list *list);
void			parse_float_trip(t_vec3 *dest, char *line);

void			scale_color(float scale, t_rgb *c1, t_rgb *c2);
void			add_colors(t_rgb *c1, t_rgb *c2, t_rgb *c3);
void			sub_colors(t_rgb *c1, t_rgb *c2, t_rgb *c3);
void			clear_color(t_rgb *color);

int				intersect_shape(t_ray *r, t_list *s, float *t, char intern);
int				intersect_cylinder(t_ray *r, t_cylinder *c, float *t, char i);
int				intersect_plane(t_ray *r, t_plane *p, float *t);
int				intersect_cone(t_ray *r, t_cone *c, float *t, char intern);
int				intersect_sphere(t_ray *r, t_sphere *s, float *t, char intern);
int				intersect_model(t_ray *r, t_model *m, float *t);

void			normal_shape(t_ray *r, t_vec3 *n, t_list *s, char intern);
void			normal_sphere(t_ray *r, t_sphere *s, t_vec3 *n, char intern);
void			normal_plane(t_ray *r, t_plane *p, t_vec3 *n);
void			normal_cylinder(t_ray *r, t_cylinder *c, t_vec3 *n, char i);
void			normal_cone(t_ray *r, t_cone *c, t_vec3 *n, char intern);
void			normal_model(t_ray *r, t_model *m, t_vec3 *n, char intern);

void			print_vec3(t_vec3 v, float scale);
void			print_scene_info(t_data *d);
void			print_rgb(t_rgb rgb);
void			print_properties(t_props p);
void			print_sphere_info(t_sphere *sphere);
void			print_plane_info(t_plane *plane);
void			print_cone_info(t_cone *cone);
void			print_cylinder_info(t_cylinder *cylinder);
void			print_light_info(t_light *light);
void			print_model_info(t_model *model);

int				parse_misc(char **split, int c, t_data *d);
int				modify_object(char **s, int c, t_data *d);
int				add_object(char **s, t_data *d);
int				del_object(char **s, t_data *d);
t_list			*get_object(t_data *d, int num);
void			display_help(void);
void			update_model(t_model *m);
void			validate_scene(t_data *d);

int				set_props(char **s, t_sphere *obj);
void			color_ambient(float ambient, t_recurse *rec);
float			handle_mats(t_recurse *rec);
void 			print_progress(t_args *a);
void			clear_loading();
#endif

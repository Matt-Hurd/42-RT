/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:15:36 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 08:50:44 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_model(t_model *m, char *line)
{
	char	**split;
	int		x;

	split = ft_strsplit(line, ' ');
	if (ft_count_words(line, ' ') != 4)
		ft_error("Invalid model file");
	m->vc = ft_atoi(split[1]);
	m->vnc = ft_atoi(split[2]);
	m->face_count = ft_atoi(split[3]);
	m->vertices = ft_memalloc(sizeof(t_vec3) * m->vc);
	m->vertices_origin = ft_memalloc(sizeof(t_vec3) * m->vc);
	m->normals = ft_memalloc(sizeof(t_vec3) * m->vnc);
	m->normals_origin = ft_memalloc(sizeof(t_vec3) * m->vnc);
	m->faces = ft_memalloc(sizeof(int *) * m->face_count);
	m->props.object = 1;
	x = -1;
	while (++x < m->face_count)
		m->faces[x] = ft_memalloc(sizeof(int) * 4);
	ft_free_strsplit(line, split, ' ');
}

void	parse_face(int face[4], char *line, t_model *m)
{
	char	**split;

	split = ft_strsplit(line, ' ');
	if (ft_count_words(line, ' ') != 5)
		ft_error("Invalid model file");
	face[0] = ft_atoi(split[1]);
	face[1] = ft_atoi(split[2]);
	face[2] = ft_atoi(split[3]);
	face[3] = ft_atoi(split[4]);
	if (face[0] < 0 || face[1] < 0 || face[2] < 0 || face[3] < 0 ||
		face[0] >= m->face_count || face[1] >= m->face_count ||
		face[2] >= m->face_count || face[3] >= m->face_count)
		ft_error("Invalid model file");
	ft_free_strsplit(line, split, ' ');
}

void	read_model(t_model *m, char *filename)
{
	int		fd;
	int		result;
	char	*buff;
	int		counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	fd = open(filename, O_RDONLY);
	m->filename = ft_strdup(filename);
	while ((result = ft_get_next_line(fd, &buff)) > 0)
	{
		if (buff[0] == '#')
			continue;
		if (buff[0] == 'c')
			init_model(m, buff);
		else if (buff[1] == 'n')
			parse_float_trip(&m->normals_origin[counts[0]++], buff);
		else if (buff[0] == 'v')
			parse_float_trip(&m->vertices_origin[counts[1]++], buff);
		else if (buff[0] == 'f')
			parse_face(m->faces[counts[2]++], buff, m);
		free(buff);
	}
	free(buff);
}

void	trim_buff(char **buff)
{
	char		*tmp;

	tmp = buff[0];
	buff[0] = ft_strtrim(buff[0]);
	free(tmp);
	tmp = buff[1];
	buff[1] = ft_strtrim(buff[1]);
	free(tmp);
}

void	parse_model(t_data *d, t_list *list)
{
	t_model		*model;
	t_list		*ret;
	char		**buff;

	model = (t_model *)ft_memalloc(sizeof(t_model));
	parse_props(list, &model->props);
	while (list && !ft_strchr(list->content, '['))
	{
		if (ft_strchr(list->content, '='))
		{
			buff = ft_strsplit(list->content, '=');
			trim_buff(buff);
			if (ft_strequ(buff[0], "model"))
				read_model(model, buff[1]);
			else if (ft_strequ(buff[0], "scale"))
				model->scale = ft_atof(buff[1]);
			ft_free_strsplit(list->content, buff, '=');
		}
		list = list->next;
	}
	update_model(model);
	ret = ft_lstnew(model, sizeof(t_model));
	free(model);
	ret->content_size = MODEL;
	ft_lstadd(&d->s->objects, ret);
}

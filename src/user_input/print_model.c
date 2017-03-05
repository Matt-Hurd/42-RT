/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 03:06:42 by mhurd             #+#    #+#             */
/*   Updated: 2017/02/20 22:17:03 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_model_info(t_model *model)
{
	ft_putendl("[model]");
	ft_putstr("	File: ");
	ft_putendl(model->filename);
	ft_putstr("	Vertices: ");
	ft_putnbr(model->vc);
	ft_putendl("");
	ft_putstr("	Normals: ");
	ft_putnbr(model->vnc);
	ft_putendl("");
	ft_putstr("	Faces: ");
	ft_putnbr(model->face_count);
	ft_putendl("");
	ft_putstr("	Scale: ");
	ft_putnbr(model->scale * 100);
	ft_putendl("");
	print_properties(model->props);
}

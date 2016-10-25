/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:10:40 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 22:13:04 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

void	ft_mat_copy(float source[4][4], float dest[4][4])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			dest[i][j] = source[i][j];
	}
}

void	ft_mat_mult(float mat1[4][4], float mat2[4][4], float dest[4][4])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			dest[i][j] = mat1[i][0] * mat2[0][j] +
				mat1[i][1] * mat2[1][j] +
				mat1[i][2] * mat2[2][j] +
				mat1[i][3] * mat2[3][j];
	}
}

void	ft_vec_mult_mat(t_vec3 *s, float mat[4][4], t_vec3 *d)
{
	float x;
	float y;
	float z;

	x = s->x * mat[0][0] +
		s->y * mat[1][0] +
		s->z * mat[2][0] +
		mat[3][0];
	y = s->x * mat[0][1] +
		s->y * mat[1][1] +
		s->z * mat[2][1] +
		mat[3][1];
	z = s->x * mat[0][2] +
		s->y * mat[1][2] +
		s->z * mat[2][2] +
		mat[3][2];
	d->x = x;
	d->y = y;
	d->z = z;
}

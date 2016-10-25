/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 19:33:55 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/15 12:08:54 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

static void	bzero_matrix(float matrix[4][4])
{
	ft_bzero(matrix[0], sizeof(float) * 4);
	ft_bzero(matrix[1], sizeof(float) * 4);
	ft_bzero(matrix[2], sizeof(float) * 4);
	ft_bzero(matrix[3], sizeof(float) * 4);
}

void		ft_make_identity_matrix(float matrix[4][4])
{
	ft_bzero(matrix[0], sizeof(float) * 4);
	ft_bzero(matrix[1], sizeof(float) * 4);
	ft_bzero(matrix[2], sizeof(float) * 4);
	ft_bzero(matrix[3], sizeof(float) * 4);
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;
}

void		ft_tr_translate(float matrix[4][4], float tx, float ty, float tz)
{
	float tmat[4][4];

	bzero_matrix(tmat);
	tmat[0][0] = 1;
	tmat[1][1] = 1;
	tmat[2][2] = 1;
	tmat[3][3] = 1;
	tmat[3][0] = tx;
	tmat[3][1] = ty;
	tmat[3][2] = tz;
	ft_mat_mult(matrix, tmat, matrix);
}

void		ft_tr_scale(float matrix[4][4], float sx, float sy, float sz)
{
	float smat[4][4];

	bzero_matrix(smat);
	smat[0][0] = sx;
	smat[1][1] = sy;
	smat[2][2] = sz;
	smat[3][3] = 1;
	ft_mat_mult(matrix, smat, matrix);
}

void		ft_tr_rotate(float matrix[4][4], float ax, float ay, float az)
{
	float xmat[4][4];
	float ymat[4][4];
	float zmat[4][4];
	float mat1[4][4];
	float mat2[4][4];

	ft_make_identity_matrix(xmat);
	ft_make_identity_matrix(ymat);
	ft_make_identity_matrix(zmat);
	xmat[1][1] = cos(ax);
	xmat[1][2] = sin(ax);
	xmat[2][1] = -sin(ax);
	xmat[2][2] = cos(ax);
	ymat[0][0] = cos(ay);
	ymat[0][2] = -sin(ay);
	ymat[2][0] = sin(ay);
	ymat[2][2] = cos(ay);
	zmat[0][0] = cos(az);
	zmat[0][1] = sin(az);
	zmat[1][0] = -sin(az);
	zmat[1][1] = cos(az);
	ft_mat_mult(matrix, ymat, mat1);
	ft_mat_mult(mat1, xmat, mat2);
	ft_mat_mult(mat2, zmat, matrix);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 20:32:51 by mhurd             #+#    #+#             */
/*   Updated: 2016/11/16 22:35:10 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int g_perlin[512];
static int g_permutation[] = { 151, 160, 137, 91, 90, 15,
	131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8,
	99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62,
	94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174,
	20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77,
	146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
	46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76,
	132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164,
	100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38,
	147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182,
	189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221,
	153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79,
	113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193,
	238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
	49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45,
	127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141,
	128, 195, 78, 66, 215, 61, 156, 180
};

static double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

static double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = h < 8 || h == 12 || h == 13 ? x : y;
	v = h < 4 || h == 12 || h == 13 ? y : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double			calc_noise(t_vec3 tmp, t_vec3 coords, int vals[6])
{
	return
	(lerp(tmp.z, lerp(tmp.y, lerp(tmp.x,
		grad(g_perlin[vals[1]], coords.x, coords.y, coords.z),
		grad(g_perlin[vals[4]], coords.x - 1, coords.y, coords.z)),
			lerp(tmp.x,
			grad(g_perlin[vals[2]], coords.x, coords.y - 1, coords.z),
			grad(g_perlin[vals[5]], coords.x - 1, coords.y - 1, coords.z))),
		lerp(tmp.y, lerp(tmp.x,
			grad(g_perlin[vals[1] + 1], coords.x, coords.y, coords.z - 1),
			grad(g_perlin[vals[4] + 1], coords.x - 1, coords.y, coords.z - 1)),
		lerp(tmp.x,
			grad(g_perlin[vals[2] + 1], coords.x, coords.y - 1, coords.z - 1),
			grad(g_perlin[vals[5] + 1], coords.x - 1, coords.y - 1, coords.z - 1
)))));
}

double			noise(double x, double y, double z)
{
	t_vec3	pos;
	t_vec3	tmp;
	t_vec3	coords;
	int		vals[6];

	pos.x = (int)floor(x) & 255;
	pos.y = (int)floor(y) & 255;
	pos.z = (int)floor(z) & 255;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	coords.x = x;
	coords.y = y;
	coords.z = z;
	tmp.x = (x * x * x * (x * (x * 6 - 15) + 10));
	tmp.y = (y * y * y * (y * (y * 6 - 15) + 10));
	tmp.z = (z * z * z * (z * (z * 6 - 15) + 10));
	vals[0] = g_perlin[(int)pos.x] + (int)pos.y;
	vals[1] = g_perlin[vals[0]] + (int)pos.z;
	vals[2] = g_perlin[vals[0] + 1] + (int)pos.z;
	vals[3] = g_perlin[(int)pos.x + 1] + (int)pos.y;
	vals[4] = g_perlin[vals[3]] + (int)pos.z;
	vals[5] = g_perlin[vals[3] + 1] + (int)pos.z;
	return (calc_noise(tmp, coords, vals));
}

void			init_perlin(void)
{
	int i;

	i = -1;
	while (++i < 256)
	{
		g_perlin[i] = g_permutation[i];
		g_perlin[256 + i] = g_perlin[i];
	}
}

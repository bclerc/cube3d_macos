/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:47:39 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/16 15:04:17 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	pixel_put(t_cube *cube, int x, int y, int color)
{
	char	*dst;
	t_mlx	*mlx;

	mlx = cube->mlx;
	dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
	if (x < cube->r_x && x >= 0 && y < cube->r_y && y >= 0)
		*(unsigned int*)dst = color;
}

void	verline(t_cube *cube, int x, int y1, int y2)
{
	while (y1 < y2)
		pixel_put(cube, x, y1++, cube->cast->color);
}

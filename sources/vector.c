/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:47:39 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/12 16:18:27 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
	if (x < width && x >= 0 && y < heigth && y >= 0)
		*(unsigned int*)dst = color;
}

void	verline(t_mlx *mlx, int x, int y1, int y2, int color)
{
	while (y1 < y2)
		pixel_put(mlx, x, y1++, color);
}

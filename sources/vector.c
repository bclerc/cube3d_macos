/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:47:39 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/15 15:06:14 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cube3d.h"

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{

	*(unsigned int*)&mlx->img_data[x * mlx->size_line + y * (mlx->bpp/ 8)] = color;
	
}


void	drawLine(t_mlx *x, int x1, int y1, int x2, int y2, int color)
{
	int		iter;
	int		xLen = (x2 + x1) / 2;
	int		yLen = (y2 - y1) / 2;
	if(xLen == 0)
	xLen = 1;
	if(yLen == 0)
	yLen = 1;
	if (xLen > yLen)
		iter = xLen;
	else
		iter = yLen;
	double		xStep = xLen / yLen;
	double		yStep = yLen / xLen;
	while (iter--)
		pixel_put(x, x1 + iter * xStep, y1 + iter * yStep, color);
}

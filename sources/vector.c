/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:47:39 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/15 17:15:37 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cube3d.h"

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{

	*(unsigned int*)&mlx->img_data[x * mlx->size_line + y * (mlx->bpp/ 8)] = color;
	
}

void	drawSqr(t_mlx *mlx, int y, int x, int size, int color)
{	
	int *img;
	int i;
	int j;

	j = 0;
	while (j < 1080)
	{
		i = 0;
		while (i < 1080)
		{
			if (i >= x && j >=y && i < x + size && j < y + size)
				pixel_put(mlx, i, j, color);
			i++;
		}
		j++;
	}
}

void	clear(t_mlx *mlx, int color)
{	
	int *img;
	int i;
	int j;

	j = 0;
	while (j < 1080)
	{
		i = 0;
		while (i < 1080)
		{
				pixel_put(mlx, i, j, color);
			i++;
		}
		j++;
	}
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

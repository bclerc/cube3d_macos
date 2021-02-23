/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:47:39 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/23 14:43:46 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cube3d.h"

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	 dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
    *(unsigned int*)dst = color;

	//*(unsigned int*)&mlx->img_data[x * mlx->size_line + y * (mlx->bpp/ 8)] = color;
	
}

void	drawSqr(t_mlx *mlx, int y, int x, int size, int color)
{	
	int *img;
	int i;
	int j;

	j = 0;
	while (j < heigth)
	{
		i = 0;
		while (i < width)
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
	while (j < heigth)
	{
		i = 0;
		while (i < width)
		{
				pixel_put(mlx, i, j, color);
			i++;
		}
		j++;
	}
}

void	verLine(t_mlx *mlx, int x, int y1, int y2, int color)
{
	while (y1 < y2)
		pixel_put(mlx, x, y1++, color);
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
	{
		if (x2 >= 0 && y2 >=0 && x2 < 920 && y2 < 920)
		pixel_put(x, x1 + iter * xStep, y1 + iter * yStep, color);

	}
}

void drawMap(t_cube *cube)
{
		int x,y = 0;

	while (cube->map->coord[y])
	{
		x = 0;
		while (cube->map->coord[y][x])
		{
			if (cube->map->coord[y][x] - '0' == 1)
			{
				drawSqr(cube->mlx, x*30, y*30, 30, 0xFFFFFF);
			}
			x++;
		}
		y++;
	}
}

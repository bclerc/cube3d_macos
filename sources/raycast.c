/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:48:39 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/18 16:50:39 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cube3d.h"

void	display(t_cube *cube)
{
	t_mlx *mlx;
	double camerax;
	double raydirx;
	double raydiry;
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	double perpwalldist;
	double drawstart;
	double drawend;
	double lineheight;
	int side;
	int color;
	int stepx;
	int stepy;
	int hit;
	int		mapx;
	int		mapy;
	int i;

	mlx = cube->mlx;
	i = 0;
	while (i < width)
	{
		hit = 0;
		camerax = 2 * i / (double)width -1;
		raydirx = cube->dirx + cube->planex * camerax;
		raydiry = cube->diry + cube->planey * camerax;
		mapx = cube->player->x;
		mapy = cube->player->y;
		deltadistx = abs(1 / raydirx);
		deltadisty = abs(1 / raydiry);
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (cube->player->x - mapx) * deltadistx; 
		}
		else
		{
			stepx = 1;
			sidedistx = (cube->player->x + 1.0 - mapx) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedistx = (cube->player->y - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedistx = (cube->player->y + 1.0 - mapy) * deltadisty;
		}
		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
		if (cube->map->coord[mapx][mapy] - '0' == 1)
			hit = 1;
		}
		if (side == 0)
			perpwalldist = (mapx - cube->player->x + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist = (mapy - cube->player->y + ( 1 - stepy) / 2) / raydiry;		
		lineheight = (heigth / perpwalldist);
		drawstart = -lineheight / 2 + heigth / 2;
		if (drawstart < 0)
			drawstart = 0;
		drawend = lineheight / 2 + heigth / 2;
		if (drawend >= heigth)
			drawend = heigth -1;
		
		color = side == 1 ? 0xFF00FF : 0xFFFFFF;
		verLine(mlx, i, 0, drawstart, 0xFF0000);
		verLine(mlx, i, drawstart, drawend, color);
		verLine(mlx, i, drawend, heigth, 0x0000FF);
		i++;
	}
}	
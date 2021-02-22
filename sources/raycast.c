/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:45:49 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/22 22:47:17 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cube3d.h"

void	move_up(t_cube *cube)
{
	if (cube->map->coord[(int)cube->player->y][(int)(cube->player->x + cube->dirx * movespeed)] - '0' == 0)
		cube->player->x += cube->dirx * movespeed;
	if (cube->map->coord[(int)(cube->player->y + cube->diry * movespeed)][(int)cube->player->x] - '0' == 0)
		cube->player->y += cube->diry * movespeed;
}

void 	move_back(t_cube *cube)
{
	if (cube->map->coord[(int)cube->player->y][(int)(cube->player->x - cube->dirx * movespeed)] - '0' == 0)
		cube->player->x -= cube->dirx * movespeed;
	if (cube->map->coord[(int)(cube->player->y - cube->diry * movespeed)][(int)cube->player->x] - '0' == 0)
		cube->player->y -= cube->diry * movespeed;		
}
void	turn_left(t_cube *cube)
{
	double oldDirx = cube->dirx;
	cube->dirx= cube->dirx * cos(rotspeed) - cube->diry * sin(rotspeed);
	cube->diry = oldDirx * sin(rotspeed) + cube->diry * cos(rotspeed);	
	double oldplanex = cube->planex;
	cube->planex = cube->planex * cos(rotspeed) - cube->planey * sin(rotspeed);
	cube->planey = oldplanex * sin(rotspeed) + cube->planey * cos(rotspeed);
}

void	turn_right(t_cube *cube)
{
	double oldDirx = cube->dirx;
	cube->dirx= cube->dirx * cos(-rotspeed) - cube->diry * sin(-rotspeed);
	cube->diry = oldDirx * sin(-rotspeed) + cube->diry * cos(-rotspeed);	
	double oldplanex = cube->planex;
	cube->planex = cube->planex * cos(-rotspeed) - cube->planey * sin(-rotspeed);
	cube->planey = oldplanex * sin(-rotspeed) + cube->planey * cos(-rotspeed);
}
void	display(t_cube *cube)
{
	t_mlx *mlx;
	double camerax = 0; 
	double raydirx = 0 ;
	double raydiry = 0 ;
	double sidedistx = 0 ;
	double sidedisty = 0 ;
	double deltadistx = 0 ;
	double deltadisty = 0 ;
	double perpwalldist = 0 ;
	int drawstart = 0 ;
	int drawend = 0 ; 
	int lineheight = 0 ;
	double side;
	int color;
	int stepx;
	int stepy;
	int hit;
	int			mapx;
	int 		mapy;
	int x;


	mlx = cube->mlx;
	x = 0;
	while (x < width)
	{
		camerax = 2 * x / (double)width - 1;
		raydirx = cube->dirx + cube->planex * camerax;
		raydiry = cube->diry + cube->planey * camerax;

		mapx = (int)cube->player->x;
		mapy = (int)cube->player->y;

		deltadistx = fabs(1 / raydirx);
		deltadisty = fabs(1 / raydiry);

		hit = 0;
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (cube->player->x - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - cube->player->x) * deltadistx;
		}
		if (raydiry < 0)
			{
				stepy = -1;
				sidedisty = (cube->player->y - mapy) * deltadisty;
			}
			else
			{
			stepy = 1;
			sidedisty = (mapy + 1.0 - cube->player->y) * deltadisty;
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
		if (cube->map->coord[mapy][mapx] - '0' > 0)
			hit = 1;	
		}
		if (side == 0)
			perpwalldist = (mapx - cube->player->x + (1 - stepx) / 2) / raydirx;	
		else
			perpwalldist = (mapy - cube->player->y + (1 - stepy) / 2) / raydiry;
		lineheight = (int)(heigth / perpwalldist);
		 drawstart = -lineheight / 2  + heigth / 2;
		if (drawstart < 0)
			drawstart = 0;
		drawend = lineheight / 2 + heigth / 2;
		if (drawend >= heigth)
			drawend = heigth -1;
	
		verLine(mlx, x, 0, drawstart, 0xFFFF00);
		verLine(mlx, x, drawstart, drawend, side ? 0xFF00FF : 0xAAAAAA);
		verLine(mlx, x, drawend, heigth, 0);

		x++;		
	}
}	
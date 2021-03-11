/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:45:49 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/11 15:57:37 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cube3d.h"

void	move_up(t_cube *cube)
{
	if (cube->map->coord[(int)cube->player->y]
		[(int)(cube->player->x + cube->dirx * movespeed)] - '0' == 0)
		cube->player->x += cube->dirx * movespeed;
	if (cube->map->coord[(int)(cube->player->y + cube->diry * movespeed)]
		[(int)cube->player->x] - '0' == 0)
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

void	draw_pixel(int x, t_raycast *ray, t_cube *cube)
{
	for( int y = ray->drawstart; y < ray->drawend; y++)
	{
		ray->y = y;
		ray->texy = (int)ray->texPos & (64 - 1);
		ray->texPos += ray->step;
		ray->color = *(int*)&ray->texture->imgdat[(ray->texy * (ray->texture->size_line) + ray->texx * (ray->texture->bpp/8))];
		pixel_put(cube->mlx, x, y, ray->color);
	}

}

void	init_ray(int x, t_raycast *ray, t_cube *cube)
{
		ray->camerax = 2 * x / (double)width - 1;
		ray->raydirx = cube->dirx + cube->planex * ray->camerax;
		ray->raydiry = cube->diry + cube->planey * ray->camerax;

		ray->mapx = (int)cube->player->x;
		ray->mapy = (int)cube->player->y;

		ray->deltadistx = fabs(1 / ray->raydirx);
		ray->deltadisty = fabs(1 / ray->raydiry);
}

void	s_dda(t_raycast *ray, t_cube *cube)
{
		while (ray->hit == 0)
		{
			if (ray->sidedistx < ray->sidedisty)
			{
				ray->sidedistx += ray->deltadistx;
				ray->mapx += ray->stepx;
				ray->side = 0;
			}
			else
			{
				ray->sidedisty += ray->deltadisty;
				ray->mapy += ray->stepy;
				ray->side = 1;
			}
			if (cube->map->coord[ray->mapy][ray->mapx] - '0' > 0)
			ray->hit = 1;	
		}
}

void	s_ray(t_raycast *ray, t_cube *cube)
{
	ray->hit = 0;
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (cube->player->x - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - cube->player->x) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (cube->player->y - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - cube->player->y) * ray->deltadisty;
	}
}

t_texture *get_direction(t_cube* cube, t_raycast *ray)
{
		t_texture *tex;
		
		if (ray->side == 0) 
			ray->wallx = cube->player->y + ray->pwalldist * ray->raydiry;
		else
			ray->wallx = cube->player->x + ray->pwalldist * ray->raydirx;
		ray->wallx -=floor((ray->wallx));
		ray->texx = (int)(ray->wallx * (double)64);
		if (ray->side == 0 && ray->raydirx > 0 )
			ray->texx = 64 - ray->texx - 1;
		if (ray->side == 1 && ray->raydiry < 0 )
			ray->texx = 64 - ray->texx -1; 
		if (ray->side == 0 && ray->raydirx > 0)
			tex = cube->texture[0];
		if (ray->side == 0 && ray->raydirx <= 0) 
			tex = cube->texture[1];
		if (ray->side == 1 && ray->raydiry < 0 )
			tex = cube->texture[2];
		if (ray->side == 1 && ray->raydiry >= 0)
			tex = cube->texture[3];
	return (tex);
}

void	display(t_cube *cube)
{
	t_mlx		*mlx;
	t_raycast	ray;

	int			x;

	mlx = cube->mlx;
	x = 0;
	while (x < width)
	{
		init_ray(x, &ray, cube);
		s_ray(&ray, cube);
		s_dda(&ray, cube);
		if (ray.side == 0)
			ray.pwalldist = (ray.mapx - cube->player->x + (1 - ray.stepx) / 2) / ray.raydirx;	
		else
			ray.pwalldist = (ray.mapy - cube->player->y + (1 - ray.stepy) / 2) / ray.raydiry;
		ray.lineheight = (int)(heigth / ray.pwalldist);
		 ray.drawstart = -ray.lineheight / 2  + heigth / 2;
		if (ray.drawstart < 0)
			ray.drawstart = 0;
		ray.drawend = ray.lineheight / 2 + heigth / 2;
		if (ray.drawend >= heigth)
			ray.drawend = heigth -1;
		ray.texture = get_direction(cube, &ray);
		ray.step = 1.0 * 64 / ray.lineheight;
		ray.texPos = (ray.drawstart - heigth/ 2 + ray.lineheight / 2) * ray.step;
		draw_pixel(x, &ray, cube);
		verLine(mlx, x, 0, ray.drawstart, *(int*)&cube->R_COLOR);
		verLine(mlx, x, ray.drawend, heigth, *(int*)&cube->G_COLOR);
		cube->x = x;
		cube->cast = &ray;
			drawSprite((void*)cube);
			x+=2;
	}
	
}	
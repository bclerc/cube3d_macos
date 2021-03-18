/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:45:49 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/17 14:47:52 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		s_dda(t_raycast *ray, t_cube *cube)
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

void		s_ray(t_raycast *ray, t_cube *cube)
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

t_texture	*get_direction(t_cube *cube, t_raycast *ray)
{
	t_texture *tex;

	if (ray->side == 0)
		ray->wallx = cube->player->y + ray->pwalldist * ray->raydiry;
	else
		ray->wallx = cube->player->x + ray->pwalldist * ray->raydirx;
	ray->wallx -= floor((ray->wallx));
	ray->texx = (int)(ray->wallx * (double)64);
	if (ray->side == 0 && ray->raydirx > 0)
		ray->texx = 64 - ray->texx - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		ray->texx = 64 - ray->texx - 1;
	if (ray->side == 0 && ray->raydirx > 0)
		tex = cube->texture[0];
	if (ray->side == 0 && ray->raydirx <= 0)
		tex = cube->texture[1];
	if (ray->side == 1 && ray->raydiry < 0)
		tex = cube->texture[2];
	if (ray->side == 1 && ray->raydiry >= 0)
		tex = cube->texture[3];
	return (tex);
}

void		display(t_cube *cube)
{
	t_raycast	ray;
	t_mlx		*mlx;
	int			x;

	mlx = cube->mlx;
	x = 0;
	while (x < cube->r_x)
	{
		init_ray(x, &ray, cube);
		s_ray(&ray, cube);
		s_dda(&ray, cube);
		calc_draw(cube, &ray);
		draw_pixel(x, &ray, cube);
		cube->cast = &ray;
		ray.color = *(int*)&cube->R_COLOR;
		verline(cube, x, 0, ray.drawstart);
		ray.color = *(int*)&cube->G_COLOR;
		verline(cube, x, ray.drawend, cube->r_y);
		cube->x = x;
		drawsprite(cube, &ray);
		x += 2;
	}
}

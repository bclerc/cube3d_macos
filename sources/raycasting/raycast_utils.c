/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:48:30 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/18 15:05:09 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	calc_draw(t_cube *cube, t_raycast *ray)
{
	if (ray->side == 0)
		ray->pwalldist = (ray->mapx - cube->player->x
			+ (1 - ray->stepx) / 2) / ray->raydirx;
	else
		ray->pwalldist = (ray->mapy - cube->player->y
			+ (1 - ray->stepy) / 2) / ray->raydiry;
	ray->lineheight = (int)(cube->r_y / ray->pwalldist);
	ray->drawstart = -ray->lineheight / 2 + cube->r_y / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + cube->r_y / 2;
	if (ray->drawend >= cube->r_y)
		ray->drawend = cube->r_y - 1;
	ray->texture = get_direction(cube, ray);
	ray->step = 1.0 * 64 / ray->lineheight;
	ray->texpos = (ray->drawstart - cube->r_y / 2 + ray->lineheight / 2)
		* ray->step;
}

void	draw_pixel(int x, t_raycast *ray, t_cube *cube)
{
	int y;

	y = ray->drawstart;
	while (y < ray->drawend)
	{
		ray->y = y;
		ray->texy = (int)ray->texpos & (64 - 1);
		ray->texpos += ray->step;
		ray->color = *(int*)&ray->texture->imgdat[(ray->texy
		* (ray->texture->size_line)
		+ ray->texx * (ray->texture->bpp / 8))];
		pixel_put(cube, x, y, ray->color);
		y++;
	}
}

void	init_ray(int x, t_raycast *ray, t_cube *cube)
{
	ray->camerax = 2 * x / (double)cube->r_x - 1;
	ray->raydirx = cube->dirx + cube->planex * ray->camerax;
	ray->raydiry = cube->diry + cube->planey * ray->camerax;
	ray->mapx = (int)cube->player->x;
	ray->mapy = (int)cube->player->y;
	ray->deltadisty = fabs(1 / ray->raydiry);
	ray->deltadistx = fabs(1 / ray->raydirx);
}

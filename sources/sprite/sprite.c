/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:50:41 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/16 14:00:03 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	calc_sprite(t_cube *cube, t_sprite_s *s, int i)
{
	s->spritex = cube->sprite[s->sorder[i]].x - cube->player->x;
	s->spritey = cube->sprite[s->sorder[i]].y - cube->player->y;
	s->invdet = 1.0 / (cube->planex * cube->diry - cube->dirx * cube->planey);
	s->transformx = s->invdet *
		(cube->diry * s->spritex - cube->dirx * s->spritey);
	s->transformy = s->invdet *
		(-cube->planey * s->spritex + cube->planex * s->spritey);
	s->screenx = (int)((cube->r_x / 2) * (1 + s->transformx / s->transformy));
	s->vmscreen = (int)(0.0 / s->transformy);
	s->sheight = abs((int)(cube->r_y / (s->transformy))) / 1;
	s->drawstarty = -s->sheight / 2 + cube->r_y / 2 + s->vmscreen;
	if (s->drawstarty < 0)
		s->drawstarty = 0;
	s->drawendy = s->sheight / 2 + cube->r_y / 2 + s->vmscreen;
	if (s->drawendy >= cube->r_y)
		s->drawendy = cube->r_y - 1;
	s->swidth = abs((int)(cube->r_y / (s->transformy))) / 1;
	s->drawstartx = -s->swidth / 2 + s->screenx;
	if (s->drawstartx < 0)
		s->drawstartx = 0;
	s->drawendx = s->swidth / 2 + s->screenx;
	if (s->drawendx >= cube->r_x)
		s->drawendx = cube->r_x - 1;
}

void	print_sprite(t_cube *cube, t_sprite_s *s, t_raycast *ray, int x)
{
	int y;
	int d;

	s->texx = (int)(256 * (x - (-s->swidth / 2 + s->screenx))
	* 64 / s->swidth) / 256;
	if (s->transformy > 0 && x >= 0 && x < cube->r_x
		&& s->transformy < ray->pwalldist)
	{
		y = s->drawstarty;
		while (y < s->drawendy)
		{
			d = (y - s->vmscreen) * 256 - cube->r_y * 128 + s->sheight * 128;
			s->texy = ((d * 64) / s->sheight) / 256;
			ray->color = *(int*)&cube->texture[4]
			->imgdat[(s->texy * (cube->texture[4]->size_line)
			+ s->texx * (cube->texture[4]->bpp / 8))];
			if (ray->color != 0)
				pixel_put(cube, x, y, ray->color);
			y++;
		}
	}
}

void	init_sprite(t_cube *cube, t_sprite_s *s)
{
	int	i;

	sortsprite(cube, cube->player->x, cube->player->y);
	i = 0;
	while (i < cube->n_sprite)
	{
		s->sorder[i] = i;
		s->sdist[i] = ((cube->player->x - cube->sprite[i].x)
		* (cube->player->x - cube->sprite[i].x)
		+ (cube->player->y - cube->sprite[i].y)
		* (cube->player->y - cube->sprite[i].y));
		i++;
	}
}

void	drawsprite(t_cube *cube, t_raycast *ray)
{
	int			i;
	int			y;
	int			x;
	t_sprite	*sprite;
	t_sprite_s	s;

	x = cube->x;
	if (!(s.sorder = (int*)malloc(cube->n_sprite * sizeof(int))))
		exit(1);
	if (!(s.sdist = (double*)malloc(cube->n_sprite * sizeof(double) + 1)))
		exit(1);
	ray = cube->cast;
	sprite = cube->sprite;
	init_sprite(cube, &s);
	i = cube->n_sprite;
	while (--i >= 0)
	{
		calc_sprite(cube, &s, i);
		if (x >= s.drawstartx && x < s.drawendx)
			print_sprite(cube, &s, ray, x);
	}
	free(s.sorder);
	free(s.sdist);
}

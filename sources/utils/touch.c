/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:50:28 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/12 16:34:44 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	move_up(t_cube *cube)
{
	if (cube->map->coord[(int)cube->player->y]
		[(int)(cube->player->x + cube->dirx * movespeed)] - '0' == 0)
		cube->player->x += cube->dirx * movespeed;
	if (cube->map->coord[(int)(cube->player->y + cube->diry * movespeed)]
		[(int)cube->player->x] - '0' == 0)
		cube->player->y += cube->diry * movespeed;
}

void	move_back(t_cube *cube)
{
	if (cube->map->coord[(int)cube->player->y]
		[(int)(cube->player->x - cube->dirx * movespeed)] - '0' == 0)
		cube->player->x -= cube->dirx * movespeed;
	if (cube->map->coord[(int)(cube->player->y - cube->diry * movespeed)]
		[(int)cube->player->x] - '0' == 0)
		cube->player->y -= cube->diry * movespeed;
}

void	turn_left(t_cube *cube)
{
	double olddirx;
	double oldplanex;

	olddirx = cube->dirx;
	cube->dirx = cube->dirx * cos(rotspeed) - cube->diry * sin(rotspeed);
	cube->diry = olddirx * sin(rotspeed) + cube->diry * cos(rotspeed);
	oldplanex = cube->planex;
	cube->planex = cube->planex * cos(rotspeed)
		- cube->planey * sin(rotspeed);
	cube->planey = oldplanex * sin(rotspeed) + cube->planey * cos(rotspeed);
}

void	turn_right(t_cube *cube)
{
	double olddirx;
	double oldplanex;

	olddirx = cube->dirx;
	cube->dirx = cube->dirx * cos(-rotspeed) - cube->diry * sin(-rotspeed);
	cube->diry = olddirx * sin(-rotspeed) + cube->diry * cos(-rotspeed);
	oldplanex = cube->planex;
	cube->planex = cube->planex * cos(-rotspeed)
		- cube->planey * sin(-rotspeed);
	cube->planey = oldplanex * sin(-rotspeed) + cube->planey * cos(-rotspeed);
}

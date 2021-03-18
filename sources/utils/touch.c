/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:50:28 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/18 15:04:17 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	move_up(t_cube *cube)
{
	if (cube->map->coord[(int)cube->player->y]
		[(int)(cube->player->x + cube->dirx * MOVESPEED)] - '0' == 0)
		cube->player->x += cube->dirx * MOVESPEED;
	if (cube->map->coord[(int)(cube->player->y + cube->diry * MOVESPEED)]
		[(int)cube->player->x] - '0' == 0)
		cube->player->y += cube->diry * MOVESPEED;
}

void	move_back(t_cube *cube)
{
	if (cube->map->coord[(int)cube->player->y]
		[(int)(cube->player->x - cube->dirx * MOVESPEED)] - '0' == 0)
		cube->player->x -= cube->dirx * MOVESPEED;
	if (cube->map->coord[(int)(cube->player->y - cube->diry * MOVESPEED)]
		[(int)cube->player->x] - '0' == 0)
		cube->player->y -= cube->diry * MOVESPEED;
}

void	turn_left(t_cube *cube)
{
	double olddirx;
	double oldplanex;

	olddirx = cube->dirx;
	cube->dirx = cube->dirx * cos(ROTSPEED) - cube->diry * sin(ROTSPEED);
	cube->diry = olddirx * sin(ROTSPEED) + cube->diry * cos(ROTSPEED);
	oldplanex = cube->planex;
	cube->planex = cube->planex * cos(ROTSPEED)
		- cube->planey * sin(ROTSPEED);
	cube->planey = oldplanex * sin(ROTSPEED) + cube->planey * cos(ROTSPEED);
}

void	turn_right(t_cube *cube)
{
	double olddirx;
	double oldplanex;

	olddirx = cube->dirx;
	cube->dirx = cube->dirx * cos(-ROTSPEED) - cube->diry * sin(-ROTSPEED);
	cube->diry = olddirx * sin(-ROTSPEED) + cube->diry * cos(-ROTSPEED);
	oldplanex = cube->planex;
	cube->planex = cube->planex * cos(-ROTSPEED)
		- cube->planey * sin(-ROTSPEED);
	cube->planey = oldplanex * sin(-ROTSPEED) + cube->planey * cos(-ROTSPEED);
}

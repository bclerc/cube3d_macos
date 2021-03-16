/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:41:46 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/16 14:59:56 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	set_direction(t_cube *cube, double dirx, double planex, double planey)
{
	cube->dirx = dirx;
	cube->planex = planex;
	cube->planey = planey;
}

void	set_pos(t_cube *cube, char direction)
{
	if (direction == 'W')
	{
		cube->diry = 0.0;
		set_direction(cube, 1.0, 0.00, -0.66);
	}
	if (direction == 'E')
	{
		cube->diry = 0.00;
		set_direction(cube, -1.0, 0.00, 0.66);
	}
	if (direction == 'S')
	{
		cube->diry = 1.0;
		set_direction(cube, 0.0, 0.66, 0.00);
	}
	if (direction == 'N')
	{
		cube->diry = -1.0;
		set_direction(cube, 0.0, -0.60, 0.00);
	}
}

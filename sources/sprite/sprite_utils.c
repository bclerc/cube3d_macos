/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:28:48 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/16 13:42:51 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int		calc_dist(t_cube *cube, int sx, int sy)
{
	int dist;

	dist = pow((sx - (int)cube->player->x), 2)
		+ pow((sy - (int)cube->player->y), 2);
	return (sqrt(dist));
}

void	sortsprite(t_cube *cube, int sx, int sy)
{
	t_sprite	*sprite;
	t_sprite	*sprite2;
	t_sprite	tmp;
	int			i;
	int			n;

	sprite = cube->sprite;
	n = cube->n_sprite;
	i = 0;
	while (i < n - 1)
	{
		sprite = &cube->sprite[i];
		sprite2 = &cube->sprite[i + 1];
		if (calc_dist(cube, (int)sprite->x, (int)sprite->y) >
			calc_dist(cube, (int)sprite2->x, (int)sprite2->y))
		{
			tmp = cube->sprite[i];
			cube->sprite[i] = cube->sprite[i + 1];
			cube->sprite[i + 1] = tmp;
			i = 1;
		}
		i++;
	}
}

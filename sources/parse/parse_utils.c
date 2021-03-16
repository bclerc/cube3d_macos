/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:04:08 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/16 15:00:06 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int			is_player_loc(char c)
{
	if (c == 'E' || c == 'S' || c == 'W' || c == 'N')
		return (1);
	return (0);
}

int			check_set(t_map *map, char *set, int x, int y)
{
	int i;
	int same;

	i = 0;
	same = 0;
	while (set[i])
	{
		if (set[i] == map->coord[y][x])
			same = 1;
		i++;
	}
	return (same);
}

void		check_zero(t_map *map, int x, int y, char *set)
{
	char	**coord;
	int		i;

	i = 0;
	coord = map->coord;
	if (x == 0 || y == 0 || y + 1 == map->max_y)
		map_error(map, x, y);
	if (!coord[y][x + 1] || !coord[y + 1][x])
		map_error(map, x, y);
	if (coord[y][x - 1] != '1' && !check_set(map, set, x - 1, y))
		map_error(map, x - 1, y);
	if (coord[y][x + 1] != '1' && !check_set(map, set, x + 1, y))
		map_error(map, x + 1, y);
	if (coord[y + 1][x] != '1' && !check_set(map, set, x, y + 1))
		map_error(map, x, y + 1);
	if (coord[y - 1][x] != '1' && !check_set(map, set, x, y - 1))
		map_error(map, x, y - 1);
}

void		set_player(t_cube *cube, int x, int y, char direction)
{
	if (cube->player->check != 1)
	{
		cube->player->x = (double)x + 0.5;
		cube->player->y = (double)y + 0.5;
		cube->player->check = 1;
		set_pos(cube, direction);
	}
	else
		map_error_m(cube->map, x, y, "Duplicate player position");
}

int			check_map(t_cube *cube)
{
	int		y;
	int		x;

	y = -1;
	while (cube->map->coord[++y])
	{
		x = -1;
		while (cube->map->coord[y][++x])
		{
			if (cube->map->coord[y][x] != '1' && cube->map->coord[y][x] != ' '
				&& cube->map->coord[y][x] != '\t')
				check_zero(cube->map, x, y, "NSWE20");
			if (is_player_loc(cube->map->coord[y][x]))
			{
				set_player(cube, x, y, cube->map->coord[y][x]);
				cube->map->coord[y][x] = '0';
			}
			if (cube->map->coord[y][x] == '2')
				cube->n_sprite++;
		}
	}
	if (cube->player->check != 1)
		error_m("Player position not set");
	return (1);
}

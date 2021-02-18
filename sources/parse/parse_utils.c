/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:04:08 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/17 16:06:22 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cube3d.h"

void check_zero(t_map *map, int x, int y)
{
	char **coord;

	coord = map->coord;
	if (x == 0 || y == 0 || y + 1 == *map->max_y)
		map_error(map, x, y);
	if (!coord[y][x + 1] || !coord[y + 1][x])
		map_error(map, x, y);
	if (coord[y][x - 1] != '1' && coord[y][x - 1] != '0')
        map_error(map, x - 1, y);  
    if (coord[y][x + 1] != '1' && coord[y][x + 1] != '0')
    	map_error(map, x + 1, y);
    if (coord[y + 1][x] != '1' && coord[y + 1][x] != '0')
    	map_error(map, x, y + 1);  
    if (coord[y - 1][x] != '1' && coord[y - 1][x] != '0')
    	map_error(map, x, y - 1); 
}


int	check_map(t_cube *cube)
{
	int y;
	int x;
	char **coord;
		
	coord = cube->map->coord;
	y = 0;
	while (coord[y])
	{
		x = 0;
		while (coord[y][x])
		{
			if (coord[y][x] != '1' && coord[y][x] != ' ' && coord[y][x] != '\t')
				check_zero(cube->map, x, y);
			x++;
		}
		y++;	
	}
	return (1);
}
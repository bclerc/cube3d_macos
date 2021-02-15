/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:23:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/15 11:34:49 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cube3d.h"

void print_map(t_map *map, int x, int y)
{
	int w;

	w = 0;
	while (map->coord[y][w])
	{
		if (x == w)
			printf("\033[0;31m%c\033[0m", map->coord[y][w]);
		else
			printf("%c", map->coord[y][w]);
		w++;
	}
	printf("\n");
}

void map_error(t_map *map, int x, int y)
{
	printf("Error\n");
	printf("---------------- Error surround line ");
	printf("\033[0;31m%d\033[0m column \033[0;31m%d\033[0m ----------------\n", y + 1, x + 1);
	print_map(map, x, y);
	exit(-1);
}
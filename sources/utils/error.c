/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:23:55 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/16 15:05:42 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	print_map(t_map *map, int x, int y)
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

void	error_m(char *msg)
{
	printf("\nError\n");
	printf("\033[0;31m%s\033[0m\n", msg);
	exit(-1);
}

void	tex_error(char *path, char *texture)
{
	printf("\nError\n");
	printf("---------------- Texture \033[0;31m%s"
		"\033[0m not found ----------------\n", texture);
	printf("\033[0;31m%s\033[0m\n", path);
	exit(-1);
}

void	map_error(t_map *map, int x, int y)
{
	printf("\nError\n");
	printf("---------------- Error surround line ");
	printf("\033[0;31m%d\033[0m column \033[0;31m%d"
			"\033[0m ----------------\n", y + 1, x + 1);
	print_map(map, x, y);
	exit(-1);
}

void	map_error_m(t_map *map, int x, int y, char *msg)
{
	printf("\nError\n");
	printf("---------------- %s ", msg);
	printf("\033[0;31m%d\033[0m column \033[0;31m%d"
		"\033[0m ----------------\n", y + 1, x + 1);
	print_map(map, x, y);
	exit(-1);
}

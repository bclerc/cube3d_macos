/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:38:52 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/11 15:01:33 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cube3d.h"

void clean_param(t_cube *cube)
{
	cube->R_X = 0;
	cube->R_Y = 0;	
}

void kill_m(t_map *map)
{
	int i;

	i = 0;
	while (map->coord[i])
	{
		free(map->coord[i]);
		i++;
	}
	free(map->coord);
}

void kill_c(t_cube *cube)
{
	free(cube->WE);
	free(cube->NO);
	free(cube->SO);
	free(cube->EA);
	free(cube->SPRITE);
}

int main(int argc, char **argv)
{
	int fd;
	t_cube cube;
	t_map map;
	
	cube.map = &map;
	cube.file_name = argv[1];
	clean_param(&cube);
	cube.fd = open(argv[1], O_RDONLY);
	cube.fd_map = open(argv[1], O_RDONLY);
	cube.fd_map2 = open(argv[1], O_RDONLY);
	if (argc != 2)
		return 0;
	if (fd < 0)
	{
		printf("Erreur: FD %s incorrect", argv[1]);
		return (0);
	}
	init_cube(&cube);
	first_read(&cube);
	parse_map(&cube);
	printf("X: %d, Y: %d\nNO: %s\nSO %s\nWE %s\nEA %s\nS %s", cube.R_X, cube.R_Y, cube.NO, cube.SO, cube.WE, cube.EA, cube.SPRITE);
	printf("\nF %d, %d, %d\nC %d, %d, %d\n", cube.G_COLOR.r, cube.G_COLOR.g, cube.G_COLOR.b, cube.R_COLOR.r, cube.R_COLOR.g, cube.R_COLOR.b);
	printf("\n Max x: %d, Max y: %d\n", cube.map->max_x, cube.map->max_y);
	
	int q = 0;
	while (cube.map->coord[q])
	{
		printf(">>> %s\n",  cube.map->coord[q]);
		q++;
	}
	check_map(&cube);
	kill_c(&cube);
	kill_m(&map);
}
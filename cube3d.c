/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:38:52 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/18 19:48:54 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

void
	kill_m(t_map *map)
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

void
	kill_c(t_cube *cube)
{
	free(cube->we);
	free(cube->no);
	free(cube->so);
	free(cube->ea);
	free(cube->sprite);
}

void
	check_argv(t_cube *cube, char *arg)
{
	if (ft_strcmp(arg, "--save") == 0)
	{
		display(cube);
		to_bmp(cube);
	}
	else
		error_m("Bad arguments");
	exit(1);
}

void
	load_fd(t_cube *cube, char *argv)
{
	if (ft_strcmp(&argv[ft_strlen(argv) - 4], ".cub") != 0)
		error_m("Not supported file");
	cube->fd = open(argv, O_RDONLY);
	cube->fd_map = open(argv, O_RDONLY);
	cube->fd_map2 = open(argv, O_RDONLY);
	if (cube->fd < 1 || cube->fd_map < 1 || cube->fd_map2 < 1)
		error_m("File not found");
}

int
	main(int argc, char **argv)
{
	int			fd;
	t_cube		*cube;
	t_texture	*texture;

	texture = (t_texture*)malloc(sizeof(t_texture));
	cube = init_cube_s();
	cube->file_name = argv[1];
	if (argc > 3 || argc < 2)
		error_m(argc > 3 ? "To many arguments"
			: "Not enough arguments");
	load_fd(cube, argv[1]);
	init_cube(cube);
	first_read(cube);
	parse_map(cube);
	check_map(cube);
	if (cube->n_sprite > 0)
		register_sprite(cube);
	cube->mlx = init_mlx(cube);
	load_texture(cube);
	if (argc == 3)
		check_argv(cube, argv[2]);
	init_hook(cube);
	kill_m(cube->map);
	kill_c(cube);
}

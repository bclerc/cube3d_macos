/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:19:44 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/24 14:00:30 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cube3d.h"

t_mlx *init_mlx()
{
	int bpp;
	int size_line;
	int endian;
	t_mlx *mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (0);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, width, heigth, "Cube3d");
	mlx->img_ptr = mlx_new_image(mlx->mlx, width, heigth);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &bpp, &size_line, &endian);
	mlx->endian = endian;
	mlx->size_line = size_line;
	mlx->bpp = bpp;
	return (mlx);
}

t_player *init_player()
{
	t_player *player;

	if (!(player = (t_player*)malloc(sizeof(t_player))))
		return (0);
	player->x = 5;
	player->y = 5;
	return (player);	
}

t_map *init_map()
{
	t_map *map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (0);
	map->coord = 0;
	map->max_x = 0;
	map->max_y = 0;
	map->parsed = 0;

	return (map);
}

t_cube *init_cube_s()
{
	t_cube *cube;

	if (!(cube = (t_cube*)malloc(sizeof(t_cube))))
		return (0);
	cube->diry = 0.0;
	cube->dirx = -1.0;
	cube->planex = 0;
	cube->planey = 0.66;
	cube->player = init_player();
	cube->map = init_map();
	cube->texture = init_texture();
	return (cube);
}

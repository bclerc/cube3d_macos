/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:19:44 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/15 10:23:27 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_mlx		*init_mlx(t_cube *cube)
{
	t_mlx	*mlx;
	int		bpp;
	int		size_line;
	int		endian;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (0);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, cube->r_x,  cube->r_y, "Cube3d");
	mlx->img_ptr = mlx_new_image(mlx->mlx, cube->r_x, cube->r_y);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &bpp, &size_line, &endian);
	mlx->endian = endian;
	mlx->size_line = size_line;
	mlx->bpp = bpp;
	return (mlx);
}

t_player	*init_player(void)
{
	t_player *player;

	if (!(player = (t_player*)malloc(sizeof(t_player))))
		return (0);
	player->x = 5;
	player->y = 5;
	return (player);
}

t_map		*init_map(void)
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

t_cube		*init_cube_s(void)
{
	t_cube *cube;

	if (!(cube = (t_cube*)malloc(sizeof(t_cube))))
		return (0);
	cube->diry = 0;
	cube->dirx = 0;
	cube->planex = 0;
	cube->planey = 0;
	cube->player = init_player();
	cube->map = init_map();
	cube->texture = init_texture();
	cube->r_x = 0;
	cube->r_y = 0;
	cube->n_sprite = 0;
	return (cube);
}

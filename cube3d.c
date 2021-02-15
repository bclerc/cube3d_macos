/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:38:52 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/15 17:16:15 by bclerc           ###   ########.fr       */
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

int	deal_key(int key, t_cube *cube)
{
	printf("key %d\n", key);
	if (key == 123)
		cube->player->x-=10;
	if (key == 125)
		cube->player->y+=10;
	if (key == 126)
		cube->player->y-=10;
	if (key == 124)
		cube->player->x+=10;
	
	clear(cube->mlx, 0x000000);
	drawSqr(cube->mlx, cube->player->x, cube->player->y, 10, 0xAA45FF);
	mlx_put_image_to_window(cube->mlx->mlx, cube->mlx->win, cube->mlx->img_ptr, 0,0);
	return (1);
}

int main(int argc, char **argv)
{
	int fd;
	t_cube cube;
	t_map map;
	t_mlx mlx;
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
	check_map(&cube);
	printf("X: %d, Y: %d\nNO: %s\nSO %s\nWE %s\nEA %s\nS %s", cube.R_X, cube.R_Y, cube.NO, cube.SO, cube.WE, cube.EA, cube.SPRITE);
	printf("\nF %d, %d, %d\nC %d, %d, %d\n", cube.G_COLOR.r, cube.G_COLOR.g, cube.G_COLOR.b, cube.R_COLOR.r, cube.R_COLOR.g, cube.R_COLOR.b);
	printf("\n Max x: %d, Max y: %d\n", cube.map->max_x, cube.map->max_y);
	
	int q = 0;
	while (cube.map->coord[q])
	{
		printf(">>> %s\n",  cube.map->coord[q]);
		q++;
	}
	int bpp;
	int size_line;
	int endian;
	mlx.mlx = mlx_init(); 
	mlx.win = mlx_new_window(mlx.mlx,1920,1080, "Cube3d");
	mlx.img_ptr = mlx_new_image(mlx.mlx, 1920, 1080); // 800 = width ; 600 = height
	mlx.img_data =  mlx_get_data_addr(mlx.img_ptr, &bpp, &size_line, &endian);
	mlx.bpp = bpp;
	mlx.size_line = size_line;
	mlx.endian = endian;
	float px, py;
	//Draw player
	cube.mlx = &mlx;

	int x,y = 0;

	while (cube.map->coord[y])
	{
		x = 0;
		while (cube.map->coord[y][x])
		{
			if (cube.map->coord[y][x] - '0' == 1)
			{
				drawSqr(cube.mlx, x*150, y*150, 150, 0xFFFFFF);
				printf("x, y");
			}
			x++;
		}
		y++;
	}














	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img_ptr, 0, 0);
	cube.player->x = 500;
	cube.player->y = 500;
	mlx_key_hook(mlx.win, deal_key, &cube);
	mlx_loop(mlx.mlx);













	check_map(&cube);
	kill_c(&cube);
	kill_m(&map);
}
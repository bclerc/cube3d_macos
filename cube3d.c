/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:38:52 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/11 14:38:11 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cube3d.h"

int key_press(int key, t_cube *cube)
{
	if (key == 12)
	{
		clear(cube->mlx, 0x0F0F0F);
		drawMap(cube);
	}
	if (key == k_down)
		cube->mlx->down = 1;
	if (key == k_up)
		cube->mlx->up = 1;
	if (key == k_left)
		cube->mlx->left = 1;
	if (key == k_right)
		cube->mlx->right = 1;
	return (1);
}

int key_relache(int key, t_cube *cube)
{
	if (key == k_down)
		cube->mlx->down = 0;
	if (key == k_up)
		cube->mlx->up = 0;
	if (key == k_left)
		cube->mlx->left = 0;
	if (key == k_right)
		cube->mlx->right = 0;
	return (1);
}


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

int	deal_key(t_cube *cube)
{	
	//printf("Player x, y : %f %f, max x, y : %d %d \n",cube->player->x, cube->player->y, *cube->map->max_y, *cube->map->max_x);
	if (cube->mlx->up == 1)
		move_up(cube);
	if (cube->mlx->down == 1)
		move_back(cube);
	if (cube->mlx->left == 1)
		turn_left(cube);
	if (cube->mlx->right == 1)
		turn_right(cube);
	display(cube);
	mlx_put_image_to_window(cube->mlx->mlx, cube->mlx->win, cube->mlx->img_ptr, 0, 0);
	mlx_string_put(cube->mlx->mlx, cube->mlx->win, 0, 5, 0xFF00FF, "X: ");
	mlx_string_put(cube->mlx->mlx, cube->mlx->win, 20, 5, 0xFF00FF, ft_itoa((int)cube->player->x));
	mlx_string_put(cube->mlx->mlx, cube->mlx->win, 0, 25, 0xFF00FF, "Y: ");	
	mlx_string_put(cube->mlx->mlx, cube->mlx->win, 20, 25, 0xFF00FF, ft_itoa((int)cube->player->y));
	printf("%c | %.3f %.3f < direction > %.3f %.3f \n", cube->map->coord[(int)cube->player->y][(int)cube->player->x] ,cube->dirx, cube->diry, cube->planex, cube->planey);
	return (1);
}

int main(int argc, char **argv)
{
	int fd;
	t_cube *cube;
	t_texture *texture;

	texture = (t_texture*)malloc(sizeof(t_texture));
	cube = init_cube_s();
	printf("%f %f >>>", cube->player->y, cube->player->x);
	cube->file_name = argv[1];
	cube->fd = open(argv[1], O_RDONLY);
	cube->fd_map = open(argv[1], O_RDONLY);
	cube->fd_map2 = open(argv[1], O_RDONLY);
	if (argc != 2)
		return 0;
	if (fd < 0)
	{
		printf("Erreur: FD %s incorrect", argv[1]);
		return (0);
	}
	init_cube(cube);
	first_read(cube);
	parse_map(cube);
	check_map(cube);
	if (cube->n_sprite > 0)
	{
		register_sprite(cube);
		printf("Sprite position %d %d \n", cube->sprite[0].x, cube->sprite[0].y);
	}
	printf("X: %d, Y: %d\nNO: %s\nSO %s\nWE %s\nEA %s\nS %s", cube->R_X, cube->R_Y, cube->NO, cube->SO, cube->WE, cube->EA, cube->SPRITE);
	printf("\nF %d, %d, %d\nC %d, %d, %d\n", cube->G_COLOR.r, cube->G_COLOR.g, cube->G_COLOR.b, cube->R_COLOR.r, cube->R_COLOR.g, cube->R_COLOR.b);
	printf("\n Posx: %f, posy: %f, Max x: %d, Max y: %d\n",cube->player->x, cube->player->y, cube->map->max_x, cube->map->max_y);	
	printf("\nNombres de sprite : %d\n", cube->n_sprite);
	cube->mlx = init_mlx();
	load_texture(cube);

	display(cube);
	mlx_put_image_to_window(cube->mlx->mlx, cube->mlx->win, cube->mlx->img_ptr, 0, 0);
	mlx_hook(cube->mlx->win, 2, 1L<<0, key_press, cube);
	mlx_hook(cube->mlx->win, 3, 1L<<1, key_relache, cube);
	mlx_loop_hook(cube->mlx->mlx, deal_key, cube);
	mlx_loop(cube->mlx->mlx);



	kill_m(cube->map);
	kill_c(cube);
}
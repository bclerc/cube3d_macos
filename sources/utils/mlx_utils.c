/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:41:22 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/18 14:08:00 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void		init_hook(t_cube *cube)
{
	mlx_hook(cube->mlx->win, 2, 1L << 0, key_press, cube);
	mlx_hook(cube->mlx->win, 3, 1L << 1, key_relache, cube);
	mlx_loop_hook(cube->mlx->mlx, deal_key, cube);
	mlx_loop(cube->mlx->mlx);
}

int			key_press(int key, t_cube *cube)
{
	if (key == 53)
		exit(0);
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

int			key_relache(int key, t_cube *cube)
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

int			deal_key(t_cube *cube)
{
	if (cube->mlx->up == 1)
		move_up(cube);
	if (cube->mlx->down == 1)
		move_back(cube);
	if (cube->mlx->left == 1)
		turn_left(cube);
	if (cube->mlx->right == 1)
		turn_right(cube);
	display(cube);
	mlx_put_image_to_window(cube->mlx->mlx,
		cube->mlx->win, cube->mlx->img_ptr, 0, 0);
	return (1);
}

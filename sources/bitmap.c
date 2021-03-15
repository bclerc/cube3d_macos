/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:23:18 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/15 15:13:34 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	put_img_to_bmp(t_cube *cube, int fd)
{
	int y;
	int x;

	y = cube->r_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < cube->r_x)
		{
			write(fd, &cube->mlx->img_data
				[y * cube->mlx->size_line + x * (cube->mlx->bpp / 8)], 4);
			x++;
		}
		y--;
	}
}

void	set_bmp_header(t_cube *cube, int fd)
{
	int header;
	int plane;
	int size;

	size = cube->r_x * cube->r_y;
	plane = 1;
	header = 40;
	write(fd, &header, 4);
	write(fd, &cube->r_x, 4);
	write(fd, &cube->r_y, 4);
	write(fd, &plane, 2);
	write(fd, &cube->mlx->bpp, 2);
	size = 0;
	write(fd, &size, 4);
	write(fd, &size, 4);
	write(fd, &size, 4);
	write(fd, &size, 4);
	write(fd, &size, 4);
	write(fd, &size, 4);
	put_img_to_bmp(cube, fd);
}

void	set_header(t_cube *cube, int fd)
{
	int size;
	int of;

	of = 54;
	size = 14 + 40 + 4 * (cube->r_x * cube->r_y);
	write(fd, "BM", 2);
	write(fd, &size, 4);
	size = 0;
	write(fd, &size, 4);
	write(fd, &of, 4);
	set_bmp_header(cube, fd);
}

void	to_bmp(t_cube *cube)
{
	int fd;

	printf("Creating save.bmp, Please wait ...\n");
	if (!(fd = open("save.bmp", O_CREAT | O_RDWR)))
		exit(-1);
	set_header(cube, fd);
	printf("save.bmp was created !");
}

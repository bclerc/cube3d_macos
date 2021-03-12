/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:14:03 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/12 16:24:05 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

/*
** SO = 0, NO = 1, WE = 2, EA = 3
*/

void		check_texture(t_cube *cube)
{
	t_texture **tex;

	tex = cube->texture;
	if (!tex[0]->imgptr)
		tex_error(cube->SO, "SO");
	if (!tex[1]->imgptr)
		tex_error(cube->NO, "NO");
	if (!tex[2]->imgptr)
		tex_error(cube->WE, "WE");
	if (!tex[3]->imgptr)
		tex_error(cube->EA, "EA");
	if (!tex[4]->imgptr)
		tex_error(cube->EA, "Sprite");
}

t_texture	**init_texture(void)
{
	t_texture	**texture;
	int			i;

	if (!(texture = (t_texture**)malloc(sizeof(t_texture*) * 5)))
		return (0);
	texture[0] = (t_texture*)malloc(sizeof(t_texture));
	texture[1] = (t_texture*)malloc(sizeof(t_texture));
	texture[2] = (t_texture*)malloc(sizeof(t_texture));
	texture[3] = (t_texture*)malloc(sizeof(t_texture));
	texture[4] = (t_texture*)malloc(sizeof(t_texture));
	return (texture);
}

void		load_image_texture(t_cube *cube)
{
	t_texture	**tex;
	void		*mlx;

	tex = cube->texture;
	mlx = cube->mlx->mlx;
	tex[0]->imgdat = (int *)mlx_get_data_addr(tex[0]->imgptr, &tex[0]->bpp,
		&tex[0]->size_line, &tex[0]->endian);
	tex[1]->imgdat = (int *)mlx_get_data_addr(tex[1]->imgptr, &tex[1]->bpp,
		&tex[1]->size_line, &tex[1]->endian);
	tex[2]->imgdat = (int *)mlx_get_data_addr(tex[2]->imgptr, &tex[2]->bpp,
		&tex[2]->size_line, &tex[2]->endian);
	tex[3]->imgdat = (int *)mlx_get_data_addr(tex[3]->imgptr, &tex[3]->bpp,
		&tex[3]->size_line, &tex[3]->endian);
	tex[4]->imgdat = (int *)mlx_get_data_addr(tex[4]->imgptr, &tex[4]->bpp,
		&tex[4]->size_line, &tex[4]->endian);
}

void		load_texture(t_cube *cube)
{
	t_texture **tex;

	tex = cube->texture;
	tex[0]->imgptr = mlx_xpm_file_to_image(cube->mlx->mlx, cube->SO,
		&tex[0]->w, &tex[0]->h);
	tex[1]->imgptr = mlx_xpm_file_to_image(cube->mlx->mlx, cube->NO,
		&tex[1]->w, &tex[1]->h);
	tex[2]->imgptr = mlx_xpm_file_to_image(cube->mlx->mlx, cube->WE,
		&tex[2]->w, &tex[2]->h);
	tex[3]->imgptr = mlx_xpm_file_to_image(cube->mlx->mlx, cube->EA,
		&tex[3]->w, &tex[3]->h);
	tex[4]->imgptr = mlx_xpm_file_to_image(cube->mlx->mlx, cube->SPRITE,
		&tex[4]->w, &tex[4]->h);
	check_texture(cube);
	load_image_texture(cube);
}

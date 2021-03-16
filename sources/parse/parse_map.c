/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:04:18 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/16 13:43:47 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void
	register_sprite(t_cube *cube)
{
	t_sprite	*tmp;
	int			i;
	int			x;
	int			y;

	if (!(tmp = (t_sprite*)malloc(sizeof(t_sprite) * cube->n_sprite)))
		return ;
	i = 0;
	x = 0;
	y = 0;
	while (cube->map->coord[y])
	{
		x = 0;
		while (cube->map->coord[y][x])
		{
			if (cube->map->coord[y][x] == '2')
			{
				tmp[i].x = (double)x + 0.5;
				tmp[i].y = (double)y + 0.5;
				tmp[i].dist = 0;
				cube->map->coord[y][x] = '0';
				i++;
			}
			x++;
		}
		y++;
	}
	cube->sprite = tmp;
}

int
	is_player(t_cube *cube, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		cube->player->check = 1;
		cube->player->view = c;
		cube->player->x = x + 0.05;
		cube->player->y = y + 0.05;
	}
	return (1);
}

int
	is_map(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	if (line[i] == '1' || line[i] == '0' || line[i] == '2')
		return (1);
	free(line);
	return (0);
}

int
	first_read(t_cube *cube)
{
	char	*line;
	int		length;
	int		y;
	int		x;

	x = 0;
	y = 0;
	length = 0;
	while (get_next_line(cube->fd_map, &line) == 1)
	{
		if (!(is_map(line)))
			continue;
		length = ft_strlen(line);
		if (length > x)
			x = length;
		y++;
		free(line);
	}
	free(line);
	close(cube->fd_map);
	cube->map->max_y = y;
	cube->map->max_x = x;
	return (1);
}

int
	parse_map(t_cube *cube)
{
	char	*line;
	int		fd;
	int		y;

	y = 0;
	cube->map->coord = (char **)malloc((cube->map->max_y + 1) * sizeof(char*));
	while (get_next_line(cube->fd_map2, &line) == 1)
	{
		if (!(is_map(line)))
			continue;
		cube->map->coord[y] = (char*)malloc((cube->map->max_x + 1)
			* sizeof(char));
		ft_bzero(cube->map->coord[y], cube->map->max_x + 1);
		ft_memcpy(cube->map->coord[y], line, ft_strlen(line));
		y++;
		free(line);
	}
	cube->map->coord[y] = 0;
	free(line);
	close(cube->fd_map2);
	return (0);
}

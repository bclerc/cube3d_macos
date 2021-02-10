/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:04:18 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/10 16:04:05 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cube3d.h"

int is_map(char *line)
{
	int i;
	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	free(line);
	return (0);
}

int first_read(t_cube *cube)
{
	char *line;
	int length;
	int	y;
	int x;

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

int parse_map(t_cube *cube)
{
	char *line;
	int fd;
	int y;
	
	y = 0;
	cube->map->coord = (char **)malloc((cube->map->max_y + 1) * sizeof(char*));
	while (get_next_line(cube->fd_map2, &line) == 1)
	{
		if (!(is_map(line)))
			continue;
		cube->map->coord[y] = (char*)malloc((cube->map->max_x + 1) * sizeof(char));
		ft_bzero(cube->map->coord[y], cube->map->max_x + 1);
		ft_memcpy(cube->map->coord[y],line, ft_strlen(line));
		y++;
		free(line);
	}
	cube->map->coord[y] = 0;
	free(line);	
	close(cube->fd_map2);
	return (0);
}
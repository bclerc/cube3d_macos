/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:55:21 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/09 14:15:03 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cube3d.h"

void	dispatch(t_cube *cube, char *line)
{
	int i;
	int valid;

	i = 0;
	def_path(cube, line);
	while (line[i])
	{
		if (line[i] == 'R')
			valid = param_r(cube, line);
		if (line[i] == 'F' || line[i] == 'C')
			valid = get_color(cube, line);;
		i++;
	}
}

int		init_cube(t_cube *cube)
{
	char *line;
	
	line = 0;
	while (get_next_line(cube->fd, &line) == 1)
	{
		dispatch(cube, line);
		free(line);
	}
	free(line);
	close(cube->fd);
	return (1);
}

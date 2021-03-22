/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:50:18 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/18 19:50:18 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int		def_path(t_cube *cube, char *line)
{
	char	**path;
	int		i;

	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O')
		param_path(&line[i + 2], &cube->no);
	if (line[i] == 'S' && line[i + 1] == 'O')
		param_path(&line[i + 2], &cube->so);
	if (line[i] == 'W' && line[i + 1] == 'E')
		param_path(&line[i + 2], &cube->we);
	if (line[i] == 'E' && line[i + 1] == 'A')
		param_path(&line[i + 2], &cube->ea);
	if (line[i] == 'S' && line[i + 1] == ' ')
		param_path(&line[i + 1], &cube->sprite_p);
	return (1);
}

int		param_path(char *line, char **path)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	*path = ft_strdup(&line[i]);
	return (1);
}

int		param_r(t_cube *cube, char *line)
{
	int i;

	i = 0;
	while (line[i] == 'R' || line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
	{
		cube->r_x = (cube->r_x * 10) + (line[i] - '0');
		i++;
	}
	if (line[i] == ' ')
	{
		i++;
		while (ft_isdigit(line[i]))
		{
			cube->r_y = (cube->r_y * 10) + (line[i] - '0');
			i++;
		}
	}
	else
		return (0);
	return (1);
}

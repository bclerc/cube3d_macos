/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:50:18 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/08 16:40:53 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int def_path(t_cube *cube, char *line)
{	int i;
	char **path;
	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O')
		param_path(&line[i + 2], &cube->NO);
	if (line[i] == 'S' && line[i + 1] == 'O')
		param_path(&line[i + 2], &cube->SO);
	if (line[i] == 'W' && line[i + 1] == 'E')
		param_path(&line[i + 2], &cube->WE);
	if (line[i] == 'E' && line[i + 1] == 'A')
		param_path(&line[i + 2], &cube->EA);
	if (line[i] == 'S' && line[i + 1] == ' ')
		param_path(&line[i + 1], &cube->SPRITE);
	return (1);
}

int param_path(char *line, char **path)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	*path = ft_strdup(&line[i]);
	return (1);
}

int param_r(t_cube *cube, char *line)
{
	int i;

	i = 0;
	while (line[i] == 'R' || line[i] == ' ')
	i++;
	while (ft_isdigit(line[i]))
	{
		cube->R_X = (cube->R_X * 10) + (line[i] - '0');
		i++;
	}
	if (line[i] == ' ')
	{
		i++;
		while (ft_isdigit(line[i]))
		{
			cube->R_Y = (cube->R_Y * 10) + (line[i] - '0');
			i++;
		}
	}
	else
	{
		return (0);
	}	
	return (1);	
}
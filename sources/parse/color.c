/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:16:44 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/08 16:11:08 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cube3d.h"

int set_color(int r, int g, int b, t_color *loc)
{
	loc->r = r;
	loc->g = g;
	loc->b = b;
	loc->a = 0;
	return (1);
}

int	get_color(t_cube *cube, char *line)
{
	char	**tab;
	int		i;

	i = 1;
	while (line[i] == ' ')
		i++;
		set_color(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]), &cube->G_COLOR);
	else
		set_color(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]), &cube->R_COLOR);
	return (1);
}
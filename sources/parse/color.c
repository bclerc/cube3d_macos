/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:16:44 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/08 16:58:20 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cube3d.h"

void	delete_tab(char **tab)
{
	int i;
	i = 0;
	while (tab[i])
		i++;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

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
	tab = ft_strsplit(&line[i], ',');
	if (line[0] == 'F')
		set_color(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]), &cube->G_COLOR);
	else
		set_color(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]), &cube->R_COLOR);
	i = 0;
	delete_tab(tab);
	return (1);
}
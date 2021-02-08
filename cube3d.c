/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:38:52 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/08 16:06:29 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cube3d.h"

void clean_param(t_cube *cube)
{
	cube->R_X = 0;
	cube->R_Y = 0;	
}


int main(int argc, char **argv)
{
	int fd;
	t_cube cube;

	clean_param(&cube);
	cube.fd = open(argv[1], O_RDONLY);
	if (argc > 2)
		return 0;
	if (fd < 0)
	{
		printf("Erreur: FD %s incorrect", argv[1]);
		return (0);
	}
	init_cube(&cube);
	printf("X: %d, Y: %d\nNO: %s\nSO %s\nWE %s\nEA %s\nS %s", cube.R_X, cube.R_Y, cube.NO, cube.SO, cube.WE, cube.EA, cube.SPRITE);
}
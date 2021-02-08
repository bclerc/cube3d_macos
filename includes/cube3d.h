/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:35:47 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/08 16:11:19 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "minilibx/mlx.h"

typedef struct s_color
{

	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
	
}				t_color;


/// cast int t_color
typedef	struct	s_cube
{	
	int fd;
	int R_X;
	int	R_Y;
	t_color G_COLOR;
	t_color R_COLOR;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *SPRITE;

}				t_cube;

int init_cube(t_cube *cube);
int	param_r(t_cube *cube, char *line);
int get_color(t_cube *cube, char *line);
int	def_path(t_cube *cube, char *line);
int	param_path(char *line, char **path);
#endif

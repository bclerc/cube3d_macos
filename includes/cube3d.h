/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:35:47 by bclerc            #+#    #+#             */
/*   Updated: 2021/02/11 15:20:04 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "minilibx/mlx.h"
# include <stdio.h>

typedef struct s_color
{

	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
	
}				t_color;

typedef struct	s_player
{
	int x;
	int y;
	int life;
	int shied;
	char view;
	int check;
}				t_player;

typedef	struct	s_map
{
	int parsed;
	int max_x;
	int max_y;
	char **coord;
}				t_map;

/// cast int t_color
typedef	struct	s_cube
{	
	int fd;
	int fd_map;
	int fd_map2;
	int R_X;
	int	R_Y;
	t_color G_COLOR;
	t_color R_COLOR;
	t_map 	*map;	
	t_player *player;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *SPRITE;
	char *file_name;

}				t_cube;

int		init_cube(t_cube *cube);
int		first_read(t_cube *cube);
int		param_r(t_cube *cube, char *line);
int		parse_map(t_cube *cube);
int		get_color(t_cube *cube, char *line);
int		def_path(t_cube *cube, char *line);
int		param_path(char *line, char **path);
int		check_map(t_cube *cube);
void	map_error(t_map *map, int x, int y);
#endif

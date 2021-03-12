/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:35:47 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/12 16:30:07 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft/libft.h"
# include <pthread.h>
# include "gnl/get_next_line.h"
# include "minilibx/mlx.h"
# include <stdio.h>
# include <math.h>
# define heigth 800
# define width	1200
# define k_up  126
# define k_down 125
# define k_left 123
# define k_right 124
# define rotspeed 0.06 
# define movespeed 0.30

typedef struct	s_sprite
{
	int x;
	int y;
	int dist;
}				t_sprite;

typedef struct s_texture
{
	void *imgptr;
	void *imgdat;
	int size_line;
	int bpp;
	int endian;
	int h;
	int w;

}				t_texture;

typedef	struct	s_sprite_s
{
	int		*sorder;
	double	*sdist;
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		screenx;
	int		vmscreen;
	int		sheight;
	int		drawstarty;
	int		drawstartx;
	int		drawendy;
	int		drawendx;
	int		swidth;
	int		texx;
	int		texy;

}				t_sprite_s;

typedef struct	s_raycast
{
	double camerax;
	double raydirx;
	double raydiry;
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	double pwalldist;
	double wallx;
	double step;
	int texx;
	int lineheight;
	double texPos;
	int texy;
	int	sprite;
	int y;
	int color;
	int drawstart;
	int drawend;
	int linehieght;
	int side;
	int stepx;
	int stepy;
	int hit;
	int mapx;
	int mapy;
	t_texture *texture;
	

}				t_raycast;
typedef struct	s_vector
{
	int x;
	int y;
}				t_vector;

typedef struct	s_mlx
{
	void *mlx;
	void *win;
	void *img_ptr;
	void *img_data;
	int	size_line;
	int	bpp;
	int endian;
	int up;
	int down;
	int left;
	int right;
	int	l;

}				t_mlx;	


typedef struct s_color
{

	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
	
}				t_color;

typedef struct	s_player
{
	double x;
	double y;
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
	double dirx;
	double diry;
	double planey;
	double planex;
	int fd;
	int fd_map;
	int fd_map2;
	int R_X;
	int	R_Y;
	int	n_sprite;
	int x;
	t_sprite  *sprite;
	t_raycast *cast;
	t_texture **texture;
	t_mlx *mlx;
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

t_texture	*get_direction(t_cube *cube, t_raycast *ray);
void	calc_draw(t_cube* cube, t_raycast *ray);
void	init_ray(int x, t_raycast *ray, t_cube *cube);
void	draw_pixel(int x, t_raycast *ray, t_cube *cube);
void	sortsprite(t_cube *cube, int sx, int sy);
int		calc_dist(t_cube *cube, int sx, int sy);
void	register_sprite(t_cube *cube);
void	drawsprite(t_cube *cube, t_raycast *ray);
void	tex_error(char *path, char *texture);
void	move_up(t_cube *cube);
void	move_back	(t_cube *cube);
void	turn_right(t_cube *cube);
void	turn_left(t_cube *cube);
void	error_m(char *msg);
void	map_error_m(t_map *map, int x, int y, char *msg);
void	display(t_cube *cube);
int		is_player(t_cube *cube, char c, int x, int y);
void	verline(t_mlx *mlx, int x, int y1, int y2, int color);
void	pixel_put(t_mlx *mlx, int x, int y, int color);
void	clear(t_mlx *mlx, int color);
int		first_read(t_cube *cube);
int		param_r(t_cube *cube, char *line);
int		parse_map(t_cube *cube);
int		get_color(t_cube *cube, char *line);
int		def_path(t_cube *cube, char *line);
int		param_path(char *line, char **path);
int		init_cube(t_cube *cube);
int		check_map(t_cube *cube);
t_cube  *init_cube_s();
t_mlx	*init_mlx();
t_map	*init_map();
t_player *init_player();
t_texture **init_texture();
void	load_texture(t_cube *cube);
void	map_error(t_map *map, int x, int y);
#endif

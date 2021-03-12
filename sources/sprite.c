/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:50:41 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/12 11:37:34 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
// px, py = Player position

int calc_dist(t_cube *cube, int sx, int sy)
{
	return (sqrt(pow((sx - (int)cube->player->x), 2) + pow((sy - (int)cube->player->y),2)));
}

void sortSprite(t_cube *cube, int sx, int sy)
{
	int i;
	int j;
	int n;
	t_sprite *sprite;
	t_sprite *sprite2;
	sprite = cube->sprite;
	n = cube->n_sprite;
	i = 0;
	while (i < n - 1)
	{
			sprite = &cube->sprite[i];
			sprite2 = &cube->sprite[i + 1];
			if (calc_dist(cube, sprite->x, sprite->y) > calc_dist(cube, sprite2->x, sprite2->y))
			{
				t_sprite tmp;
				tmp = cube->sprite[i];
				cube->sprite[i] = cube->sprite[i + 1];
				cube->sprite[i + 1] = tmp;
				i = 1;
			}
		i++;
	}

}
	
void *drawSprite(void *tmp)
{	
	t_sprite *sprite;
	t_cube *cube;
	t_raycast *ray;
	t_sprite_s s;
	cube = (t_cube*)tmp;

	int x = cube->x;
	if (!(s.sorder = (int*)malloc(cube->n_sprite * sizeof(int))))
		exit(1);
	s.sdist = (double*)malloc(cube->n_sprite * sizeof(double) + 1);
	ray = cube->cast;
	sprite = cube->sprite;
	sortSprite(cube, cube->player->x, cube->player->y);
 	 for(int i = 0; i < cube->n_sprite; i++)
    {
      s.sorder[i] = i;
      s.sdist[i] = ((cube->player->x - sprite[i].x) * (cube->player->x  - sprite[i].x) + (cube->player->y  - sprite[i].y) * (cube->player->y - sprite[i].y)); //sqrt not taken, unneeded
    }
    for(int i = cube->n_sprite-1; i >=0; i--)
    {
       s.spritex = sprite[s.sorder[i]].x - cube->player->x;
       s.spritey = sprite[s.sorder[i]].y - cube->player->y;


     s.invdet = 1.0 / (cube->planex * cube->diry - cube->dirx * cube->planey);

		s.transformx = s.invdet * (cube->diry * s.spritex - cube->dirx * s.spritey);
		s.transformy = s.invdet * (-cube->planey * s.spritex + cube->planex * s.spritey); 
      	s.screenx = (int)((width / 2) * (1 + s.transformx / s.transformy));
    	s.vmscreen = (int)(0.0 / s.transformy);
	
       s.sheight = abs((int)(heigth / (s.transformy) )) / 1;
      	s.drawstarty = -s.sheight / 2 + heigth / 2  + s.vmscreen;
      if(s.drawstarty < 0) s.drawstarty = 0;
      	s.drawendy = s.sheight / 2 + heigth / 2 + s.vmscreen;
      if(s.drawendy >= heigth) s.drawendy = heigth - 1;


      s.swidth = abs( (int) (heigth / (s.transformy))) / 1;
      s.drawstartx = -s.swidth / 2 + s.screenx;
      if(s.drawstartx < 0) s.drawstartx = 0;
		 s.drawendx = s.swidth / 2 + s.screenx;
      if(s.drawendx >= width) s.drawendx = width - 1;

    	if (x >= s.drawstartx &&  x < s.drawendx)
      {
        s.texx = (int)(256 * (x - (-s.swidth / 2 + s.screenx)) * 64 / s.swidth) / 256;
        if(s.transformy > 0 && x >= 0 && x < width && s.transformy < ray->pwalldist)
        {
        for (int y = s.drawstarty; y < s.drawendy; y++)
        {
         	int d = (y-s.vmscreen) * 256 - heigth * 128 + s.sheight * 128;
          	s.texy = ((d * 64) / s.sheight) / 256;

			ray->color = *(int*)&cube->texture[4]->imgdat[(s.texy * (cube->texture[4]->size_line) + s.texx * (cube->texture[4]->bpp/8))];
				if (ray->color != 0)
                pixel_put(cube->mlx, x, y, ray->color |= 0x000000FF);
        }
      }
	//  x++;
	}
    }
	free(s.sorder);
	free(s.sdist);
}
    
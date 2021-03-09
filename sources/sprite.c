/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:50:41 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/09 15:57:55 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
// px, py = Player position

double ZBuffer[width];
int calc_dist(int px, int py, int sx, int sy)
{
	return (sqrt(pow((sx - px), 2) + pow((sy - py),2)));
}

void sortSprite(t_sprite *sprite, int px, int py)
{
	int i;
	i = 0;
	while (i < 11)
	{
		calc_dist(px, py, sprite[i].x, sprite[i].y);
		printf("Sprite %d (%d %d) have dist : %d\n", i, sprite[i].x, sprite[i].y, calc_dist(px, py, sprite[i].x, sprite[i].y));
		i++;
	}
	
}
void *drawSprite(void *tmp)
{	t_sprite *sprite;
	t_cube *cube;
	cube = (t_cube*)tmp;
	t_raycast *ray;
	int x = cube->x;
	ray = cube->cast;
	sprite = cube->sprite;
    ZBuffer[x] = ray->pwalldist;
	int spriteOrder[cube->n_sprite];
	double spriteDistance[cube->n_sprite];
	sortSprite(sprite, cube->player->x, cube->player->y);
	while (1);
  for(int i = 0; i < cube->n_sprite; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((cube->player->x - sprite[i].x) * (cube->player->x  - sprite[i].x) + (cube->player->y  - sprite[i].y) * (cube->player->y - sprite[i].y)); //sqrt not taken, unneeded
    }

    
    for(int i = 0; i < cube->n_sprite; i++)
    {
      double spriteX = sprite[spriteOrder[i]].x - cube->player->x;
      double spriteY = sprite[spriteOrder[i]].y - cube->player->y;


      double invDet = 1.0 / (cube->planex * cube->diry - cube->dirx * cube->planey);

      double transformX = invDet * (cube->diry * spriteX - cube->dirx * spriteY);
      double transformY = invDet * (-cube->planey * spriteX + cube->planex * spriteY); 
      int spriteScreenX = (int)((width / 2) * (1 + transformX / transformY));
    int vMoveScreen = (int)(0.0 / transformY);
      int spriteHeight = abs((int)(heigth / (transformY) )) / 1;
      int drawStartY = -spriteHeight / 2 + heigth / 2  + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + heigth / 2 + vMoveScreen;
      if(drawEndY >= heigth) drawEndY = heigth - 1;

      int spriteWidth = abs( (int) (heigth / (transformY))) / 1;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= width) drawEndX = width - 1;
	int test = -(heigth * 128 - spriteHeight * 128);
    	if (x >= drawStartX && x < drawEndX)
      {
        int texX = (int)(256 * (x - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
        if(transformY > 0 && x >= 0 && x < width && transformY < ZBuffer[x])
        {
        for (int y = drawStartY; y < drawEndY; y++)
        {
         	 int d = (y * 256) + test;
          	int texY = ((d * 64) / spriteHeight) / 256;

			ray->color = *(int*)&cube->texture[4]->imgdat[(texY * (cube->texture[4]->size_line) + texX * (cube->texture[4]->bpp/8))];
            if (ray->color != 0)
                pixel_put(cube->mlx, x, y, ray->color);
        
        }
      }
	  x++;
	}
    }

}
    
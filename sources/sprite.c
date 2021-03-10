/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:50:41 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/10 17:13:36 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
// px, py = Player position

double ZBuffer[width];
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
	cube = (t_cube*)tmp;
	t_raycast *ray;
	int x = cube->x;
	ray = cube->cast;
	sprite = cube->sprite;
    ZBuffer[x] = ray->pwalldist;
	int spriteOrder[cube->n_sprite];
	double spriteDistance[cube->n_sprite];
	sortSprite(cube, cube->player->x, cube->player->y);
	for(int b = cube->n_sprite -1; b >= 0; b--)
	{
		//printf("Sprite %d (%d;%d) have dist : %d\n", b, sprite[b].x, sprite[b].y, calc_dist(cube, sprite[b].x, sprite[b].y));
	}
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
while(1);
}
    
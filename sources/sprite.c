/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:50:41 by bclerc            #+#    #+#             */
/*   Updated: 2021/03/08 07:06:44 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"


typedef struct Sprite
{
  double x;
  double y;
  int texture;
}       Sprite;

#define numSprites 19

Sprite sprite[numSprites] =
{
  {64, 13, 10}, 
};

double ZBuffer[width];

int spriteOrder[numSprites];
double spriteDistance[numSprites];

void drawSprite(t_cube *cube, t_raycast *ray, int x)
{

    ZBuffer[x] = ray->pwalldist;
  for(int i = 0; i < numSprites; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((cube->player->x - sprite[i].x) * (cube->player->x  - sprite[i].x) + (cube->player->y  - sprite[i].y) * (cube->player->y - sprite[i].y)); //sqrt not taken, unneeded
    }

    
    for(int i = 0; i < numSprites; i++)
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

      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
        if(transformY > 0 && stripe >= 0 && stripe < width && transformY < ZBuffer[stripe])
        {
        for(int y = drawStartY; y < drawEndY; y++)
        {
          int d = (y) * 256 - heigth * 128 + spriteHeight * 128;
          int texY = ((d * 64) / spriteHeight) / 256;


		ray->color = *(int*)&cube->texture[4]->imgdat[(texY * (cube->texture[4]->size_line) + texX * (cube->texture[4]->bpp/8))];
            if (ray->color != 0)
                pixel_put(cube->mlx, stripe, y, ray->color);
        //
        }
        }
      }
    }

}
    
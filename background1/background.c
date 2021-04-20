#include "background.h"

void initBack (background *b)
{
//background
b->imgback=IMG_Load("bg2.jpg");
b->posback.x=0;
b->posback.y=0;
//camera
b->camera.x=0;
b->camera.y=0;
b->camera.w=SCREEN_W; 
b->camera.h=SCREEN_H;
//musique
b->son=Mix_LoadMUS("son.mp3"); //Chargement de la musique
Mix_PlayMusic(b->son, -1); //Jouer infiniment la musique
}

void afficheBack (background b, SDL_Surface *ecran)
{
/* On blitte par-dessus l'écran */
SDL_BlitSurface(b.imgback,&b.camera,ecran,&b.posback);

}

void scrolling (background *b,int direction)
{
const int speed=6;
if (direction ==0)
		b->camera.x+=speed;
else if (direction ==1)
		b->camera.x-=speed;
else if (direction ==2)
		b->camera.y+=speed;
else if (direction ==3)
		b->camera.y-=speed;

}

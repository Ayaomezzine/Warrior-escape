/**
* @file main.c
* @brief Testing Program.
* @author aziz
* @version 1.0
* @date Apr 19, 2021
*
* Testing program for ennemi
*
*/
#include "ennemi.h"
int main(char argc, char argv[])
{
	ennemi e;
	int continuer = 1,i,j;
	int largeur_fenetre = 1280;
	int hauteur_fenetre = 640;
	SDL_Surface *screen = NULL;
	SDL_Surface *background = NULL;
	SDL_Rect pos;
	SDL_Event event;
	int volum = 50;

	personne p;
	int collision = 0;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	
	screen = SDL_SetVideoMode(largeur_fenetre, hauteur_fenetre, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("ENNEMI", NULL);

	background = IMG_Load("resources/image/background2.jpg");
	pos.x = 0;
	pos.y = 0;

    p.image[0]= IMG_Load("resources/image/ligne.png");
	p.pos.x = 315;
	p.pos.y = 250; 
	p.pos.w = p.image[0]->w;
	p.pos.h = p.image[0]->h;
   p.image[1]= IMG_Load("resources/image/hero.png");
	p.posh.x = 715;
	p.posh.y = 450; 
	p.posh.w = p.image[1]->w;
	p.posh.h = p.image[1]->h;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }

    Mix_Chunk  *music1;
    Mix_AllocateChannels(2);
    Mix_Music *music;
    music1 = Mix_LoadWAV("resources/sound/ClicDeSouris.wav");
    music= Mix_LoadMUS("resources/sound/music.mp3");
    Mix_VolumeMusic(volum);
    Mix_PlayMusic(music,-1);

	initEnnemi(&e);

	while(continuer)
	{ 
		collision = collisionBb(p,e);
		if(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				continuer = 0;
				break;
				case SDL_KEYDOWN:
				    switch (event.key.keysym.sym) 
                    {
                    	case SDLK_q:
                    	continuer = 0;
                    	break;
                    	case SDLK_d:
                    	p.pos.x+=7;
                    	break;
                    	case SDLK_g:
                    	p.pos.x-=7;
                    	break;
case SDLK_LEFT:
                    	p.posh.x+=7;
                    	break;
                    	case SDLK_RIGHT:
                    	p.posh.x-=7;
                    	break;
                    }
				break;
			}
		}

		if(collision == 1)
		{
			
                        e.num=1;
			Mix_PlayChannel(-1, music1, 0);
		}
       
       //deplacer et animer l'ennemi
		deplacerEnnemi(&e);
		animerEnnemi(&e);
		

       //afficher
		SDL_BlitSurface(background,NULL,screen,&pos);
		afficherEnnemi(e,screen);
SDL_Delay(140);
		SDL_BlitSurface(p.image[0],NULL,screen,&p.pos);
		
SDL_BlitSurface(p.image[1],NULL,screen,&p.posh);
		SDL_Flip(screen);  
	}

	
	SDL_FreeSurface(background);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(p.image[0]);
SDL_FreeSurface(p.image[1]);
	Mix_FreeChunk(music1);
	Mix_FreeMusic(music);

	for(i=0; i<2 ;i++)
	{
		for(j=0 ;j<3 ;j++)
		{
			SDL_FreeSurface(e.image[i][j]);
		}
	}

    SDL_Quit();
	return 0;
}

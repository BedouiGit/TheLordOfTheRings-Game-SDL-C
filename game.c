#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include<math.h>
#include<time.h>
#include <SDL/SDL_ttf.h>
#include "functions.h"
#include "menu.h"
#include "main.h"
int main()
{
  int choix;
TTF_Init();
settings s;
SDL_Surface *ecran;
perso* p1=NULL;
p1=malloc(sizeof(perso));
perso p=*p1;
perso* p2=NULL;
p2=malloc(sizeof(perso));
perso p3=*p2;
s=init_settings(s);
if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
     printf("%s", Mix_GetError());
    }
Mix_Music *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadMUS("music/music1.mp3"); //Chargement de la musique
    Mix_PlayMusic(musique, -1);
SDL_EnableKeyRepeat(10,10);

    SDL_Init(SDL_INIT_AUDIO);
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_EnableKeyRepeat(120,60);
    p=init_controls(p);
    p=animate_initialisation(p);
    p=initialisation_personnage(p);
    p.score[1]=3;
    p.hp[1]=80;
    p=initialiser_background(p);
    p3=init_controls_p2(p3);
    p3=animate_initialisation(p3);
    p3=initialisation_personnage(p3);
    p3.score[1]=3;
    p3.hp[1]=80;
    p3=initialiser_background(p3);
    p3.number=2;
    p.number=1;

while(choix!=3)
{
ecran = SDL_SetVideoMode(1920,1200,32,s.screen);
choix=menu(ecran);
if(choix==1) p=settings_surface(&s,p);
if(choix==2) credits(ecran);
if(choix==0)
{choix=choix_single_multiplayer(ecran);
p=choix_player(ecran,p);
if(choix==1) {p.number=3;p=level_one_singleplayer(p,s,ecran);ecran = SDL_SetVideoMode(1920,1200,32,s.screen);
if(p.done==1){p.pos.x=200;p.bg.x=0;p.hp[0]=100;p.hp[1]=60;level_two_singleplayer(p,s,ecran);p.done=0;}
if(p.done==1){p.pos.x=200;p.bg.x=0;p.hp[0]=100;p.hp[1]=60;level_three_singleplayer(p,s,ecran);p.done=0;}}
if(choix==2) {p.number=1; level_one_multiplayer(p,p3,s,ecran);}
}
}
return 0;
}

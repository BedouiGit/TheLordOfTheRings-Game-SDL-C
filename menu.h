#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "functions.h"
typedef struct
{
    SDL_Surface *image[2];
    SDL_Rect pos;
    int state;//SELECTIONNÉ OU NON SELECTIONNÉ
    int sound;//on off
}button_menu;
typedef struct
{
    SDL_Surface *image[3];
    SDL_Rect pos;
}button;
typedef struct
{
    Uint32 screen;//LE TYPE DE L AFFICHAGE
    int sfx_volume; //VOLUME DE SON BREF
    int music_volume;//VOLUME DE LA MUSIQUE
}settings;


settings init_settings(settings s);
perso settings_surface(settings *s,perso p);
int menu(SDL_Surface *ecran);
void credits(SDL_Surface *ecran);
//choix singleplayer or multiplayer
int choix_single_multiplayer(SDL_Surface *ecran);
perso choix_player(SDL_Surface *ecran,perso p);
#endif // MENU_H_INCLUDED

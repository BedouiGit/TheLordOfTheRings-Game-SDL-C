#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "menu.h"
#include "functions.h"
int menu(SDL_Surface *ecran)
{
    SDL_Surface *images=NULL;
    int i=0,exit=1;
    SDL_Rect mouse_pos;
    mouse_pos.w=1;
    mouse_pos.h=1;
    SDL_Event event;
    button_menu t[4];
    images=IMG_Load("menu.png");
    for(i=0; i<4; i++)
    {
        t[i].state=1;
        t[i].pos.x=46+462*i;
        t[i].pos.y=800;
        t[i].pos.h=145;
        t[i].pos.w=436;
	t[i].sound=1;
    }
    t[0].image[0]=IMG_Load("menu b/play.png");
    t[1].image[0]=IMG_Load("menu b/settings.png");
    t[2].image[0]=IMG_Load("menu b/credits.png");
    t[3].image[0]=IMG_Load("menu b/quit.png");
    t[0].image[1]=IMG_Load("menu b/play1.png");
    t[1].image[1]=IMG_Load("menu b/settings1.png");
    t[2].image[1]=IMG_Load("menu b/credits1.png");
    t[3].image[1]=IMG_Load("menu b/quit1.png");
    while(exit!=0)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_MOUSEMOTION)
            {
                mouse_pos.x=event.motion.x;
                mouse_pos.y=event.motion.y;
            }
            if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                for(i=0; i<4; i++)
                    if(t[i].state==2)
                        t[i].state++;

            }
        }
        for(i=0; i<4; i++)
        {
            if(t[i].state!=3)
            {
                if(bounding_box(mouse_pos,t[i].pos)==1)
                    {t[i].state=2;if(t[i].sound==1) {sound_effect("music/button click.wav",120);t[i].sound=0;}}
                else
                    {t[i].sound=1;t[i].state=1;}
            }
            if(t[i].state==3)
                    {   SDL_FreeSurface(images);
                        images=NULL;
                        SDL_FreeSurface(ecran);
                        return i;}
        }
        SDL_BlitSurface(images,NULL,ecran,NULL);
        for(i=0; i<4; i++)
        {
            SDL_BlitSurface(t[i].image[t[i].state-1],NULL,ecran,&t[i].pos);
        }
        SDL_Flip(ecran);

    }
    return 0;
}
void credits(SDL_Surface *ecran)
{
    SDL_Surface *images;
    char ch[50];int i=0;
    while(i<125)

    {i++;
        sprintf(ch,"%s%d%s","credits/Layer ",i,".png");
        images=IMG_Load(ch);
        SDL_Delay(10);
        SDL_BlitSurface(images,NULL,ecran,NULL);
        SDL_Flip(ecran);
        SDL_FreeSurface(images);
        images=NULL;
    }
}
settings init_settings(settings s)
{
s.screen=SDL_HWSURFACE;
s.sfx_volume=80;
s.music_volume=80;
return s;
}


perso settings_surface(settings *s,perso p)
{
    SDL_Surface *images=NULL,*ecran,*b,*b1;
    int i=0,exit=1,waiting=0;
    SDL_Rect mouse_pos,pos;
    mouse_pos.w=1;
    mouse_pos.h=1;
    ecran = SDL_SetVideoMode(1920,1200,32,(*s).screen);
    SDL_Event event,e;
    button_menu t[12];
    b=IMG_Load("button.png");
    b1=IMG_Load("button_s.png");
    for(i=0; i<10; i++)
    {
        t[i].state=1;
        t[i].image[0]=IMG_Load("button.png");
        t[i].image[1]=IMG_Load("button_s.png");
    }
            t[2].image[0]=IMG_Load("khit.png");
            t[3].image[0]=IMG_Load("khit.png");
    for(i=0; i<2; i++)
        {t[i].pos.h=52;t[i].pos.w=52;t[i].pos.x=459+i*407;t[i].pos.y=312;}
    for(i=2; i<4; i++)
	{t[i].pos.h=15;t[i].pos.w=300;t[i].pos.x=322+(i-2)*699;t[i].pos.y=204;}
    for(i=4; i<9; i++)
        {t[i].pos.h=52;t[i].pos.w=52;t[i].pos.x=434;t[i].pos.y=475+47*(i-4);}
    images=IMG_Load("settings2.png");
    while(exit!=0)
    {

        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_KEYDOWN)
            exit=0;
            if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                for(i=0; i<2; i++)
                    if(t[i].state==2)
                            t[i].state++;
                for(i=4; i<9; i++)
                    if(t[i].state==2)
                            t[i].state++;
                if(t[2].state==2)
                    {(*s).music_volume=(event.motion.x-t[2].pos.x)*128/300;sound_effect("music/button click.wav",(*s).music_volume);}
                if(t[3].state==2)
                    {(*s).sfx_volume=(event.motion.x-t[3].pos.x)*128/300;sound_effect("music/button click.wav",(*s).sfx_volume);}
            }
        }
        mouse_pos.x=event.motion.x;
        mouse_pos.y=event.motion.y;
        for(i=0; i<9; i++)
        {
            if(t[i].state!=3)
            {
		if(bounding_box(mouse_pos,t[i].pos)==1)
                    {t[i].state=2;if(t[i].sound==1) {if((i!=2)&&(i!=3))sound_effect("music/button click.wav",(*s).sfx_volume);t[i].sound=0;}}
                else
                    {t[i].sound=1;t[i].state=1;}
            }
            if(t[i].state==3)
            {t[i].state=1;
                if(i==0)
                    {if((*s).screen!=SDL_FULLSCREEN)(*s).screen=SDL_FULLSCREEN;ecran = SDL_SetVideoMode(1920,1200,32,(*s).screen);}
                if(i==1)
                    {if((*s).screen!=SDL_RESIZABLE)(*s).screen=SDL_RESIZABLE;ecran = SDL_SetVideoMode(1366,768,32,(*s).screen);}
                if(i>3)
                    {waiting=0;
                while(waiting==0)
                    while(SDL_PollEvent(&e))
                    if(e.type==SDL_KEYDOWN)
            {
                if(i==4)
                    p.k.move_left=e.key.keysym.sym;
                if(i==5)
                    p.k.move_right=e.key.keysym.sym;
                if(i==6)
                    p.k.sprinting=e.key.keysym.sym;
                if(i==7)
                    p.k.jumping=e.key.keysym.sym;
                    waiting=1;
            }


                    t[i].state=1;}
            }
        }

        SDL_BlitSurface(images,NULL,ecran,NULL);
        for(i=0;i<2;i++)
	    {
            SDL_BlitSurface(t[i].image[t[i].state-1],NULL,ecran,&t[i].pos);
	    }
	for(i=2;i<4;i++)
	    {
	    pos.y=t[i].pos.y-20;
        SDL_BlitSurface(t[i].image[0],NULL,ecran,&t[i].pos);
	    if(i==2) {pos.x=315+(*s).music_volume*300/140;if((*s).music_volume<127)SDL_BlitSurface(b,NULL,ecran,&pos);
	    else SDL_BlitSurface(b1,NULL,ecran,&pos);}
	    if(i==3) {pos.x=1020+(*s).sfx_volume*300/140;if((*s).sfx_volume<127)SDL_BlitSurface(b,NULL,ecran,&pos);
	    else SDL_BlitSurface(b1,NULL,ecran,&pos);}
	    }
        for(i=4;i<8;i++)
            SDL_BlitSurface(t[i].image[t[i].state-1],NULL,ecran,&t[i].pos);
        SDL_Flip(ecran);
    }
    return p;
}
int choix_single_multiplayer(SDL_Surface *ecran)
{
    SDL_Surface *image;int exit=0;SDL_Event e;
    image=IMG_Load("1p2p.png");
    SDL_BlitSurface(image,NULL,ecran,NULL);
    SDL_Flip(ecran);
    while(exit==0)
        {
        while(SDL_PollEvent(&e))
        if(e.type==SDL_KEYDOWN)
        if(e.key.keysym.sym==SDLK_ESCAPE) exit=1;
        if(e.key.keysym.sym==SDLK_a) return 1;
        if(e.key.keysym.sym==SDLK_b) return 2;
        }
    return 3;
}
perso choix_player(SDL_Surface *ecran,perso p)
{
    int i;
    char name[40];
    SDL_Surface *image;int exit=0;SDL_Event e;
    image=IMG_Load("male_female.png");
    SDL_BlitSurface(image,NULL,ecran,NULL);
    SDL_Flip(ecran);
    while(exit==0)
        {
        while(SDL_PollEvent(&e))
        if(e.type==SDL_KEYDOWN)
        if(e.key.keysym.sym==SDLK_ESCAPE) exit=1;
        if(e.key.keysym.sym==SDLK_f) {
    for(i=1; i<6; i++)
    {
        sprintf(name,"%s%d%s","char/female_right/Layer ",i+1,".png");
        p.p[0][i-1]=IMG_Load(name);
        sprintf(name,"%s%d%s","char/female_left/Layer ",i+1,".png");
        p.p[1][i-1]=IMG_Load(name);
        sprintf(name,"%s%d%s","char/female_right/Layer ",i+1,".png");
        p.p[2][i-1]=IMG_Load(name);
        sprintf(name,"%s%d%s","char/female_left/Layer ",i+1,".png");
        p.p[3][i-1]=IMG_Load(name);
    }
    return p;};
        if(e.key.keysym.sym==SDLK_m) {    for(i=1; i<6; i++)
    {
        sprintf(name,"%s%d%s","char/male_right/Layer ",i+1,".png");
        p.p[0][i-1]=IMG_Load(name);
        sprintf(name,"%s%d%s","char/male_left/Layer ",i+1,".png");
        p.p[1][i-1]=IMG_Load(name);
        sprintf(name,"%s%d%s","char/male_right/Layer ",i+1,".png");
        p.p[2][i-1]=IMG_Load(name);
        sprintf(name,"%s%d%s","char/male_left/Layer ",i+1,".png");
        p.p[3][i-1]=IMG_Load(name);
    }return p;};
        }
    return p;
}


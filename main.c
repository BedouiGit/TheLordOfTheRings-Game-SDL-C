#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include<math.h>
#include<time.h>
#include "functions.h"
#include "menu.h"

perso level_one_singleplayer(perso p,settings s,SDL_Surface *ecran)
{
    int exit=0,should_move=0,souris=0;
    ea b[5];
    int i,cpt_noun=0;
    char noun[30]="";
    int FPS = 30,NextTick, interval ;
    unsigned int time1=0;
    test tab[8];
    enigme t[20];
    enigmes tableau[3];
    int la=0,atick=0;
    SDL_Event event;
p.done=0;
    initialisation_e_s(tab);
    b[0]=initialisation_ea(b[0]);
    b[1]=initialisation_ea(b[1]);
    initialiser_enigme(t);
    init_test_enigmes(tableau);
    generate_enigmes(t);
    generate_enigmes(t);
saving r;
    generation_auto_reponses(t);
r=load_from_file();
if(choose_saved_or_no(ecran)==1)
{load_last_game(r,&p,tab);if(r.level==2) {p.done=1;return p;}}
    srand(time(NULL));
    cha9_cha9(t);
    FPS_Initial(&NextTick,&interval,FPS);
    while(exit==0)
    {
        {
            FPS_Fn(&NextTick,&interval);
            while( SDL_PollEvent( &event ) )
            {
                if(event.type==SDL_MOUSEBUTTONDOWN)
                    if(event.button.button == SDL_BUTTON_RIGHT)
                    {
                        p=mouvement_souris_initialiser(p,event.motion.x);
                        souris=1;SDL_BlitSurface(p.background[2],NULL,ecran,NULL);
                        ecran = SDL_SetVideoMode(1920,1200, 32, SDL_FULLSCREEN);
                    }
            }
            if(souris==1)
                p=mouvement_souris(ecran,p,&souris);
            if(should_move==1)
            {
                p=scrolling_background(p);
                p=animate_animation(p);
                gestion_pos_e_s(tab,p);
                gestion_position_absolue_e_s(tab,p);
            }
            b[0]=animation_ea(b[0]);
            p=mouvementv2(p,&should_move,&exit);
            p=gravity(p,p.background[1]);
            p=speed_control(p);
	    animation_e_s(tab);
            if(test_enemies(tab,p)==1)
                p=gestion_vie_et_score(p,-50,0);
            if(test_enemies_dodged(tab,p)==1)
            {
                p=gestion_vie_et_score(p,20,0);
                p.s.e_d++;
            }
            if(test_enigme(p,tableau)==1)
            {
                i=resolution_enigmes(ecran,t,p);
                if(i==-1)
                    p=gestion_vie_et_score(p,-20,0);
                else
                {
                    p=gestion_vie_et_score(p,1,(i-4)*10);
                    p.s.r_s++;
                }
            }

            p=jump_trigger(p);
            b[1]=animation_ea(b[1]);
            gestion_pos_e_s(tab,p);
            chasing_enemies(tab,p);
            b[0]=deplacement_aleatoire(b[0]);
            b[1]=deplacement_aleatoire(b[1]);
            affichage_background(p,ecran);
            affichage(p,ecran,tab,b,time1/1000);
            animate_blit(p,ecran);
	    minimap_singleplayer(p,ecran);
            p=jump(p);
            time1=compteur(&exit,2000);
            if(p.pos.x-p.bg.x>7800)
            {
                for(i=0; i<30; i++)
                {
                    SDL_SetAlpha(p.background[2],SDL_SRCALPHA,75);
                    SDL_BlitSurface(p.background[2], NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    SDL_Delay(50);
                }
		i=enigme_plumber(10);p=gestion_vie_et_score(p,0,i);
		if(i!=3)
                    {SDL_BlitSurface(p.background[2], NULL,ecran,NULL);
                    p.done=1;exit=1;}
		else p.hp[0]=-1;
            }
            if((restart(p)==1)||(p.hp[0]<0))
            {
		sound_effect("music/death.wav",s.sfx_volume);
                initialisation_e_s(tab);p.pos.x=200;p.bg.x=0;
                p.score[1]--;p.hp[0]=100;p.hp[1]=40;
                p.s.l_r--;
            }
            if(p.score[1]==0)
                return p;
            SDL_Flip(ecran);
        }
    }
if(p.done==0){r.level=1;
r=save(p,tab,r);
if(p.score[1]>0)
if(save_or_no(ecran)==1)
save_to_file(r);}
    return p;
}
perso level_two_singleplayer(perso p,settings s,SDL_Surface *ecran)
{
    int exit=0,should_move=0,souris=0;
    ea b[5];
    int i,cpt_noun=0;
    char noun[30]="";
    int FPS = 30,NextTick, interval ;
    unsigned int time1=0;
    test tab[8];
    enigme t[20];
    enigmes tableau[3];
    int la=0,atick=0;
    SDL_Event event;
    initialisation_e_s(tab);
    b[0]=initialisation_ea(b[0]);
    b[1]=initialisation_ea(b[1]);
    initialiser_enigme(t);
    init_test_enigmes(tableau);
    generate_enigmes(t);
    generate_enigmes(t);
p.background[0]=IMG_Load("map2.png");
p.background[1]=IMG_Load("mask2.png");
saving r;
    generation_auto_reponses(t);
    srand(time(NULL));
    cha9_cha9(t);
    FPS_Initial(&NextTick,&interval,FPS);
	if(r.level==3) {p.done=1;return p;}    
	while(exit==0)
    {
        {
            FPS_Fn(&NextTick,&interval);
            while( SDL_PollEvent( &event ) )
            {
                if(event.type==SDL_MOUSEBUTTONDOWN)
                    if(event.button.button == SDL_BUTTON_RIGHT)
                    {
                        p=mouvement_souris_initialiser(p,event.motion.x);
                        souris=1;SDL_BlitSurface(p.background[2],NULL,ecran,NULL);
                        ecran = SDL_SetVideoMode(1920,1200, 32, SDL_FULLSCREEN);
                    }
            }
            if(souris==1)
                p=mouvement_souris(ecran,p,&souris);
            if(should_move==1)
            {
                p=scrolling_background(p);
                p=animate_animation(p);
                gestion_pos_e_s(tab,p);
                gestion_position_absolue_e_s(tab,p);
            }
            b[0]=animation_ea(b[0]);
            p=mouvementv2(p,&should_move,&exit);
            p=gravity(p,p.background[1]);
            p=speed_control(p);
	    animation_e_s(tab);
            if(test_enemies(tab,p)==1)
                p=gestion_vie_et_score(p,-50,0);
            if(test_enemies_dodged(tab,p)==1)
            {
                p=gestion_vie_et_score(p,20,0);
                p.s.e_d++;
            }
            if(test_enigme(p,tableau)==1)
            {
                i=resolution_enigmes(ecran,t,p);
                if(i==-1)
                    p=gestion_vie_et_score(p,-20,0);
                else
                {
                    p=gestion_vie_et_score(p,1,(i-4)*10);
                    p.s.r_s++;
                }
            }

            p=jump_trigger(p);
            b[1]=animation_ea(b[1]);
            gestion_pos_e_s(tab,p);
            chasing_enemies(tab,p);
            b[0]=deplacement_aleatoire(b[0]);
            b[1]=deplacement_aleatoire(b[1]);
            affichage_background(p,ecran);
            affichage(p,ecran,tab,b,time1/1000);
            animate_blit(p,ecran);
	    minimap_singleplayer(p,ecran);
            p=jump(p);
            time1=compteur(&exit,2000);
            if(p.pos.x-p.bg.x>7800)

            {
                for(i=0; i<30; i++)
                {
                    SDL_SetAlpha(p.background[2],SDL_SRCALPHA,75);
                    SDL_BlitSurface(p.background[2], NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    SDL_Delay(50);
                }
		i=ia_2_joueur_contre_l_ordinateur(ecran);p.done=1;
		if(i!=3)
                    {SDL_BlitSurface(p.background[2], NULL,ecran,NULL);
                    time1=compteur(&exit,2000);
                    highscores(p,ecran,time1/1000);
                    exit=1;}
		else p.hp[0]=-1;
            }
            if((restart(p)==1)||(p.hp[0]<0))
            {
		sound_effect("music/death.wav",s.sfx_volume);
                initialisation_e_s(tab);p.pos.x=200;p.bg.x=0;
                p.score[1]--;p.hp[0]=100;
                p.s.l_r--;
            }
            if(p.score[1]==0)
                exit=1;
            SDL_Flip(ecran);
        }
    }
r.level=2;
if(p.done==0){r.level=1;
r=save(p,tab,r);
if(p.score[1]>0)
if(save_or_no(ecran)==1)
save_to_file(r);}
    return p;
}
perso level_three_singleplayer(perso p,settings s,SDL_Surface *ecran)
{
    int exit=0,should_move=0,souris=0;
    ea b[5];
    int i,cpt_noun=0;
    char noun[30]="";
    int FPS = 30,NextTick, interval ;
    unsigned int time1=0;
    test tab[8];
    enigme t[20];
    enigmes tableau[3];
    int la=0,atick=0;
    SDL_Event event;
    initialisation_e_s(tab);
    b[0]=initialisation_ea(b[0]);
    b[1]=initialisation_ea(b[1]);
    initialiser_enigme(t);
    init_test_enigmes(tableau);
    generate_enigmes(t);
    generate_enigmes(t);
p.background[0]=IMG_Load("map3.png");
p.background[1]=IMG_Load("mask3.png");
saving r;
    generation_auto_reponses(t);
    srand(time(NULL));
    cha9_cha9(t);
    FPS_Initial(&NextTick,&interval,FPS);
    while(exit==0)
    {
        {
            FPS_Fn(&NextTick,&interval);
            while( SDL_PollEvent( &event ) )
            {
                if(event.type==SDL_MOUSEBUTTONDOWN)
                    if(event.button.button == SDL_BUTTON_RIGHT)
                    {
                        p=mouvement_souris_initialiser(p,event.motion.x);
                        souris=1;SDL_BlitSurface(p.background[2],NULL,ecran,NULL);
                        ecran = SDL_SetVideoMode(1920,1200, 32, SDL_FULLSCREEN);
                    }
            }
            if(souris==1)
                p=mouvement_souris(ecran,p,&souris);
            if(should_move==1)
            {
                p=scrolling_background(p);
                p=animate_animation(p);
                gestion_pos_e_s(tab,p);
                gestion_position_absolue_e_s(tab,p);
            }
            b[0]=animation_ea(b[0]);
            p=mouvementv2(p,&should_move,&exit);
            p=gravity(p,p.background[1]);
            p=speed_control(p);
	    animation_e_s(tab);
            if(test_enemies(tab,p)==1)
                p=gestion_vie_et_score(p,-50,0);
            if(test_enemies_dodged(tab,p)==1)
            {
                p=gestion_vie_et_score(p,20,0);
                p.s.e_d++;
            }
            if(test_enigme(p,tableau)==1)
            {
                i=resolution_enigmes(ecran,t,p);
                if(i==-1)
                    p=gestion_vie_et_score(p,-20,0);
                else
                {
                    p=gestion_vie_et_score(p,1,(i-4)*10);
                    p.s.r_s++;
                }
            }

            p=jump_trigger(p);
            b[1]=animation_ea(b[1]);
            gestion_pos_e_s(tab,p);
            chasing_enemies(tab,p);
            b[0]=deplacement_aleatoire(b[0]);
            b[1]=deplacement_aleatoire(b[1]);
            affichage_background(p,ecran);
            affichage(p,ecran,tab,b,time1/1000);
            animate_blit(p,ecran);
	    minimap_singleplayer(p,ecran);
            p=jump(p);
            time1=compteur(&exit,2000);
            if(p.pos.x-p.bg.x>7800)

            {
                for(i=0; i<30; i++)
                {
                    SDL_SetAlpha(p.background[2],SDL_SRCALPHA,75);
                    SDL_BlitSurface(p.background[2], NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    SDL_Delay(50);
                }
		i=ia_2_joueur_contre_l_ordinateur(ecran);p.done=1;
		if(i!=3)
                    {SDL_BlitSurface(p.background[2], NULL,ecran,NULL);
                    time1=compteur(&exit,2000);
                    highscores(p,ecran,time1/1000);
                    exit=1;}
		else p.hp[0]=-1;
            }
            if((restart(p)==1)||(p.hp[0]<0))
            {
		sound_effect("music/death.wav",s.sfx_volume);
                initialisation_e_s(tab);p.pos.x=200;p.bg.x=0;
                p.score[1]--;p.hp[0]=100;
                p.s.l_r--;
            }
            if(p.score[1]==0)
                exit=1;
            SDL_Flip(ecran);
        }
    }
r.level=3;
if(p.done==0){r.level=1;
r=save(p,tab,r);
if(p.score[1]>0)
if(save_or_no(ecran)==1)
save_to_file(r);}
    return p;
}

perso level_one_multiplayer(perso p,perso p1,settings s,SDL_Surface *ecran)
{
    int exit=0,should_move=0,exit1=0,should_move1=0,souris=0,x;
    ea b[5];
    int i,cpt_noun=0;
    char noun[30]="";
    int FPS = 30,NextTick, interval ;
    enigmes tableau[3],tableau1[3];
    unsigned int time1=0;
    test tab[8],tab1[8];
    enigme t[20],t1[8];
    int la=0,atick=0;
    SDL_Event event;
    b[0]=initialisation_ea(b[0]);
    b[1]=initialisation_ea(b[1]);
    initialiser_enigme_multiplayer(t);
    initialisation_e_s(tab);
    initialiser_enigme_multiplayer(t1);
    initialisation_e_s_p2(tab1);
    generate_enigmes(t);
    generate_enigmes(t);
    init_test_enigmes(tableau);
    init_test_enigmes(tableau1);
    generation_auto_reponses(t);
    srand(time(NULL));
    cha9_cha9(t);
    FPS_Initial(&NextTick,&interval,FPS);
    p.background[0]=IMG_Load("map1.png");
    p.background[1]=IMG_Load("mask.png");
    p1.background[0]=IMG_Load("map1.png");
    p1.background[1]=IMG_Load("mask.png");
    while(exit==0)
    {
        {
            FPS_Fn(&NextTick,&interval);
            while( SDL_PollEvent( &event ) )
            {
                if(event.type==SDL_KEYDOWN)
                {
                    i=i; // :)
                }
            }
            if(souris==1)
                p=mouvement_souris(ecran,p,&souris);
            if(should_move==1)
            {
                p=scrolling_background_multiplayer(p);

                p=animate_animation(p);
                gestion_pos_e_s(tab,p);
                gestion_position_absolue_e_s(tab,p);
            }
            if(should_move1==1)
            {
                p1=scrolling_background_multiplayer(p1);
                p1=animate_animation(p1);
                gestion_pos_e_s(tab1,p1);
                gestion_position_absolue_e_s(tab1,p1);
            }
            b[0]=animation_ea(b[0]);
            p=mouvementv2(p,&should_move,&exit);
            p=gravity(p,p.background[1]);
            p=speed_control(p);
	    p1=mouvementv2(p1,&should_move1,&exit1);
            p1=gravity(p1,p1.background[1]);
            p1=speed_control(p1);
            if(test_enemies(tab,p)==1)
                p=gestion_vie_et_score(p,-50,0);
            if(test_enemies_dodged_multiplayer(tab,p)==1)
            {
                p=gestion_vie_et_score(p,20,0);
                p.s.e_d++;
            }
	if(test_enemies(tab1,p1)==1)
                p1=gestion_vie_et_score(p1,-50,0);
            if(test_enemies_dodged_multiplayer(tab1,p1)==1)
            {
                p1=gestion_vie_et_score(p1,20,0);
                p1.s.e_d++;
            }
            if(test_enigme(p,tableau)==1)
            {
                i=resolution_enigmes_multiplayer(ecran,t,p);
                if(i==-1)
                    p=gestion_vie_et_score(p,-20,0);
                else
                {
                    p=gestion_vie_et_score(p,1,(i-4)*10);
                    p.s.r_s++;
                }
            }
	if(test_enigme(p1,tableau1)==1)
            {
                i=resolution_enigmes_multiplayer(ecran,t1,p1);
                if(i==-1)
                    p1=gestion_vie_et_score(p1,-20,0);
                else
                {
                    p1=gestion_vie_et_score(p1,1,(i-4)*10);
                    p1.s.r_s++;
                }
            }
            p=jump_trigger(p);
	    p1=jump_trigger(p1);
            b[1]=animation_ea(b[1]);
            gestion_pos_e_s(tab,p);
            chasing_enemies(tab,p);
            gestion_pos_e_s(tab1,p1);
            chasing_enemies(tab1,p1);
            b[0]=deplacement_aleatoire(b[0]);
            b[1]=deplacement_aleatoire(b[1]);
	affichage_background(p1,ecran);
	affichage_background(p,ecran);
	animate_blit(p,ecran);
	time1=compteur(&exit,2000);
	affichage_multiplayer(p,ecran,tab,b,time1/1000);


	animate_blit(p1,ecran);
            affichage_multiplayer(p1,ecran,tab1,b,time1/1000);

            p=jump(p);p1=jump(p1);
            if(p.pos.x-p.bg.x>7800)
            {
                for(i=0; i<30; i++)
                {
                    SDL_SetAlpha(p.background[2],SDL_SRCALPHA,75);
                    SDL_BlitSurface(p.background[2], NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    SDL_Delay(50);
                }
		player_one_won(ecran);
                    exit=1;
            }
            if(p1.pos.x-p1.bg.x>7800)
            {
                for(i=0; i<30; i++)
                {
                    SDL_SetAlpha(p.background[2],SDL_SRCALPHA,75);
                    SDL_BlitSurface(p.background[2], NULL,ecran,NULL);
                    SDL_Flip(ecran);
                    SDL_Delay(50);
                }
		player_two_won(ecran);
                    exit=1;
            }
            if((restart(p)==1)||(p.hp[0]<0))
            {
                initialisation_e_s(tab);
                p=initialisation_personnage(p);
                p.score[1]--;
                p.s.l_r--;
            }
	    if((restart(p1)==1)||(p1.hp[0]<0))
            {
                initialisation_e_s(tab1);
                p1=initialisation_personnage(p1);
                p1.score[1]--;
                p1.s.l_r--;
            }

            SDL_Flip(ecran);
        }
    }
    return p;
}






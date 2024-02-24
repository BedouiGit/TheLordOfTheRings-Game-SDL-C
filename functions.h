#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
/*-----------------------------------------------------LES STRUCTURES----------------------------------------------------*/
typedef struct
{
int e_d;//enemies_dodged
int r_s;//riddles solved
int l_r;//lives_remaining
}stats; //les variables pour l'affichage de score
typedef struct
{
    SDLKey move_left;
    SDLKey move_right;
    SDLMod jumping;
    SDLMod sprinting;
}keymapping;//input
typedef struct
{
SDL_Surface *p[6][4];//images perso
SDL_Rect pos;//position_perso
int direction;
int previous_direction;//pour savoir si le charactere a changé de direction ou non
int num;//numero animation
int hp[2];//hp et shield
int score[2];//score
int pos_absolue;//la position du personnage par rapport au background total
SDL_Surface *background[4];//les backgrounds
SDL_Rect bg;//la position du background
int next;//la position du mouvement du souris
int jump;//variable pour sauter
int speed;//la vitesse
int done;//savoir si le joueur a fini le jeu ou non
keymapping k;//les controls (input)
stats s;//les variables pour l'affichage de score
int number;//le numero du personnage(car il ya multiplayer)
}perso;//la structure du hero
typedef struct
{
SDL_Surface *image[2];//image de l entite secondaire
SDL_Rect pos;//position de l entite secondaire
SDL_Rect crop;//position pour la spritesheet de l entite secondaire
int xmin;//la position minimale
int xmax;//la position maximale
int d;//la direction
int num;//numero si l on affiche ou non
int speed;//la vitesse
int triggered;//state(si il te suit ou non)
}test;//la structure de l entite secondaire
typedef struct
{
SDL_Surface *image[2][5];//les images
SDL_Rect pos;//la position
int d;//la direction
int d1;//pour savoir si l entité a changé de direction ou non
int num;//numero si l on affiche ou non
int num_animation;//numero de l animation
int animation_speed;//la vitesse de l animation
int speed;//la vitesse
}ea;//entite_aleatoire
typedef struct
{
SDL_Surface *background;
SDL_Rect pos;
SDL_Surface * question;
SDL_Surface * answers[4];
int correct;
int type;
int used; // initialisation used=0;
}enigme;
typedef struct
{SDL_Rect pos_perso;//la position du personnage lors de l enregistrement
SDL_Rect pos_bg;//la position du background lors de l enregistrement
test t[3];//les entites secondaires lors de l enregistrement
int level;//le niveau lors de l enregistrement
int hp;//le hp du personnage lors de l enregistrement
}saving;//la structure pour sauvegarder
typedef struct
{
int x;//la position du declanchement de l enigme
int state;//si on a passé l enigme ou non
}enigmes;//structure pour la position du declanchement de l enigme

/*----------------------------------------------LES PROTOTYPES DES FONCTIONS---------------------------------------------*/
//gestion du temps
void afficher_temps_with_ticks(SDL_Surface *ecran,unsigned int time,int finish);
unsigned int compteur(int *exit,int exit_time);
int compteur_maze(int difficulty);
//


void gestion_position_absolue_e_s(test tab[8],perso p);
perso gestion_position_absolue(perso p);

//personnage
perso initialisation_personnage(perso p);
perso animate_initialisation(perso p);
perso animate_animation(perso p);
void animate_blit(perso p,SDL_Surface *ecran);

perso mouvement_souris_initialiser(perso p,Sint32 x);
perso mouvement_souris(SDL_Surface *ecran,perso p,int *souris);

perso mouvementv2(perso p,int *should_move,int *exit);
perso speed_control(perso p);

perso gravity(perso p,SDL_Surface *ecran);
perso jump(perso p);
perso jump_trigger(perso p);

int restart(perso p);

perso gestion_vie_et_score(perso p,int health,int score);
void afficher_personnage(SDL_Surface *screen,perso p,unsigned int time);

perso init_controls(perso p);
perso init_controls_p2(perso p);

void afficher_personnage_multiplayer(SDL_Surface *screen,perso p,unsigned int time);
//entites secondaires
void initialisation_e_s(test t[8]);
void affichage_entites_secondaires(test t[8],SDL_Surface *ecran);
void affichage_entites_secondaires_multiplayer(test t[8],SDL_Surface *ecran,int n);
void animation_e_s(test t[8]);

//les collisions
int collision_trigo(SDL_Rect t1,SDL_Rect t2);
int bounding_box(SDL_Rect t1,SDL_Rect t2);
SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);
int color_test(SDL_Surface *pSurface,perso p);
int ground_test(SDL_Surface *pSurface,perso p);
int roof_test(SDL_Surface *pSurface,perso p);

int test_enemies(test t[8],perso p);

//background
perso initialiser_background(perso p);
perso scrolling_background(perso p);
perso scrolling_background_multiplayer(perso p);
int test_scrolling(perso p);
void affichage_background(perso p,SDL_Surface *ecran);
//affichage total
void affichage(perso p,SDL_Surface *ecran,test tab[8],ea b[5],unsigned int time);
void affichage_multiplayer(perso p,SDL_Surface *ecran,test tab[8],ea b[5],unsigned int time);
//entite aleatoire
void affichage_ea(ea b,SDL_Surface *ecran);
ea deplacement_aleatoire(ea b);
ea initialisation_ea(ea b);
ea animation_ea(ea b);

//enigmes
int afficherenigme(SDL_Surface *screen,enigme t[20]);
void initialiser_enigme(enigme t[20]);
void cha9_cha9(enigme t[20]);
void generate_enigmes(enigme t[20]);
void generation_auto_reponses(enigme t[20]);
int resolution_enigmes(SDL_Surface *ecran,enigme t[20],perso p);

int test_enigme(perso p,enigmes t[3]);
void init_test_enigmes(enigmes t[3]);
//enigmes multiplayer
int afficherenigme_multiplayer(int n,SDL_Surface *screen,enigme t[20]);
void initialiser_enigme_multiplayer(enigme t[20]);
void generate_enigmes_multiplayer(enigme t[20]);
void generation_auto_reponses_multiplayer(enigme t[20]);
int resolution_enigmes_multiplayer(SDL_Surface *ecran,enigme t[20],perso p);
//autre type d enigmes
int enigme_plumber(int size);

//FPS
void FPS_Initial(int *NextTick,int *interval,int FPS);
void FPS_Fn(int *NextTick,int *interval);
//entites secondaires
void gestion_pos_e_s(test t[8],perso p);
int trigger_chase(SDL_Rect t1,SDL_Rect t2);
SDL_Rect chase(SDL_Rect t1,SDL_Rect t2);
void chasing_enemies(test t[8],perso p);
void initialisation_e_s_p2(test t[8]);
int test_enemies_dodged(test t[8],perso p);
int test_enemies_dodged_multiplayer(test t[8],perso p);

//score au fin du jeu
int input(SDL_keysym k,char nom[30],int i);
void highscores(perso p,SDL_Surface *ecran,unsigned int time1);

//ajout du zoom
void zoom_affichage(SDL_Surface *image,SDL_Surface *ecran);

//IA2 jouer contre l ordinateur
int ia_2_joueur_contre_l_ordinateur(SDL_Surface *ecran);

//sauvegarde
saving save(perso p,test t[8],saving s);
void save_to_file(saving s);
saving load_from_file();
void load_last_game(saving s,perso *p,test t[8]);
int choose_saved_or_no(SDL_Surface *ecran);
int save_or_no(SDL_Surface *ecran);

//minimap
void minimap_singleplayer(perso p,SDL_Surface *screen);
void minimap_multiplayer(perso p,perso p1,SDL_Surface *screen);
void minimap_singleplayer2(perso p,SDL_Surface *screen);
void minimap_multiplayer2(perso p,perso p1,SDL_Surface *screen);
void minimap_singleplayer3(perso p,SDL_Surface *screen);
void minimap_multiplayer3(perso p,perso p1,SDL_Surface *screen);

//multiplayer gagnant
void player_one_won(SDL_Surface *ecran);
void player_two_won(SDL_Surface *ecran);

//BONUS:gestion du son
void sound_effect(char ch[20],int volume);
void music(char ch[20],int volume);











//void testing(SDL_Surface *ecran,perso p);
#endif // FUNCTIONS_H_INCLUDED

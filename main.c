#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 780
#define IMAGE1 "images/Calque 3.jpg"
#define IMAGE2 "images/Calque 21.jpg"
#define IMAGE3 "images/Calque 22.jpg"
#define IMAGE4 "images/Calque 23.jpg"
#define IMAGE5 "images/Calque 31.jpg"
SDL_Window *pWindow; //pointeur pointant sur paramètres window
SDL_Renderer *pRenderer;//pointeur pointant sur paramètres renderer


typedef struct Element Element;
struct Element
{
    SDL_Texture* sdlTexture;
    Element *suivant;
};

typedef struct File File;
struct File
{
    Element *premier;
    Element *dernier;
    int n_taille;
};

//Prototypes
File* initialisation();
void enfiler(File *file, SDL_Texture* sdlNewTexture);
int defiler(File *file);
void afficherFile(File *file);
void retourneTaille(File* file);
void consultPrems(File *file);
void consultdernier(File *file);

int main(int argc, char *argv[])
{
        initSDL();

        char* img1 = IMAGE1;
        char* img2 = IMAGE2;
        char* img3 = IMAGE3;
        char* img4 = IMAGE4;
        char* img5 = IMAGE5;

        SDL_Surface *pSurface1 = NULL;
        SDL_Surface *pSurface2 = NULL;
        SDL_Surface *pSurface3 = NULL;
        SDL_Surface *pSurface4 = NULL;
        SDL_Surface *pSurface5 = NULL;

        SDL_Texture *pTexture1 = NULL;
        SDL_Texture *pTexture2 = NULL;
        SDL_Texture *pTexture3 = NULL;
        SDL_Texture *pTexture4 = NULL;
        SDL_Texture *pTexture5 = NULL;




        pSurface1 = IMG_Load(img1);
        pSurface2 = IMG_Load(img2);
        pSurface3 = IMG_Load(img3);
        pSurface4 = IMG_Load(img4);
        pSurface5 = IMG_Load(img5);

        if(!pSurface1||!pSurface2||!pSurface3||!pSurface4||!pSurface5)
        {
            SDL_Log("Unable to set surface: %s", SDL_GetError());
            return 1;
        }
        else
        {
            pTexture1 = SDL_CreateTextureFromSurface(pRenderer, pSurface1);
            pTexture2 = SDL_CreateTextureFromSurface(pRenderer, pSurface2);
            pTexture3 = SDL_CreateTextureFromSurface(pRenderer, pSurface3);
            pTexture4 = SDL_CreateTextureFromSurface(pRenderer, pSurface4);
            pTexture5 = SDL_CreateTextureFromSurface(pRenderer, pSurface5);

            SDL_FreeSurface(pSurface1);
            SDL_FreeSurface(pSurface2);
            SDL_FreeSurface(pSurface3);
            SDL_FreeSurface(pSurface4);
            SDL_FreeSurface(pSurface5);
        }


    File *file = NULL;
    file = (File*)malloc(sizeof(File));

    File* maFile = initialisation();

    enfiler(maFile, pTexture1);
    enfiler(maFile, pTexture2);
    enfiler(maFile, pTexture3);
    enfiler(maFile, pTexture4);
    enfiler(maFile, pTexture5);


    //printf("\nContenu de la file :\n");
    afficherFile(maFile);

   // printf("\non defile %s\n", defiler(maFile));
    //printf("on defile %s\n", defiler(maFile));

   // printf("\nContenu de la file :\n");
    afficherFile(maFile);

    retourneTaille(maFile);

    consultPrems(maFile);

    consultdernier(maFile);



    return 0;
}

File* initialisation()
{
    File* file = (File*)malloc(sizeof(*file));
    file->premier = NULL;
    file->n_taille = NULL;

    return file;
}


void enfiler(File *file, SDL_Texture* sdlNewTexture)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->sdlTexture = sdlNewTexture;
    nouveau->suivant = NULL;


    if (file->premier != NULL)
    {

        Element *elementActuel = file->premier;
        while (elementActuel->suivant != NULL)
        {
            elementActuel = elementActuel->suivant;
            file->dernier = nouveau;


        }
        elementActuel->suivant = nouveau;
        file->n_taille++;
    }
    else
    {
        file->premier = nouveau;
    }
}

int defiler(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDefile = 0;

    Element* elementDepile = file->dernier;


    if (file->premier != NULL)
    {
        Element *elementDefile = file->premier;

        nombreDefile = elementDefile->sdlTexture;
        file->premier = elementDefile->suivant;
        free(elementDefile);
        file->n_taille--;
    }
     for(int n_i=0; n_i<file->n_taille; n_i++){
        if (file != NULL && file->dernier != NULL)
        {
            file->dernier = elementDepile->suivant;
            SDL_DestroyTexture(elementDepile->sdlTexture);
            //free(elementDepile);
            file->n_taille--;
        }
    }
    free(file);


    if(pRenderer){
        SDL_DestroyRenderer(pRenderer);
    }
    if(pWindow){
      SDL_DestroyWindow(pWindow);
    }

    return nombreDefile;
}

void afficherFile(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = file->premier;

    while (actuel != NULL)
    {
       // printf("%s\n", actuel->sdlTexture);
       SDL_Rect dst_Img={0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
            SDL_RenderCopy(pRenderer,actuel->sdlTexture,NULL,&dst_Img);
            SDL_RenderPresent(pRenderer);
            SDL_Delay(1000);
        actuel = actuel->suivant;
    }

  //  printf("\n");
}

void retourneTaille(File *file)
{
    //printf("La taille de la file est: %d\n", file->n_taille+1);
}

void consultPrems(File *file)

{
    Element *element = file->premier;

    if(file->premier != NULL){
      //  printf(" Le premier element est : %s\n", element->sdlTexture);
    }
}

void consultdernier(File *file)

{
    Element *element = file->dernier;

    if(file->dernier != NULL){
      //  printf(" Le dernier element est : %s\n", element->sdlTexture);
    }
}

void initSDL()
{
     //Initialisation de la SDL2
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){

        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }else{
        //Set window
        pWindow=SDL_CreateWindow("An SDL2 window",0,0,WINDOW_WIDTH,WINDOW_HEIGHT,
                                 SDL_WINDOW_SHOWN);
        //Set rendu
        if(pWindow){

            pRenderer=SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_PRESENTVSYNC);

        }

        //Set img flags
        int flags=IMG_INIT_JPG|IMG_INIT_PNG;
        int initted=IMG_Init(flags);
        if((initted&flags)!=flags){
             SDL_Log("IMG_Init:Failed to init required jpg and png support !\n");
             SDL_Log("IMG_Init: %s\n", IMG_GetError());

             return 1;

        }
    }
}



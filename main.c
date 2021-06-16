#include <stdio.h>
#include <stdlib.h>


typedef struct Element Element;
struct Element
{
    char* str_chaine;
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
void enfiler(File *file, char* str_newChaine);
int defiler(File *file);
void afficherFile(File *file);
void retourneTaille(File* file);
void consultPrems(File *file);
void consultdernier(File *file);

int main()
{
    File *file = NULL;
    file = (File*)malloc(sizeof(File));

    File* maFile = initialisation();

    enfiler(maFile, "Hello");
    enfiler(maFile, "Bonjour");
    enfiler(maFile, "Hola");
    enfiler(maFile, "Ullakut");
    enfiler(maFile, "Guten tag");
    enfiler(maFile, "Namaste");

    printf("\nContenu de la file :\n");
    afficherFile(maFile);

    printf("\non defile %s\n", defiler(maFile));
    printf("on defile %s\n", defiler(maFile));

    printf("\nContenu de la file :\n");
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


void enfiler(File *file, char* str_newChaine)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->str_chaine = str_newChaine;
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


    if (file->premier != NULL)
    {
        Element *elementDefile = file->premier;

        nombreDefile = elementDefile->str_chaine;
        file->premier = elementDefile->suivant;
        free(elementDefile);
        file->n_taille--;
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
        printf("%s\n", actuel->str_chaine);
        actuel = actuel->suivant;
    }

    printf("\n");
}

void retourneTaille(File *file)
{
    printf("La taille de la file est: %d\n", file->n_taille+1);
}

void consultPrems(File *file)

{
    Element *element = file->premier;

    if(file->premier != NULL){
        printf(" Le premier element est : %s\n", element->str_chaine);
    }
}

void consultdernier(File *file)

{
    Element *element = file->dernier;

    if(file->dernier != NULL){
        printf(" Le dernier element est : %s\n", element->str_chaine);
    }
}

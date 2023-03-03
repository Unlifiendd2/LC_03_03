#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure du Maillon
typedef struct m
{
    int n;
    char nom[100];
    struct m *next;

} Maillon;

// Initialisation d'un maillon
Maillon *initMaillon(int n, const char *nom)
{
    // allocation mémoire
    Maillon *temp = malloc(sizeof(Maillon));

    // Initialisation
    strcpy(temp->nom, nom);
    temp->n = n;
    temp->next = NULL;

    // Renvoie l'adresse allouée.
    return temp;
}

// Ajout fin récursif
void ajoutFinRecur(Maillon **pointeurSurListe, int n, const char *nom)
{
    // On récupère la liste
    Maillon *liste = *pointeurSurListe;

    if(liste == NULL){
        liste = initMaillon(n,nom);
    }else{
        ajoutFinRecur(&(liste->next), n, nom);
    }

    // on n'oublie pas de recoller la liste au pointeur
    *pointeurSurListe = liste;
}


void ajoutTete(Maillon ** pointeurSurListe, int n, const char * s) {
    if(*pointeurSurListe == NULL) {
        *pointeurSurListe = initMaillon(n, s);
    } else {
        Maillon * tmp = *pointeurSurListe;
        *pointeurSurListe = malloc(sizeof(Maillon));
        (*pointeurSurListe)->n = n;
        strcpy((*pointeurSurListe)->nom, s);
        (*pointeurSurListe)->next = tmp;
    }
}


// liberation de la liste avec while
void libererListe(Maillon **pointeurSurListe)
{
    Maillon *liste = *pointeurSurListe;
    Maillon *temp = NULL;

    while (liste != NULL)
    {
        temp = liste->next;
        free(liste);
        liste = temp;
    }

    *pointeurSurListe = NULL;
}

void liberationRecu(Maillon ** Pliste) {
    if (*Pliste == NULL)
        return;
    liberationRecu(&((*Pliste)->next));
    free(*Pliste);
    *Pliste = NULL;
}

void retirerDebut(Maillon ** Pliste) {
    if (*Pliste == NULL)
        printf("Impossible de retirer au debut : liste vide.");
    else {
        Maillon * tmp = (*Pliste)->next;
        free(*Pliste);
        *Pliste = tmp;
    }
}

void retirerFin(Maillon ** Pliste) {
    if (*Pliste == NULL)
        printf("Impossible de retirer à la fin : liste vide.");
    else {
        Maillon * head = *Pliste;
        Maillon * tmp = *Pliste;
        while(tmp->next != NULL) {
            *Pliste = tmp;
            tmp = tmp->next;
        }
        free(tmp);
        (*Pliste)->next = NULL;
        *Pliste = head;
    }
}

void rechercher(Maillon * liste, int n) {
    while (liste->n != n && liste->next != NULL) {
        liste = liste->next;
    }
    if (liste->n == n)
        printf("Nom du maillon %d : %s.", n, liste->nom);
    else
        printf("Le maillon n'existe pas.");
}

void afficherListeAvecWhile(Maillon *liste)
{

    if (liste == NULL)
    {
        printf("Liste vide \n");
    }
    else
    {
        printf("HEAD \n");
        while (liste != NULL)
        {
            printf("Nom : %s, Maillon: %d \n", liste->nom, liste->n);
            liste = liste->next;
        }
        printf("TAIL \n");
    }
}

void afficherListeAvecFor(Maillon *liste)
{

    if (liste == NULL)
    {
        printf("Liste vide \n");
    }
    else
    {
        for (; liste != NULL; liste = liste->next)
        {
            printf("Nom : %s, Maillon: %d \n", liste->nom, liste->n);
        }
    }
}

void afficherListeRecur(Maillon *liste)
{

    if (liste == NULL)
    {
        printf("TAIL\n");
    }
    else
    {
        printf("Nom : %s, Maillon: %d \n", liste->nom, liste->n);
        afficherListeRecur(liste->next);
    }
}




int main()
{
    printf("\n\n********* Liste simplement chaînée *********\n\n");
    Maillon *liste = NULL;

    // Ajout (recursive) en fin de liste (TAIL)
    ajoutFinRecur(&liste, 1, "A");
    ajoutFinRecur(&liste, 2, "B");
    afficherListeAvecWhile(liste);


    // Ajout en début de liste (HEAD)
    printf("\n\n********* Ajout au debut *********\n\n");
    ajoutTete(&liste, 3, "C");
    afficherListeAvecWhile(liste);


    // Ajout en fin de liste (TAIL)
    printf("\n\n********* Ajout a la fin *********\n\n");
    ajoutTete(&liste, 3456, "D");
    ajoutTete(&liste, 8293, "E");
    ajoutTete(&liste, 719, "F");
    ajoutTete(&liste, 70, "G");
    ajoutTete(&liste, 1023, "H");
    ajoutTete(&liste, 7, "I");
    afficherListeAvecWhile(liste);


    // Retrait au debut (HEAD)
    printf("\n\n********* Retrait au debut *************\n\n");
    retirerDebut(&liste);
    afficherListeAvecWhile(liste);


    // Retrait a la fin (TAIL)
    printf("\n\n********* Retrait a la fin *************\n\n");
    retirerFin(&liste);
    afficherListeAvecWhile(liste);


    // Recherche par n
    printf("\n\n*********** Recgerche par n ***************\n\n");
    int n;
    scanf("%d", &n);
    rechercher(liste, n);


    // Liberation
    printf("\n\n********* Free ******************\n\n");
    liberationRecu(&liste);
    afficherListeAvecWhile(liste);

    return 0;
}
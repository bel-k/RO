#include<stdio.h>
#include<stdlib.h>

#define MAX_ELEMS 30
#define ETAT_DEHORS -1
#define ETAT_ATTENTE -2
#define ETAT_TERMINE -3

typedef struct PILE {
    int tab[MAX_ELEMS];
    int sommet; // indique l'index du dernier element
} PILE;


// la fct creer liste
/*****************
 * creer et initialiser la pile
 * @return
 */
PILE *createTPile() {// declaration + allocation de la memoire
    PILE *pile = (PILE *) malloc(sizeof(PILE));
    pile->sommet = -1;//
    if (!pile)//si liste existe
    {
        printf("Erreur de location de la memoire");
        exit(0);
    }
    return ((PILE *) pile);
}//fin fct







/*************************
 * empiler une valeur dans une pile
 * @param pile
 * @param val valeur a empiler
 * @return 1 si la valeur est empile, 0 sinon
 */
int empiler_Tab(PILE *pile, int val) {

    if (!pile) // pile n'existe pas
        return ((int) 0);
    //pile existe pas
    if ((pile->sommet + 1) == MAX_ELEMS) //pile est saturee
        return ((int) 0);

    // empilage et incrementation du sommet
    pile->tab[++(pile->sommet)] = val;

    return ((int) 1); // empilage est bien effectuée
}//fin fct


/**************
 * depiler un element
 * @param pile
 * @return nombre element si l'element est depiler sinon 0
 */
int depiler_Tab(PILE *pile) {

    if (!pile) // pile n'existe pas
    {

        return ((int) 0);
    }

    if ((!(pile->sommet + 1))) //si le sommet == -1
    {

        return ((int) 0); //pile est vide
    }

    // depilage et decrementation du sommet
    return pile->tab[pile->sommet--]; // retourne la valeur depiler

}//fin fct

/***********
 * Afficher le contenu de la pile
 * @param pile
 */
void affiche_TPile(PILE *pile) {
    int i;
    //pile n'exist pas
    if (!pile) {
        printf("\nListe n'est pas initialisee\n");

        return;
    }
    // TPile est vide
    if (!(pile->sommet + 1)) {

        printf("\nla liste est vide\n");
        return;
    }


    for (i = 0; i <= pile->sommet; ++i)
        printf("%d\t", pile->tab[i]);
}


void LireGraphe(int matrice[MAX_ELEMS][MAX_ELEMS], int *n) {

    FILE *file = NULL;
    int i, j;

    file = fopen("matrice.txt", "r");
    if (!file) {
        printf("le fichier n existe pas \n");
        exit(-1);
    }
    fscanf(file, "%d\n", n);


    while (!feof(file)) {
        for (i = 0; i < *n; i++) {

            for (j = 0; j < *n; j++) {
                fscanf(file, "%d\t", &matrice[i][j]);

            }

        }
    }
    fclose(file);
}


void enumerer(int s, int n,
              int matrice[MAX_ELEMS][MAX_ELEMS],
              int etat[MAX_ELEMS], PILE *pile) {
    int y;
    for (y = 0; y < n; y++) {
        if (matrice[s][y] == 1) {
            if (etat[y] != ETAT_ATTENTE) {
                empiler_Tab(pile, y);
                printf(" chemin : \t");
                affiche_TPile(pile);
                printf("   \n");
                etat[y] = ETAT_ATTENTE;
                enumerer(y, n, matrice, etat, pile);
            } else if (etat[y] == ETAT_ATTENTE) {
                printf(" circuit : \t");
                affiche_TPile(pile);
                printf("%d  \n", y);
            }
        }
    }
    depiler_Tab(pile);
    etat[s] = ETAT_TERMINE;
}


void chemin(int s, int n, int matrice[MAX_ELEMS][MAX_ELEMS]) {

    PILE *pile = createTPile();
    int cpt;
    int etat[MAX_ELEMS];

    //initialiser le tableau etat
    for (cpt = 0; cpt < n; etat[cpt++] = ETAT_DEHORS);

    etat[s] = ETAT_ATTENTE;//en attente
    empiler_Tab(pile, s);
    enumerer(s, n, matrice, etat, pile);
}


void main() {
    int s, n, i, j, choix;
    int matrice[MAX_ELEMS][MAX_ELEMS];

    //lecture du graphe du fichier
    LireGraphe((matrice), &n);
    do {

        //initialiser le choix
        choix = -1;
        printf("\n *****************************************************************************************************************\n "
               "\n 1  : chercher tous les chemins issus d un sommet s    \n"
               "\n 2  : afficher matrice adjacence qui represente le graphe G\n"
               "\n 0  : quitter \n"

               "\n **********************************************************************************************************************\n "
               "\n >>>>>  ");

        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 0:
                break;
            case 1: {
                printf("la taille de la matrice d'adjacence est %d : \n\n ", n);
                printf("************************************************************************************************************\n\n");
                printf("le graph est compose par les sommets:\n");
                for (i = 0; i < n; i++)
                printf("sommet %d  \t", i);
                printf("  \n");
                printf("************************************************************************************************************\n\n");
                printf("inserer le  sommet S   \n");
                scanf("%d", &s);

                printf("************************************************************************************************************\n\n");
                chemin(s, n, matrice);
                break;
            }

            case 2: {
                printf("la matrice d'adjacence est \n");
                for (i = 0; i < n; i++) {
                    for (j = 0; j < n; j++) {
                        printf("%d \t", (matrice[i][j]));
                    }
                    printf("\n");
                }
                break;
            }
            default :
                printf("\n\nErreur : Choix Invalide\n\n");
        }
    } while (choix);

}
								
 	
 	
 	

#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMS 30


typedef struct Cellule
{
    int val;
    struct Cellule *svt;
}Cellule;

typedef struct PFile
{
    struct Cellule *tete;
    struct Cellule *queue;
    int taille;
}PFile;
 


PFile* createPFile()
{
    PFile *pfile = (PFile*) malloc(sizeof(PFile));

    if (!pfile)
    {
        printf("Erreur de location de la memoire");
        exit(0);
    }
    return pfile;
}



PFile *initialiser_PFile ()
{
    PFile *f = createPFile();
    f->tete=NULL; // on initialise la tete du PFile a NULL
    f->queue=NULL; // on initialise le queue du PFile a NULL
    f->taille=0; // on initialise la taille du PFile a 0
    return ((PFile*) f);
}

int PFile_existe (PFile *f)
{
    // 1 existe
    // 0 n'existe pas
    if (!f)
        return 0;
    return 1;
}

int PFile_vide (PFile *f)
{
    // 1 PFile vide
    // 0 PFile non vide
    if ((f->tete==NULL)&&(f->queue==NULL))
        return 1;
    return 0;
}


void enfiler_PFile(PFile *f, int sommet)
{
    Cellule *e=NULL; // declaration et initialiastion a NULL de l'Cellule a ajouter

    if (!PFile_existe(f)) // si la PFile n'existe pas
        return ;

    if (PFile_vide(f)) // si la PFile vide
    {
        e=(Cellule *)malloc(sizeof(Cellule)); // l'allocation du memeoire

        e->val = sommet;
        f->tete=e; // definition du nouveau tete
        f->queue=e; // definition du nouveau queue
        f->taille++; // l'incrementation du taille du file
    }
    else // si la PFile non vide
    {
        e=(Cellule *)malloc (sizeof(Cellule)); // l'allocation du memeoire

        e->val = sommet;
        f->queue->svt=e; // definition du nouveau tete
        f->queue=e;
        f->taille++; // l'incrementation du taille du file
    }
    return  ;
}

void defiler_PFile(PFile *f)
{
    Cellule *tmp; // pointeur de type Cellule vers l'Cellule a supprimer
    if (!PFile_existe(f)) //file n'existe pas
        
    if (PFile_vide(f)) //file est vide
        return ;

    // cas d'une seule Cellule
    if (f->taille == 1)
    {
        tmp = f->tete;
        f->tete= f->queue = NULL;
        f->taille--;
        free(tmp);
    }
    // cas de plusieurs Cellules
    else
    {
        tmp=f->tete; // on pointe sur le premier Cellule du file
        f->tete=f->tete->svt; // definition de la nouvelle tete du file
        free(tmp); // on supprimer le premier Cellule du file
        f->taille--; // decrimentation du taille du file
    }
    return  ;
}




void chemin(int s, int t, int n, int matrice[ MAX_ELEMS][ MAX_ELEMS]){
  	PFile* pFile =initialiser_PFile();// pour stocket les sommets 
	int  i,j, cpt  ;
	int marquer[ MAX_ELEMS];//sommet deja marquer
	//initialiser le tableau 
	for (cpt = 0; cpt < n; marquer[cpt++]=-1)
 	enfiler_PFile(pFile,s);
 	while ((!PFile_vide(pFile)) && marquer[t] == -1)
	{
		i = pFile->tete->val;
		defiler_PFile(pFile);
	 		for (j = 0; j < n; j++)
		{
			if (matrice[i][j] == 1)
			{
				if (marquer[j] == -1)
				{
					marquer[j] = i;
			 		enfiler_PFile(pFile,j);
				} 
			} 
		} 
	} 
	if (marquer[t] == -1)
	{
		printf("il n'existe pas de chemin entre %d et %d\n ", s+1, t+1);
	} 
	else{
		printf("le chemin de %d a %d dans l'ordre inverse est \n", s+1, t+1);
		j = t;
		while (j != s)
		{
	 		printf("%d<-", j + 1);
	  		j = marquer[j];
		}
		printf("%d \n", s + 1);
   	}
} 






void LireGraphe(int matrice[MAX_ELEMS][MAX_ELEMS],int *n){
	 
 FILE* file = NULL;
	 int i,j ;

	file = fopen("matrice.txt", "r");
	if (!file)
	{
		printf("le fichier n existe pas \n");
		exit(-1);
	}
	fscanf(file, "%d\n", n);
	 

	
	while (!feof(file))
	{
		for (i = 0; i < *n; i++)
		{	
			
			for (j = 0; j < *n; j++)
			{
				fscanf(file, "%d\t", &matrice[i][j]);	
			 
			}
		 
		}
	}
	fclose(file);
 
 
 }
void main()
{
	int s, t, n, i, j,choix;
	int matrice[MAX_ELEMS][MAX_ELEMS];
	 
	LireGraphe((matrice), &n);
	 do
    {
       
        //initialiser le choix
        choix = -1;
        printf("\n *****************************************************************************************************************\n "
               "\n 1  : chercher un chemin entre deux sommets du graphe G \n"
               "\n 2  : afficher matrice adjacence qui represente le graphe G\n"
               "\n 0  : quitter \n"
              
               "\n **********************************************************************************************************************\n "
               "\n >>>>>  ");

        scanf("%d", &choix); getchar();
         
       switch(choix)
        {
            case 0: break;
            case 1:
	
				printf("la taille de la matrice d'adjacence est %d : \n\n ", n);
				printf("************************************************************************************************************\n\n");
				printf("le graph est compose par les sommets:\n"	);
				for (i=0;i<n;i++)
				printf("sommet %d  \t", i+1);
				printf("  \n" );
				printf("************************************************************************************************************\n\n");
				printf("inserer le premier sommet S du chemin  \n");
				scanf("%d", &s);
				printf("inserer le dernier sommet T du chemin \n");
				scanf("%d", &t);
				printf("************************************************************************************************************\n\n");
				chemin(s - 1, t - 1, n, matrice);
				break;
				
			case 2:
                printf("la matrice d'adjacence est \n");
                for (i = 0; i < n; i++)
				{	
					for (j = 0; j < n; j++)
						{
						printf("%d \t", (matrice[i][j]));
						}
					printf("\n");
				}
                break;

	
 			default :   printf("\n\nErreur : Choix Invalide\n\n");


 		}
 	}while(choix);
 
}





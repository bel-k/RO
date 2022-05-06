#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMS 35
typedef struct Cellule
{
    char val;
    struct Cellule *svt;
}Cellule;


// la fct creer liste
Cellule * creer_PListe(int elem )
{
// declarer une variable de type pt
    Cellule* NE;
// allocation de la memoire
    NE=(Cellule*)malloc(sizeof(Cellule));
//si il y a un probleme d'allocation
    if(!NE)
    { 
        return((Cellule*)NULL);//retourner null
    }
//si l'allocatin est bien passer
//initialisation
    NE->val=elem;
    NE->svt=NULL;
     
    //retourner l'element de type Cellule
    return((Cellule*)NE);
}//fin fct


// fct taille liste
int taille_pliste(Cellule *list)
{ // declaration d'un pt
    Cellule *pt;
    // initialiser la variable compt a zero
    int compt=0;
    //cas ou la iste n'existe pas
    if(!list)
    { printf("liste n'existe pas !! \n");
        return((int)-2);
    }
// si la liste existe
    pt=list;
//tant que pt est != de null
    while(pt)
    {
// incrementer le compteur
        compt++;
        pt=pt->svt;
    }
    return((int)compt);
}//fin fct


Cellule *inserer_queue_PList(Cellule *list, int val ) {
    Cellule *ne;
    ne = creer_PListe(val );

    //cas ou la liste n'existe pas
    if(!list)
    { 
        return((Cellule*) ne);
    }

    Cellule *pt = NULL;
    for(pt = list; pt->svt; pt = pt->svt);

    pt->svt = ne;
    return ((Cellule*) list);

}


// Fct affiche tout les element de la liste
int afficher_plistCaractere(Cellule *list)
{
    // declaration des variable
    Cellule *pt;//pour parcourir la liste
    int compt;// donner les positions des elements
    //list n'exist pas
    if (!list)
        return -2 ;
    //Liste existe
    pt=list;
    compt=1;
    while(pt)//tant que ot n'est pas null
    {//
        printf("% c\t",  'A' +pt->val);
        compt++;
        pt=pt->svt;
    }
    return 1;// pour la gesti

}

// Fct affiche tout les element de la liste
int afficher_plistChiffre(Cellule *list)
{
    // declaration des variable
    Cellule *pt;//pour parcourir la liste
    int compt;// donner les positions des elements
    //list n'exist pas
    if (!list)
        return -2 ;
    //Liste existe
    pt=list;
    compt=1;
    while(pt)//tant que ot n'est pas null
    {   printf("% d\t",  pt->val);
        compt++;
        pt=pt->svt;
    }
    return 1;// pour la gesti

}
//fonction qui recherche si un element existe dans la liste
int recherche_elem(Cellule *list,int elm )
{	int result=0;
    //liste n'exist pas
    if (!list)
    {
       
        return((int)result);
    }
    // liste existe
    Cellule *pt=NULL;
	pt=list;// pour parcourir la liste
    
    while(pt)//tant que ot n'est pas null
    {
        
        if((pt->val)==elm)// element trouver
        result=1;
        pt=pt->svt;
    }
    // element n'existe pas dans laliste
    return((int)result);
}//fin fct



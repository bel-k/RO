#include<stdio.h>
#include<stdlib.h>
#include "list.c"

/**************************************************************************
*  fonction qui cherche les successeurs d'un élément(sommet) et les
* ajouter dans la liste  X+ = PlusList si le successeur n'appartient pas
* à cette liste (verifient si marquerSuc[successeur]=0 )
***************************************************************************/

Cellule *ChercherPlusList(Cellule *listSucc[MAX_ELEMS],Cellule *PlusList,
						int marquerSuc[MAX_ELEMS] ,int index) {

	Cellule *pt=NULL;//liste pour parcourir listSucc[index]
	int i;
	pt=listSucc[index];
	while(pt)
	{	//parcourir la liste adjacente et chercher si les succeseur  est dans la liste X+
		if(marquerSuc[pt->val]==0)
		{	PlusList=inserer_queue_PList(PlusList,pt->val);
			marquerSuc[pt->val]=1;
			
		}
		
			pt=pt->svt;
			
	}
	//return X+
	return((Cellule*)PlusList);
}
/**************************************************************************
* 	 fonction qui insere l'élément d'indice :index la liste  X+ = PlusList 
*	et cherche ses successeurs et les successeurs des successeurs et les ajouter
*	dans la liste  X+ si le successeur n'appartient pas à cette liste
*	(verifient si marquerSuc[successeur]=0 )
***************************************************************************/
Cellule *CreatelistPlus(Cellule *listSucc[MAX_ELEMS],int marquerSuc[MAX_ELEMS],
						int index){
	Cellule *PlusList=NULL;//la liste X+
	Cellule *pt=NULL;//pour parcourir PlusList
	//INSERER 1ER ELEMENT
 	if(	marquerSuc[index]==0){
	PlusList=inserer_queue_PList(PlusList,index);
	marquerSuc[index]=1;
	}
	pt=PlusList;
	while(pt){	 
	/*  si marquerSuc[index]= 0: l'élément n'a pas encore été ajouté à la liste PlusList(X+)
		si marquerSuc[index]= 1: l'élément deja ajouté dans la liste PlusList(X+) mais ses successeurs pas encore
		si marquerSuc[index]=2 : l'élément et ses successeurs deja ajouté dans la liste PlusList(X+)*/
		if(marquerSuc[pt->val]<= 1) {
		PlusList=ChercherPlusList(listSucc,PlusList,marquerSuc ,pt->val);
		 marquerSuc[pt->val]=2;}
		pt=pt->svt;
	}
	//return X+
	return((Cellule*)PlusList);
}
/**************************************************************************
*  fonction qui cherche les prédécesseurs d'un élément(sommet) et les
* ajouter dans la liste  X- = MoinsList si le prédécesseur n'appartient pas
* à cette liste (verifient si marquerPRE[prédécesseur]=0 )
***************************************************************************/
Cellule *ChercherMoinsList(Cellule *listPre[MAX_ELEMS],Cellule *MoinsList,
							int marquerPRE[MAX_ELEMS] ,int index) {

		Cellule *pt=NULL;//liste pour parcourir listPre[index]
		pt=listPre[index];
	int i;
	while(pt)
	
	{//parcourir la liste adjacente et chercher si les prédécesseur est dans la liste X-
		if(marquerPRE[pt->val]==0)
		{	MoinsList=inserer_queue_PList(MoinsList,pt->val);
			marquerPRE[pt->val]=1;
			
		}
		
			pt=pt->svt;
	}
	//return X-
	return(MoinsList);
}
/************************************************************************************************
*  	fonction qui insere l'élément d'indice:index et les ajoute dans la liste  X- = MoinsList
*	et cherche ses prédécesseur et les prédécesseurs des prédécesseurs et les ajoute dans la liste X-
* 	si le prédécesseur n'appartient pas à cette liste (verifient si marquerPRE[prédécesseur]=0 )
**************************************************************************************************/
Cellule *CreatelistMoins(Cellule *listPre[MAX_ELEMS],int marquerPRE[MAX_ELEMS],int index){
	Cellule *MoinsList=NULL;
	Cellule *pt=NULL;//pour parcourir MoinsList
	//INSERER 1ER ELEMENT
	if(	marquerPRE[index]==0){
	MoinsList=inserer_queue_PList(MoinsList,index);
	marquerPRE[index]=1;
	}
	pt=MoinsList;
	while(pt){	 
	/* 	si marquerPRE[index]= 0: l'élément n'a pas encore été ajouté à la liste MoinsList(X-)
		si marquerPRE[index]= 1: l'élément deja ajouté dans la liste MoinsList(X-) mais ses prédécesseur pas encore
		si marquerPRE[index]=2 : l'élément et ses prédécesseur deja ajouté dans la liste MoinsList(X-)*/
		if(marquerPRE[pt->val]<= 1) {
			MoinsList=ChercherMoinsList(listPre,MoinsList,marquerPRE ,pt->val);
			marquerPRE[pt->val]=2;
		}
		pt=pt->svt;
	}	//return X-
	return((Cellule*)MoinsList);
}

/************************************************************************************************
*  	fonction qui prend comme entree la liste X- = MoinsList et la liste X+ = PlusList
*	et retourne X' : la liste des éléments qui appartient à X+ et X+ 
**************************************************************************************************/
Cellule *intersection(Cellule *MoinsList,Cellule *PlusList,int marquer[MAX_ELEMS]) {
		Cellule *List=NULL;//la liste X'
		Cellule *pt=NULL;//liste pour parcourir PlusList X+
		pt=PlusList;
		while(pt){
			/*recherche_elem(): fontion qui cherche si un element apparttient a une liste 
			retourne 1 si l element est dans la liste et 0 sinon*/
			if(recherche_elem(MoinsList,pt->val )){//si x apparttient a X+ et X-
			List=inserer_queue_PList(List,pt->val);//inserer dans X' 
			marquer[pt->val]=1;}
			pt=pt->svt;
		}	
		//afficher_plist(List);
		return((Cellule*)List);
}

/************************************************************************************************
*  	fonction qui prend comme entree les tableaux de listes d'adjacences (représentation du graphe)
* 	et retourne le tableau de listes des composantes fortement connexe de graphe 
**************************************************************************************************/
int Cf(Cellule *CfList[MAX_ELEMS],Cellule *listSucc[MAX_ELEMS],Cellule *listPre[MAX_ELEMS],
		int marquerSuc[MAX_ELEMS],int marquerPRE[MAX_ELEMS],int marquer[MAX_ELEMS],int nbElm)
{
	int j,i=0,
		nbCF=0;//nombre de CF
	Cellule *ListP=NULL;
	Cellule *ListM=NULL;
	Cellule *pt=NULL;
	
	do{		//si i n'existe pas dans une CFc
		if(marquer[i]==0){	
			ListP=CreatelistPlus(listSucc ,marquerSuc,i);
			ListM=CreatelistMoins(listPre, marquerPRE,i);
			printf("\nla liste X+ :\n" );
			afficher_plistChiffre(ListP);
			printf("\nLa liste X- : \n" );
			afficher_plistChiffre(ListM);
		
			CfList[nbCF++]=intersection(ListP,ListM, marquer);
			printf("\nLa liste X' :\n" );
			afficher_plistChiffre(CfList[nbCF-1]);
			printf("\n\n" );
		}
		i++;
		for(j=0;j<nbElm;j++)
				{
					marquerSuc[j]=0;
					marquerPRE[j]=0;
					ListP=ListM=NULL;
				}
	}while(i<nbElm);
	printf(" \n le graphe est composer de %d composantes fortement connexes:\n",nbCF );
	for(i=0;i<nbCF;i++)
	{	printf("\n CFC %d :\t" ,i+1);
		afficher_plistChiffre(CfList[i]);
   		printf("\n" );
	}
	return((int )nbCF);
}

/*** fonction qui retourne la matrice du graphe réduit.*/
 
 void MatRed(int mat[MAX_ELEMS][MAX_ELEMS],Cellule *CfList[MAX_ELEMS],int nbCF,Cellule *listSucc[MAX_ELEMS]){
 	Cellule *pt1,*pt2,*pt3=NULL;
 	int i,j,indBreak=0,nbElm=nbCF;
 	for(i=0;i<nbCF;i++)
	{	
		nbElm=nbCF-1;//nbr de test pour remplire la matrice :exemple ligne c1 (3CFc)
		/* 	chercher un un arc entre c1 avec c2 ->nbElm--
			chercher un un arc entre c2 avec c3 ->nbElm--
			car c1 avec c1 par defaut mat[c1][c1]=0*/
		j=(i+1)%3;
		while(nbElm){
			pt1=CfList[i];
			pt2=CfList[j];
			indBreak=0;
			while(pt1)
				{	pt3=listSucc[pt1->val];
					while(pt3){
						if(recherche_elem(pt2,pt3->val )){
						indBreak=1;
						goto end;
						}
						pt3=pt3->svt;
					}
					pt1=pt1->svt;
				}
			end :
				 mat[i][j]=indBreak;
				j=(j+1)%3;
				nbElm--;}
	}
}
/************************
lire d un fichier
***********************/


void LireGraphe(Cellule *listSucc[MAX_ELEMS],Cellule *listPre[MAX_ELEMS]){
	 
 FILE* file = NULL;
	 int i,j,n ;

	file = fopen("listeAdj.txt", "r");
	if (!file)
	{
		printf("le fichier n existe pas \n");
		exit(-1);
	}
	fscanf(file, "%d\n", &n);
	i=0;
	/* *************************************************************
	la 1er ligne du fichier contient le nombre des sommets
		du 2EME ligne jusqu a la fin du fichier:
			+ de i=0 jusqu a i< nombre de sommet: chaque chiffre lu 
				est inserer dans la liste listSucc[i] et la lecture -1 
				determine la fin de la liste. et l incrementation de i
				
			+de i=nombre de sommet  jusqu a la fin du fichier: chaque chiffre lu 
				est inserer dans la liste listPre[i] et la lecture -1 
				determine la fin de la liste. et l incrementation de i
		**************************/
	while (!feof(file))
	{	//remplir le tableau de listes d'adjacences (succeseur). 
		if(i<n){
				fscanf(file, "%d\t", &j);
				if(j != -1){
					listSucc[i]=inserer_queue_PList(listSucc[i],j );
					}
				else i++;
			
		}
		// remplir le tableau de listes d'adjacences (prédécesseurs)
			else{
				fscanf(file, "%d\t", &j);
				if(j != -1){
					listPre[i%n]=inserer_queue_PList(listPre[i%n],j );
				}
				else i++;
				}
		//	
		 
		
	}
	fclose(file);
 
 
 }
 
void LireNbSommet(int *n){
	 
 FILE* file = NULL;
	file = fopen("listeAdj.txt", "r");
	if (!file)
	{
		printf("le fichier n existe pas \n");
		exit(-1);
	}
	fscanf(file, "%d\n", n);
	 	printf(" nombre de sommets de ce graphe : %d\n",*n);
 
	fclose(file);
 
 
 }
 
 
int main() {
	
	int i,j,	//des indice pour parcourir les tableaux
	nbElm,//nombre de sommets
	nbCF;	//nombre de CFC
	Cellule *listSucc[MAX_ELEMS];//tableau de listes d'adjacences (succeseur). 
	Cellule *CfList[MAX_ELEMS];// la liste X'
	Cellule *listPre[MAX_ELEMS];// tableau de listes d'adjacences (prédécesseurs)
	int marquerSuc[MAX_ELEMS];//si=1 element deja ajouter a la liste X+
	int marquerPRE[MAX_ELEMS];//si=1 element deja ajouter a la liste X-
	int marquer[MAX_ELEMS];//si=1 deja existe dans une CFC 
	int mat[MAX_ELEMS][MAX_ELEMS];//matrice du graphe réduit.
	//initialisation
	//lire nombre de sommets pour initialiser les structures
	LireNbSommet(&nbElm);
	for(i=0;i<nbElm;i++)
	{
		listSucc[i]=NULL;
		listPre[i]=NULL;
		CfList[i]=NULL;
		marquerSuc[i]=0;
		marquerPRE[i]=0;
		marquer[i]=0;
	}
	//lire les tableaux de listes d'adjacences
	LireGraphe(listSucc,listPre);
	
  	nbCF=Cf(CfList,listSucc, listPre,marquerSuc, marquerPRE, marquer, nbElm);
  	printf("\n") ;
  	//matrice du graph reduit
  	/*************************/
  	//initialisation de la matrice
	for(i=0;i<nbCF;i++)
	{
		for(j=0;j<nbCF;j++)	mat[i][j]=0;
	}
	/**********************/
	printf(" la matrice du graphe reduit :\n\n") ;
 	 MatRed( mat,CfList,nbCF,listSucc);
 	 //affichage de la matrice
  	for(i=0;i<nbCF;i++)
	{
		for(j=0;j<nbCF;j++)	printf("%d \t",mat[i][j]) ;
	 	printf("\n") ;
	}
return 1;
}//fin 

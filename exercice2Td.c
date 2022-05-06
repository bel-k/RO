#include<stdio.h>
#include<stdlib.h>
#include "list.c"


Cellule *ChercherPlusList(Cellule *listSucc[MAX_ELEMS],Cellule *PlusList,int marquerSuc[MAX_ELEMS] ,int index) {

	Cellule *pt=NULL;//liste pour parcourir listSucc[index]
	int i;
	pt=listSucc[index];
	while(pt)
	{	
		if(marquerSuc[pt->val]==0)
		{	PlusList=inserer_queue_PList(PlusList,pt->val);
			marquerSuc[pt->val]=1;
			
		}
		
			pt=pt->svt;
			
	}
	return((Cellule*)PlusList);
}

Cellule *ClistPlus(Cellule *listSucc[MAX_ELEMS],int marquerSuc[MAX_ELEMS],int index){
	Cellule *PlusList=NULL;
	Cellule *pt=NULL;//pour parcourir PlusList
	//INSERER 1ER ELEMENT
 	if(	marquerSuc[index]==0){
	PlusList=inserer_queue_PList(PlusList,index);
	marquerSuc[index]=1;
	}
	pt=PlusList;
	while(pt){	 
		
		if(marquerSuc[pt->val]<= 1) {	//on n a pas encore ajouter les succseseur
		PlusList=ChercherPlusList(listSucc,PlusList,marquerSuc ,pt->val);
		 marquerSuc[pt->val]=2;}
		pt=pt->svt;
	}

	return((Cellule*)PlusList);
}

Cellule *ChercherMoinsList(Cellule *listPre[MAX_ELEMS],Cellule *MoinsList,int marquerPRE[MAX_ELEMS] ,int index) {

		Cellule *pt=NULL;//liste pour parcourir listPre[index]
		pt=listPre[index];
	int i;
	while(pt)
	
	{
		if(marquerPRE[pt->val]==0)
		{	MoinsList=inserer_queue_PList(MoinsList,pt->val);
			marquerPRE[pt->val]=1;
			
		}
		
			pt=pt->svt;
	}
	
	return(MoinsList);
}

Cellule *ClistMoins(Cellule *listPre[MAX_ELEMS],int marquerPRE[MAX_ELEMS],int index){
	Cellule *MoinsList=NULL;
	Cellule *pt=NULL;//pour parcourir MoinsList
	//INSERER 1ER ELEMENT
	if(	marquerPRE[index]==0){
	MoinsList=inserer_queue_PList(MoinsList,index);
	marquerPRE[index]=1;
	}
	pt=MoinsList;
	while(pt){	 
		
		if(marquerPRE[pt->val]<= 1) {	//on n a pas encore ajouter les succseseur
		MoinsList=ChercherMoinsList(listPre,MoinsList,marquerPRE ,pt->val);
		marquerPRE[pt->val]=2;
		}
		pt=pt->svt;
	}
	return((Cellule*)MoinsList);
}


Cellule *intersection(Cellule *MoinsList,Cellule *PlusList,int marquer[MAX_ELEMS]) {
		Cellule *List=NULL;//la liste X'
		Cellule *pt=NULL;//liste pour parcourir PlusList X+
		pt=PlusList;
		while(pt){
			if(recherche_elem(MoinsList,pt->val )){//si x apparttient a X+ et X-
			List=inserer_queue_PList(List,pt->val);
			marquer[pt->val]=1;}
			pt=pt->svt;
		}	
		//afficher_plist(List);
		return((Cellule*)List);
}

int Cf(Cellule *CfList[MAX_ELEMS],Cellule *listSucc[MAX_ELEMS],Cellule *listPre[MAX_ELEMS],
		int marquerSuc[MAX_ELEMS],int marquerPRE[MAX_ELEMS],int marquer[MAX_ELEMS],int nbElm)
{
	int j,i=0,
		nbCF=0;//nombre de CF
	Cellule *ListP=NULL;
	Cellule *ListM=NULL;
	Cellule *pt=NULL;
	
	do{		//si i n existe pas dans une CF
		if(marquer[i]==0){	
			ListP=ClistPlus(listSucc ,marquerSuc,i);
			ListM=ClistMoins(listPre, marquerPRE,i);
			//if((ListM==NULL)|| (ListP==NULL)) goto pp;
			printf("\nla liste X+ \n" );
			afficher_plistCaractere(ListP);
			printf("\n liste X- \n" );
			afficher_plistCaractere(ListM);
		
			CfList[nbCF++]=intersection(ListP,ListM, marquer);
			printf("\n liste X' \n" );
			afficher_plistCaractere(CfList[nbCF-1]);
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
	printf(" \n le graphe est composer de %d composantes connexes:\n",nbCF );
	for(i=0;i<nbCF;i++)
	{	printf("\n CF %d :\t" ,i+1);
		afficher_plistCaractere(CfList[i]);
   		printf("\n" );
	}
	return((int )nbCF);
}

 //matrice reduite
 
 void MatRed(int mat[MAX_ELEMS][MAX_ELEMS],Cellule *CfList[MAX_ELEMS],int nbCF,Cellule *listSucc[MAX_ELEMS]){
 	Cellule *pt1,*pt2,*pt3=NULL;
 	int i,j,
	 	indBreak=0,
		nbElm=nbCF;
 	for(i=0;i<nbCF;i++)
	{	
		nbElm=nbCF-1;//nbr de test pour remplire la matrice :exemple ligne c1 (3CF)
		/* 	chercher un un arc entre c1 avec c2 ->nbElm--
			chercher un un arc entre c2 avec c3 ->nbElm--
			car c1 avec c1 automatiquement mat[c1][c1]=0*/
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
				nbElm--;
		}
	}
}
/************************
lire d un fichier
***********************/


void LireGraphe(Cellule *listSucc[MAX_ELEMS],Cellule *listPre[MAX_ELEMS]){
	 
 FILE* file = NULL;
	 int i,j,n ;

	file = fopen("listeAdjTd.txt", "r");
	if (!file)
	{
		printf("le fichier n existe pas \n");
		exit(-1);
	}
	fscanf(file, "%d\n", &n);

	i=0;
	
	while (!feof(file))
	{
			printf("HORS i= %d\n",i);
		if(i<n){
		 		
				fscanf(file, "%d\t", &j);
				if(j != -1){
					listSucc[i]=inserer_queue_PList(listSucc[i],j );
				}
				else i++;
		}
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
	file = fopen("listeAdjTd.txt", "r");
	if (!file)
	{
		printf("le fichier n existe pas \n");
		exit(-1);
	}
	fscanf(file, "%d\n", n);
	 	printf(" n= %d\n",*n);
 
	fclose(file);
 
 
 }
 
 
 
 /*
void LireGraphePre(Cellule *listPre[MAX_ELEMS],int *n){
	 
 FILE* file = NULL;
	 int i,j ;

	file = fopen("listePre.txt", "r");
	if (!file)
	{
		printf("le fichier n existe pas \n");
		exit(-1);
	}
	fscanf(file, "%d\n", n);
	 

	i=0;
	while (!feof(file))
	{
		//for (i = 0; i < *n; i++)
	 	//
		 	printf(" i= %d\n",i);
			//	while (file!='\n')
			
		//	{
				 
				fscanf(file, "%d\t", &j);
				printf(" j= %d\n",j);
				if (j != -1)
				{
				listPre[i]=inserer_queue_PList(listPre[i],j );	
				}
				else i++;
			 
		//	
		 
		//}
	}
	fclose(file);
 
 }*/
int main() {
	
	int i,j,	//des indice pour parcourir les tableaux
		nbElm,//nombre de sommets
		nbCF;	//nombre de CF
Cellule *listSucc[MAX_ELEMS];// la liste X+
Cellule *CfList[MAX_ELEMS];// la liste X'
Cellule *listPre[MAX_ELEMS];// la liste X-
int marquerSuc[MAX_ELEMS];//si=1 element deja ajouter a la liste X+
int marquerPRE[MAX_ELEMS];//si=1 element deja ajouter a la liste X-
int marquer[MAX_ELEMS];//si=1 deja existe dans une CF 
int mat[MAX_ELEMS][MAX_ELEMS];//matrice reduite


//initialisation

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
LireGraphe(listSucc,listPre);
//LireGraphePre(listPre,&nbElm);


//exemple exercice td
 /*
 listSucc[0]=inserer_queue_PList(listSucc[0],1  );
 listSucc[0]=inserer_queue_PList(listSucc[0],2 );
 
 listSucc[1]=inserer_queue_PList(listSucc[1],8  );
 listSucc[1]=inserer_queue_PList(listSucc[1],4 );
  
 listSucc[2]=inserer_queue_PList(listSucc[2],10 );
 
 listSucc[3]=inserer_queue_PList(listSucc[3],0  );
 listSucc[3]=inserer_queue_PList(listSucc[3],  2);
 
  listSucc[4]=inserer_queue_PList(listSucc[4],6 );
  
 listSucc[5]=inserer_queue_PList(listSucc[5],  4);
 
  listSucc[6]=inserer_queue_PList(listSucc[6],  5);
 listSucc[6]=inserer_queue_PList(listSucc[6],  7);
 
  listSucc[7]=inserer_queue_PList(listSucc[7],  5);
  
   listSucc[8]=inserer_queue_PList(listSucc[8],  9);
   
    listSucc[9]=inserer_queue_PList(listSucc[9],2  );
    
 listSucc[10]=inserer_queue_PList(listSucc[10],3 );
  listSucc[10]=inserer_queue_PList(listSucc[10],11 );
  
   listSucc[11]=inserer_queue_PList(listSucc[11],12 );
   
    listSucc[12]=inserer_queue_PList(listSucc[12],13);
    
     listSucc[13]=inserer_queue_PList(listSucc[13],11);
 
  	////liste adj pred


 listPre[0]=inserer_queue_PList(listPre[0],3  );
 
 listPre[1]=inserer_queue_PList(listPre[1],0 );
 
  
 listPre[2]=inserer_queue_PList(listPre[2],0 );
  listPre[2]=inserer_queue_PList(listPre[2],9);
   listPre[2]=inserer_queue_PList(listPre[2],3 );
 
 listPre[3]=inserer_queue_PList(listPre[3],10  );
 
  listPre[4]=inserer_queue_PList(listPre[4],1  );
  listPre[4]=inserer_queue_PList(listPre[4],5 );
  
  listPre[5]=inserer_queue_PList(listPre[5],6 );
  listPre[5]=inserer_queue_PList(listPre[5],7 );
  
  listPre[6]=inserer_queue_PList(listPre[6],4 );
  
  listPre[7]=inserer_queue_PList(listPre[7],6 );
  
  listPre[8]=inserer_queue_PList(listPre[8],1);
  
  listPre[9]=inserer_queue_PList(listPre[9],8 );
  
  listPre[10]=inserer_queue_PList(listPre[10],2 );
  
  listPre[11]=inserer_queue_PList(listPre[11],10);
  
  listPre[11]=inserer_queue_PList(listPre[11],13);
  
  listPre[12]=inserer_queue_PList(listPre[12],11 );
  
  listPre[13]=inserer_queue_PList(listPre[13],12 );
  
 
   */
  
  nbCF=Cf(CfList,listSucc, listPre,marquerSuc, marquerPRE, marquer, nbElm);
  	printf("\n") ;
  //matrice reduite
  /*************************/
  //initialisation de la matrice
	for(i=0;i<nbCF;i++)
	{
		for(j=0;j<nbCF;j++)	mat[i][j]=0;
	}
	/**********************/
	printf(" la matrice reduite de ce graphe :\n\n") ;
  MatRed( mat,CfList,nbCF,listSucc);
  //affichage
  	for(i=0;i<nbCF;i++)
	{
		for(j=0;j<nbCF;j++)	printf("%d \t",mat[i][j]) ;
	 	printf("\n") ;
	}
return 1;
}//

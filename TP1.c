#include<stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Complexe{
    float re, im;
    struct Complexe* e;
}Complexe;
Complexe *AjoutTete(Complexe*, float, float);
void AfficherComplexes(Complexe *);
int LongueurListe(Complexe *);
Complexe *AjoutQueue(Complexe*, float, float);
void NormesComplexes(Complexe*);
Complexe SommeComplexes(Complexe *);
Complexe* supprissionFin(Complexe *);
Complexe* SuppressionDebut(Complexe *);
Complexe *AjoutTete(Complexe* liste, float P_Reel, float P_Im){
    Complexe *temp;
    temp = (Complexe*)malloc(sizeof(Complexe));
    temp->re = P_Reel;
    temp->im = P_Im;
    temp->e = liste;
    liste = temp;
    return liste;
}
void AfficherComplexes(Complexe *liste)
{
 Complexe *temp = liste;
 int i=1;
 while(temp != NULL)
 {
 if(temp->im == 0)
 {
 printf("Complexe%d : %.2f \n", i, temp->re);
 i++;
 }
 if(temp->re == 0)
 {
 printf("Complexe%d : %.2f*i \n", i, temp->im);
 i++;
 }
 if(!(temp->im == 0 || temp->re == 0))
 {
 printf("Complexe%d : %.2f + %.2f*i\n", i, temp->re, temp->im);
 i++;
 }
 temp = temp->e;
 }
}
int LongueurListe(Complexe *liste)
{
 int i=0;
 while(liste != NULL)
 {
 liste = liste->e;
 i++;
 }
 return i;
}
Complexe *AjoutQueue(Complexe* liste, float P_Reel, float P_Im)
{
 Complexe *temp, *p;
 temp = (Complexe*)malloc(sizeof(Complexe));
 temp->re = P_Reel;
 temp->im = P_Im;
 if(liste == NULL)
 {
 temp->e = liste;
 liste = temp;
 return liste;
 }
 else
 {
 p = liste;
 for(;p->e != NULL;)
 {
 p = p->e;
 }
 temp->e = NULL;
 p->e = temp;
 return liste;
 }
}
void NormesComplexes(Complexe *liste)
{
 Complexe *p = liste;
 int i=1;
 float Norme;
 while(p != NULL)
 {
 Norme = sqrt(pow(p->re,2)+pow(p->im,2));
 printf("norme%d = %.2f\n", i, Norme);
 i++;
 p=p->e;
 }
}
Complexe SommeComplexes(Complexe *liste)
{
 Complexe *p = liste;
 Complexe S;
 S.im = 0;
 S.re = 0;
 while(p != NULL)
 {
 S.im += p->im;
 S.re += p->re;
 p=p->e;
 }
 return S;
}

Complexe* suppressionDebut(Complexe *Liste)
{
    Complexe *p;
    if(Liste==NULL)
        return Liste;
    else
    {
        p=Liste;
        Liste = p->e;
        free(p);
        return Liste;
    }
}
Complexe* supprissionFin(Complexe* Liste)
{
    Complexe *prec,*actu;
    if (Liste==NULL)
    {
        return Liste;
    }
    else if(Liste->e == NULL)
    {
        suppressionDebut(Liste);
        return Liste;
    }
    else
    {
        actu = Liste;
        prec = Liste;
        while(actu->e!=NULL)
        {
            prec = actu;
            actu = actu->e;
        }
        free(actu);
        prec->e = NULL;
        return Liste;
    }
    
}

int main(void)
{
 Complexe *liste=NULL,t;
 float im,re;
 int i,n;
 printf("saisir le nombre d'entree:");scanf("%d",&n);
 for(i=0;i<n;i++){
 printf("saisir votre complexe:Re=");
 scanf("%f",&re);
 printf("Im=");
 scanf("%f",&im);
 liste=AjoutTete(liste, re, im);
 }
 printf("Affichage:\n");
 AfficherComplexes(liste);
 printf("la longueure:%d\n", LongueurListe(liste));
 printf("saisir votre complexe a ajouter en fin de liste:Re");
 scanf("%f",&re);
 printf("Im=");
 scanf("%f",&im);
 liste=AjoutQueue(liste, re, im);
 printf("Affichage:\n");
 AfficherComplexes(liste);
 printf("la nouvelle longueure:%d\n", LongueurListe(liste));
 NormesComplexes(liste);
 t= SommeComplexes(liste);
 printf("la somme est :%.2f+%.2f *i\n",t.re,t.im);
  liste= suppressionDebut(liste);
  printf("Affichage:\n");
 AfficherComplexes(liste);
 liste=  supprissionFin(liste);
  printf("Affichage:\n");
 AfficherComplexes(liste);
 return 0;
}
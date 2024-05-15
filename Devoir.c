
#include <stdio.h>
#include<stdlib.h>

typedef struct monome{
    int coef,exp;
    struct monome *sv;
}mn;
mn* CreerMonome(void);
mn* AjoutD(mn *);
mn* AjoutF(mn *);
mn* AjoutPos(mn *,int);
mn* AjoutTri(mn *);
void Affiche(mn *);
void Comp(mn *, mn *);
mn* SuppD(mn *);
mn* SuppF(mn *);
mn* SuppPos(mn *,int);
mn* SuppDeg(mn *,int);
void Check(mn* , mn*);
int Modiff(mn*,int, int);
mn* Derive(mn*);
mn* Produit(mn*,int);
mn* Somme(mn*,mn*);
int checkElement(int , int , mn*);



mn* CreerMonome(void){
    mn *monom;
    monom=(mn*)malloc(sizeof(mn));
    printf("saisir l'exposant:"); scanf("%d",&monom->exp);
    printf("saisir le coefficient:"); scanf("%d",&monom->coef);
    monom->sv=NULL;
    return monom;
}
mn* AjoutD(mn *poly){
    mn *monom;
    monom=CreerMonome();
    monom->sv=poly;
    poly=monom;
    return poly;
}
void Affiche(mn *liste){
    mn *p=liste;
    while(p->sv!=NULL){
        printf("%dX^%d+",p->coef,p->exp);
        p=p->sv;
    }
    if(p->sv==NULL) printf("%dX^%d\n",p->coef,p->exp);
}
mn* AjoutF(mn *poly){
    mn *monom, *p;
    monom=CreerMonome();
    p=poly;
    if(p==NULL){
        AjoutD(poly);
    }
    else {
        while(p->sv!=NULL){
        p=p->sv;
    }
        monom->sv=NULL;
        p->sv=monom;
            }
    return poly;
    }
mn* AjoutPos(mn *poly, int pos){
    mn *monom,*p;
    p=poly;
    int i=1;
    monom=CreerMonome();
    if(pos == 1) {
        poly=AjoutD(poly);
        return poly;
    }
    
    while(p!=NULL){
        if(pos-1==i){
            monom->sv=p->sv;
            p->sv=monom;
            return poly;
        }
        i++;
        p=p->sv;
    }
    if(p==NULL){
        puts("position invalide");
    }
    return poly;
}
mn* SuppD(mn *liste){
    mn *p=liste;
    if(liste !=NULL){
        liste=p->sv;
        free(p);
        return liste;
    }
    else return liste;
}
mn* SuppF(mn *liste){
    mn *sup,*p=liste;
    sup =liste;
    
    if(liste==NULL) return liste;
    else if(liste->sv ==NULL){
        liste=SuppD(liste);
        return liste;}
    else{
        while(p->sv !=NULL){
            sup=p;
            p=p->sv;
        }
        sup->sv=NULL;
        free(p);
        return liste;
    }
    return liste;
}
mn* SuppPos(mn *poly, int pos){
    mn *sup=poly,*p;
    p=poly;
    int i=1;
    if(pos == 1) {
        poly= SuppD(poly);
        return poly;
    }
    while(p!=NULL){
        i++;
        if(pos-1==i){
            sup=p->sv;
            p->sv=sup->sv;
            free(sup);
            return poly;
        }
        p=p->sv;
    }
    if(p==NULL){
        puts("position invalide");
    }
    return poly;
}
mn* SuppDeg(mn *liste,int deg){
    mn *sup=liste,*p;
    p=liste;
    while(p!=NULL && p->exp !=deg){
            sup=p;
            p=p->sv;
        }
    if( p->exp==deg){
        sup->sv=NULL;
        free(p);
        return liste;
    }
    if(p==NULL){
        puts("puissance invalide");
    }
    return liste;
}
int checkElement(int x, int y, mn* liste)
{
    mn *p = liste;
    int flag = 0, count=0;
    while (p != NULL)
    {
        if(x == p->coef && y == p->exp)
        {
            flag = 1;
            count++;
        }
        p = p->sv;
    }
    if(flag && count==1)
        return 1;
    else return 0;
}
void Comp(mn *liste1, mn *list2)
{
    mn *p=liste1 ,*P=list2;
    int i=0, j=0;
    while(p!=NULL)
    {
        if(checkElement(p->coef,p->exp,P))
            i++;
        p = p->sv;
        j++;
    }
    if(i==j)
    {
        printf("les deux polynomes sont egaux\n");
    }
    else
        printf("les deux polynomes sont inegaux\n");
}
void Check(mn *liste, mn *monome){
    mn *p=liste;
    if (liste==NULL) return;
    while(p!=NULL){
        if(p->exp== monome->exp && p->coef== monome->coef){
            printf("le monome appartient à ce polynome.");
            return;
        }
        p=p->sv;
    }
    printf("le monome n'appartient pas à ce polynome.");
    return;
}
int Modiff(mn* liste,int deg, int coeff){
    mn *p=liste;
    while(p!=NULL){
        if(p->exp == deg){
            p->coef = coeff;
            return 1;
        }
        p=p->sv;
    }
    return 0;
}
mn* Derive(mn *liste){
    mn *p=liste;
    while(p!=NULL){
        if(p->exp !=0 && p->exp !=1){
            p->coef= (p->coef )*(p->exp);
            (p->exp)--;
            printf("%dX^%d",p->coef,p->exp);
        }
        else{ 
            if(p->exp==1){
                p->exp=0;
                printf("%d",p->coef);
            }
            if(p->exp ==0){
                p->coef=0;
                printf(" ");
            }
        }
        p=p->sv;
        printf("+");
    }
    return liste;
}
mn* Produit(mn* liste,int prd){
    mn *p=liste;
    while(p!=NULL){
        (p->coef)*= prd;
        p=p->sv;
    }
    return liste;
}
mn* Somme(mn* liste1, mn* liste2) {
    mn* p1 = liste1;
    mn* p2 = liste2;
    mn* somme = NULL;
    mn* tmp = NULL;

    while (p1 != NULL || p2 != NULL) {
        mn* nouveau_monome = (mn*)malloc(sizeof(mn));
        if (nouveau_monome == NULL) {
            printf("Erreur: Échec de l'allocation de mémoire.\n");
            exit(1);
        }
        if (p1 == NULL) {
            nouveau_monome->coef = p2->coef;
            nouveau_monome->exp = p2->exp;
            p2 = p2->sv;
        } else if (p2 == NULL) {
            nouveau_monome->coef = p1->coef;
            nouveau_monome->exp = p1->exp;
            p1 = p1->sv;
        } else if (p1->exp > p2->exp) {
            nouveau_monome->coef = p1->coef;
            nouveau_monome->exp = p1->exp;
            p1 = p1->sv;
        } else if (p1->exp < p2->exp) {
            nouveau_monome->coef = p2->coef;
            nouveau_monome->exp = p2->exp;
            p2 = p2->sv;
        } else {
            nouveau_monome->coef = p1->coef + p2->coef;
            nouveau_monome->exp = p1->exp;
            p1 = p1->sv;
            p2 = p2->sv;
        }
        nouveau_monome->sv = NULL;
        if (somme == NULL) {
            somme = nouveau_monome;
            tmp = somme;
        } else {
            tmp->sv = nouveau_monome;
            tmp = tmp->sv;
        }
    }
    return somme;
}

 
int main(int argc, const char * argv[]) {
    mn *poly=NULL , *polynome=NULL, *mon;
    int size;
    int pos,deg,coef;
    poly=AjoutD(poly);
    Affiche(poly);
    poly=AjoutF(poly);
    Affiche(poly);
    printf("saisir la position:");scanf("%d",&pos);
    poly=AjoutPos(poly,pos);
    printf("AFFICHAGE\n");
    Affiche(poly);
    printf("entrer size: ");
    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        polynome=AjoutF(polynome);
    }
    printf("AFFICHAGE\n");
    Affiche(polynome);
    Comp(poly,polynome);
    poly=SuppD(poly);
    printf("AFFICHAGE\n");
    Affiche(poly);
    poly=SuppF(poly);
    Affiche(poly);
    printf("saisir la position:");scanf("%d",&pos);
    polynome=SuppPos(polynome,pos);
    printf("AFFICHAGE\n");
    Affiche(polynome);
    printf("saisir le degre:");scanf("%d",&deg);
    polynome=SuppDeg(polynome,deg);
    mon=CreerMonome();
    Check(polynome ,mon);
    printf("saisir le degre et le coefficient:");scanf("%d %d",&deg,&coef);
    Modiff(polynome,deg, coef);
    polynome=Derive(polynome);
    printf("saisir le scalaire:");scanf("%d",&deg);
    polynome=Produit(polynome,deg);
    int i = 0;
    mn *pol1 = NULL, *pol2 = NULL, *s;
    printf("Saisie du premier polynome:\n");
    for (i = 0; i < 2; i++) {
        pol1 = AjoutD(pol1);
    }
    printf("Saisie du deuxieme polynome:\n");
    for (i = 0; i < 2; i++) {
        pol2 = AjoutD(pol2);
    }
    s = Somme(pol1, pol2);
    printf("Somme: ");
    Affiche(s);
    mn *temp;
    while (s != NULL) {
        temp = s;
        s = s->sv;
        free(temp);
    }
    while (pol1 != NULL) {
        temp = pol1;
        pol1 = pol1->sv;
        free(temp);
    }
    while (pol2 != NULL) {
        temp = pol2;
        pol2 = pol2->sv;
        free(temp);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int day, month, year;
}Date;

typedef struct Wagon_1{
    int id;
    int capacity;
    int class;
    Date date;
    struct Wagon_1 *next;
}Wagon;

/*************************************functions prototype*******************************************/
Wagon *AjoutTete(Wagon* , Wagon);
Wagon *AjoutQueue(Wagon*,Wagon);
Wagon *AjoutPosition(Wagon*, Wagon, int);
Wagon *AjoutPositionId(Wagon*, Wagon, int);
void SuppTete(Wagon*);
void SuppFin(Wagon*);
void SuppPosition(Wagon*, int);
int *AffichWagonList(Wagon*, int *);
int AffichWagonListclasse2(Wagon*);
int AffichWagonListclasse1(Wagon*);
int *AffichWagoncapacity(Wagon*, int*);
Wagon* CreerWagon();

/*************************************functions definition*******************************************/
Wagon* CreerWagon(){
    Wagon *new = (Wagon*)malloc(sizeof(Wagon));
    printf("entrer ID:");
    scanf("%d", &new->id);
    printf("\nentrez la capacite: ");
    scanf("%d",&new->capacity) ;
    printf("\nEntrez la classe (1-premier ou 2-executif): ");
    scanf("%d",&new->class);
    printf("\nEntrer Jour/mois/anne: ");
    scanf("%d%d%d",&new->date.day,&new->date.month,&new->date.year);
}
/***************functions of Adding***************/

Wagon *AjoutTete(Wagon* Train, Wagon new){
    Wagon *temp;
    temp = (Wagon*)malloc(sizeof(Wagon));
    (*temp) = new;
    temp->next = Train;
    Train = temp;
    return Train;
}
Wagon *AjoutQueue(Wagon* Train, Wagon new)
{
    Wagon *temp, *p;
    temp = (Wagon*)malloc(sizeof(Wagon));
    (*temp) = new;
    if(Train == NULL)
    {
        temp->next = Train;
        Train = temp;
        return Train;
    }
    else
    {
        p = Train;
        for(;p->next != NULL;)
        {
            p = p->next;
        }
        temp->next = NULL;
        p->next = temp;
        return Train;
    }
}
Wagon *AjoutPosition(Wagon* Train, Wagon new, int pos)
{
    Wagon *temp, *p;
    int i=0;
    temp = (Wagon*)malloc(sizeof(Wagon));
    (*temp) = new;
    if(Train == NULL)
    {
        printf("\nle Train est vide.\n");
        return Train;
    }
    else
    {
        p = Train;
        for(;p->next != NULL;)
        {
            if(i==pos-1)
                break;
            i++;
            p = p->next;
        }
        if(i<pos-1)
        {
            printf("on a pas cette position.");
            return Train;
        }
        temp->next = p->next;
        p->next = temp;
        return Train;
    }
}
Wagon *AjoutPositionId(Wagon* Train, Wagon new, int id)
{
    Wagon *temp, *p;
    int flag = 0;
    temp = (Wagon*)malloc(sizeof(Wagon));
    (*temp) = new;
    if(Train == NULL)
    {
        printf("\nle Train est vide.\n");
        return Train;
    }
    else
    {
        p = Train;
        for(;p->next != NULL;)
        {
            if((p->id)==id)
                break;
            p = p->next;
            if(p->next == NULL)
                flag = 1;
        }
        p=p->next;
        if(flag)
        {
            printf("on a pas cette position.");
            return Train;
        }
        temp->next = p->next;
        p->next = temp; //test par rapport a pos = 1 donc pos-1 = 0
        return Train;
    }
}

/***************functions of Deleting***************/
void SuppTete(Wagon* Train)
{
    Wagon *tete;
    if(Train == NULL)
    {
        printf("vide");
    }
    else{
        tete = Train;
        Train = tete->next;
        free(tete);
    }
}
void SuppFin(Wagon* Train)
{
    Wagon *fin, *prec;
    prec = Train;
    fin = prec->next;
    while(fin->next !=NULL)
    {
        prec = prec->next;
        fin = fin->next;
    }
    fin->next = NULL;
    free(fin);
}
void SuppPosition(Wagon* Train, int position)
{
    Wagon *Prec, *P;
    int flag=0, i=0;
    if(Train!=NULL)
    {
        if(position-1 == 0)
            return SuppTete(Train);
        else
        {
            Prec = Train;
            P = Train->next;
            while(P!= NULL && !flag)
            {
                if(position-1==i)
                {
                    flag = 1;
                }
                else
                {
                    Prec = P;
                    P = P->next;
                }
            }
            if(flag)
            {
                Prec->next = P->next;
                free(P);
            }
            else
                printf("%d n est pas dans la liste.", position);
        }
    }
    else
        printf("vide");
}

/***************functions of Displaying***************/
int *AffichWagonList(Wagon* Train, int *i)
{
    Wagon *temp;
    temp = Train;
    while(temp !=NULL)
    {
        printf("Wagon-%d: Id %d || Capacity %d || Classe %d || Date %d/%d/%d.", 
        *i+1, temp->id, temp->capacity, temp->class, temp->date.day, temp->date.month, temp->date.year);
        temp = temp->next;
        (*i)++;
    }
    return i;
}
int *AffichWagoncapacity(Wagon* Train, int *i)
{
    Wagon *temp;
    temp = Train;
    while(temp !=NULL)
    {
        temp = temp->next;
        (*i)+=temp->capacity;
    }
    return i;
}
int AffichWagonListclasse1(Wagon* Train)
{
    Wagon *temp;
    temp = Train;
    int i=0;
    while(temp !=NULL)
    {
        if(temp->class == 1)
        {
            i += temp->capacity;
        }
        temp = temp->next;
    }
    return i;
}
int AffichWagonListclasse2(Wagon* Train)
{
    Wagon *temp;
    temp = Train;
    int i=0;
    while(temp !=NULL)
    {
        if(temp->class == 2)
        {
            i += temp->capacity;
        }
        temp = temp->next;
    }
    return i;
}

/***************Main Function***************/
int main()
{
    Wagon *W1=NULL, *W2=NULL;
    Wagon w;
    int choice;
    printf("entrer ID:");
    scanf("%d", &w.id);
    printf("\nentrez la capacite: ");
    scanf("%d",&w.capacity) ;
    printf("\nEntrez la classe (1-premier ou 2-executif): ");
    scanf("%d",&w.class);
    printf("\nEntrer Jour/mois/anne: ");
    scanf("%d%d%d",&w.date.day,&w.date.month,&w.date.year);
    printf("1- wagon 1, 2- wagon 2");
    printf("\n\nVoulez");
    switch (choice)
    {
    case 1:
        W1=AjoutTete(W1,w);
        break;
    case 2:
        W2=AjoutQueue(W2,w);
        break;
    default:
        break;
    }
    int i=0, j=0;
    printf("train capacity %d", AffichWagoncapacity(W1, &i));
    printf("train capacity %d", AffichWagoncapacity(W2, &j));
    printf("les places de 1er classe: ");
    printf("pour wagon 1: %d", AffichWagonListclasse1(W1));
    printf("pour wagon 2: %d", AffichWagonListclasse1(W2));
    printf("les places de 2eme classe: ");
    printf("pour wagon 1: %d", AffichWagonListclasse2(W1));
    printf("pour wagon 2: %d", AffichWagonListclasse2(W2));
    i=0;
    int *s1 = AffichWagonList(W1, &i);
    printf("nombre wagon dans 1: %d", *s1);
    int *s2 = AffichWagonList(W2, &i);
    printf("nombre wagon dans 2: %d", *s2);
    
}
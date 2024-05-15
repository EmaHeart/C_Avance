#include <stdio.h>
#include <stdlib.h>

/****************structure recursive****************/
typedef struct Patient{
    char Nom[15];
    char Prenom[15];
    int rdv;
    /*rendezvous vaut: 1: si patient a un rdv
    0 : sinon */
    struct Patient *next; // de la structure recursive
}Patient;

/****************prototype functions******************/
Patient *InitialiserLaLSC_C();
Patient *CreerPatient();
Patient *AjoutPatientT(Patient*, Patient *);
Patient *AjoutPatientQ(Patient*, Patient *);
Patient *AjoutPatientPos(Patient*, Patient *, int);
Patient *SuppressionPatientT(Patient*);
Patient *SuppressionPatientQ(Patient*);
Patient *SuppressionPatientPos(Patient*, int);


/*******************functions definition******************/

//Function de Ajout
Patient *InitialiserLaLSC_C()
{
    Patient *Liste;
    Liste = (Patient*)malloc(sizeof(Patient));
    Liste->next = Liste;
    return  Liste;
}

Patient *CreerPatient()
{
    Patient *NouvPatient;
    NouvPatient = (Patient *) malloc(sizeof(Patient));
    printf("Entrez le nom du patient:\n");
    scanf("%s",NouvPatient->Nom);
    printf("Entrez le prenom du patient:\n");
    scanf(" %s",NouvPatient->Prenom);
    printf("patient a un rdv:(si oui : 1 sinon : 0)");
    do
    {
        scanf("%d", &NouvPatient->rdv);
    } while (NouvPatient->rdv !=0 || NouvPatient->rdv !=1);
    return  NouvPatient;
}

Patient *AjoutPatientT(Patient* tete, Patient *P)
{
    P->next = tete->next;
    tete->next=P;
    return tete;
}

Patient *AjoutPatientQ(Patient* tete, Patient *P)
{
    if(tete->next == tete)
        return AjoutPatientT(tete,P);
    Patient *tmp = tete;
    while (tmp->next != tmp)
    {
        tmp = tmp->next;
    }
    P->next = tete;
    tmp->next = P;
    return tete;
}


Patient *AjoutPatientPos(Patient* tete, Patient *P, int position)
{
    if(position ==1)
        return AjoutPatientT(tete, P);
    Patient *tmp = tete;
    int i=0;
    while (tmp->next != tmp)
    {
        if(i==position-1)
        {
            P->next = tmp->next;
            tmp->next = P;
            return tete;
        }
        i++;
        tmp = tmp->next;
    }
    if(position-1 > i)
    {
        printf("INVALID POSITION");
        return tete;
    }
}

//Function de Supp
Patient *SuppressionPatientT(Patient* tete)
{
    if(tete->next == tete)
        return tete;
    Patient *p = tete;
    tete->next = p->next;
    free(p);
    return tete;
}

/*Patient *SuppressionPatientQ(Patient* tete)
{
    Patient *p, *p1;
    if(tete->next == tete)
        return tete;
    
}
*/
int main()
{

    return 0;
}
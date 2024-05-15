#include <stdio.h>
#include <stdlib.h>

typedef struct monome {
    int coef, exp;
    struct monome *sv;
} mn;

mn* Somme(mn*, mn*);
mn* CreerMonome(void);
mn* AjoutD(mn*);
void AfficherPolynome(mn*);

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

mn* CreerMonome(void) {
    mn *monom = (mn*)malloc(sizeof(mn));
    if (monom == NULL) {
        printf("Erreur: Échec de l'allocation de mémoire.\n");
        exit(1);
    }
    printf("Saisir l'exposant: ");
    scanf("%d", &monom->exp);
    printf("Saisir le coefficient: ");
    scanf("%d", &monom->coef);
    monom->sv = NULL;
    return monom;
}

mn* AjoutD(mn *poly) {
    mn *monom = CreerMonome();
    monom->sv = poly;
    return monom;
}

void AfficherPolynome(mn* poly) {
    mn* p = poly;
    while (p != NULL) {
        printf("%dx^%d ", p->coef, p->exp);
        p = p->sv;
        if (p != NULL)
            printf("+ ");
    }
    printf("\n");
}

int main() {
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
    AfficherPolynome(s);

    // Libération de la mémoire allouée
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

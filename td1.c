/*
 * TD1 : Les Structures
 * Exercice 1 : Point
 * Exercice 2 : Heure
 * Filières : IISD & IDRS - Semestre 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TMAX 20

/* =====================================================
 * EXERCICE 1 : Structure Point
 * ===================================================== */

typedef struct {
    int abs;
    int ord;
} Point;

/* Saisir un point */
Point SaisirPoint() {
    Point p;
    printf("Donner les coordonnees du point (x y) : ");
    scanf("%d %d", &p.abs, &p.ord);
    return p;
}

/* Afficher un point sous format (x,y) */
void AfficherPoint(Point p) {
    printf("(%d, %d)\n", p.abs, p.ord);
}

/* Distance par valeur */
float DistanceParValeur(Point p) {
    return sqrt((float)(p.abs * p.abs + p.ord * p.ord));
}

/* Distance par adresse */
float DistanceParAdresse(Point *p) {
    return sqrt((float)(p->abs * p->abs + p->ord * p->ord));
}

/* Tri par ordre croissant des distances (selection sort) */
void TrierParDistance(Point t[], int taille) {
    int i, j;
    Point aux;
    for (i = 0; i < taille - 1; i++) {
        for (j = i + 1; j < taille; j++) {
            if (DistanceParValeur(t[i]) > DistanceParValeur(t[j])) {
                aux  = t[i];
                t[i] = t[j];
                t[j] = aux;
            }
        }
    }
}

/* =====================================================
 * EXERCICE 2 : Structure Heure (hh/mm/ss)
 * ===================================================== */

typedef struct {
    int hh;
    int mm;
    int ss;
} Heure;

/* Heure → secondes */
int HeureEnSecondes(Heure h) {
    return h.hh * 3600 + h.mm * 60 + h.ss;
}

/* Secondes → Heure */
Heure SecondesEnHeure(int sec) {
    Heure h;
    h.hh = sec / 3600;
    sec  = sec % 3600;
    h.mm = sec / 60;
    sec  = sec % 60;
    h.ss = sec;
    return h;
}

/* Addition de deux heures */
Heure AddHeures(Heure h1, Heure h2) {
    return SecondesEnHeure(HeureEnSecondes(h1) + HeureEnSecondes(h2));
}

/* Différence entre deux heures (|h1 - h2|) */
Heure DiffHeures(Heure h1, Heure h2) {
    int diff = abs(HeureEnSecondes(h1) - HeureEnSecondes(h2));
    return SecondesEnHeure(diff);
}

/* Afficher une heure */
void AfficherHeure(Heure h) {
    printf("%02d:%02d:%02d\n", h.hh, h.mm, h.ss);
}

/* =====================================================
 * PROGRAMME PRINCIPAL
 * ===================================================== */

int main() {
    printf("=== TD1 - Exercice 1 : Points ===\n\n");

    /* --- Tableau statique --- */
    Point TStat[TMAX];
    int taille, i;

    srand((unsigned int)time(NULL));

    printf("Donner la taille du tableau (<= %d) : ", TMAX);
    scanf("%d", &taille);
    if (taille > TMAX) taille = TMAX;

    /* Remplissage aléatoire */
    for (i = 0; i < taille; i++) {
        TStat[i].abs = rand() % 100;
        TStat[i].ord = rand() % 100;
    }

    printf("\nPoints avant tri :\n");
    for (i = 0; i < taille; i++) AfficherPoint(TStat[i]);

    TrierParDistance(TStat, taille);

    printf("\nPoints apres tri par distance croissante :\n");
    for (i = 0; i < taille; i++) {
        AfficherPoint(TStat[i]);
        printf("  -> distance = %.2f\n", DistanceParValeur(TStat[i]));
    }

    /* --- Tableau dynamique --- */
    printf("\n--- Tableau dynamique ---\n");
    int tailleD;
    printf("Donner la taille du tableau dynamique : ");
    scanf("%d", &tailleD);

    Point *TDyn = (Point *)malloc(tailleD * sizeof(Point));
    if (!TDyn) { printf("Erreur malloc\n"); return 1; }

    for (i = 0; i < tailleD; i++) {
        TDyn[i].abs = rand() % 100;
        TDyn[i].ord = rand() % 100;
    }
    printf("Points dynamiques avant tri :\n");
    for (i = 0; i < tailleD; i++) AfficherPoint(TDyn[i]);

    TrierParDistance(TDyn, tailleD);
    printf("Points dynamiques apres tri :\n");
    for (i = 0; i < tailleD; i++) AfficherPoint(TDyn[i]);

    free(TDyn);

    /* --- Distance par valeur et par adresse --- */
    printf("\nTest distance (par valeur et par adresse) :\n");
    Point p = {3, 4};
    printf("Point "); AfficherPoint(p);
    printf("Distance (par valeur)  = %.2f\n", DistanceParValeur(p));
    printf("Distance (par adresse) = %.2f\n", DistanceParAdresse(&p));

    /* ---- Exercice 2 : Heures ---- */
    printf("\n=== TD1 - Exercice 2 : Heures ===\n\n");

    Heure h1 = {1, 30, 45};
    Heure h2 = {0, 45, 20};

    printf("Heure 1 : "); AfficherHeure(h1);
    printf("Heure 2 : "); AfficherHeure(h2);
    printf("H1 en secondes : %d\n", HeureEnSecondes(h1));
    printf("H2 en secondes : %d\n", HeureEnSecondes(h2));

    Heure somme = AddHeures(h1, h2);
    printf("H1 + H2 = "); AfficherHeure(somme);

    Heure diff = DiffHeures(h1, h2);
    printf("H1 - H2 = "); AfficherHeure(diff);

    return 0;
}

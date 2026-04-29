/*
 * TD2 : Complexité & Récursivité
 * Exercice 1 : Indice du minimum
 * Exercice 2 : MiniMax matrice
 * Exercice 3 : Puissance récursive + rapide + somme
 * Exercice 4 : rec1 et rec2
 * Filières : IISD & IDRS - Semestre 2
 */

#include <stdio.h>
#include <stdlib.h>

/* =====================================================
 * EXERCICE 1 : Indice de la première occurrence du minimum
 * Complexité : O(n)
 * ===================================================== */

int indiceMin(int tab[], int N) {
    int i, index = 0;
    for (i = 1; i < N; i++) {
        if (tab[i] < tab[index])
            index = i;
    }
    return index;
}

/* =====================================================
 * EXERCICE 2 : MiniMax d'une matrice n x m
 * Complexité : O(n*m)
 * ===================================================== */

int MiniMax(int tab[][10], int n, int m) {
    int i, j;
    int max, minimax;

    for (i = 0; i < n; i++) {
        max = tab[i][0];
        for (j = 1; j < m; j++) {
            if (tab[i][j] > max)
                max = tab[i][j];
        }
        if (i == 0)
            minimax = max;
        else if (minimax > max)
            minimax = max;
    }
    return minimax;
}

/* =====================================================
 * EXERCICE 3 : Puissance récursive simple
 * Complexité : O(n)
 * ===================================================== */

int puissance(int a, int i) {
    if (i == 0) return 1;
    return a * puissance(a, i - 1);
}

/* Exponentiation rapide
 * Complexité : O(log n)
 */
int expRapide(int a, int i) {
    if (i == 0) return 1;
    if (i % 2 == 0) {
        int demi = expRapide(a, i / 2);
        return demi * demi;
    } else {
        int demi = expRapide(a, i / 2);
        return a * demi * demi;
    }
}

/* Somme : S(a,n) = a^0 + a^1 + ... + a^n
 * Complexité : O(n^2) car appel à puissance(O(n)) pour chaque terme
 */
int somme(int a, int n) {
    if (n == 0) return 1;
    return puissance(a, n) + somme(a, n - 1);
}

/* =====================================================
 * EXERCICE 4 : rec1 et rec2 — calculent toutes deux 2^n
 *
 * rec1 : complexité O(n)   — linéaire (arbre de récursion linéaire)
 * rec2 : complexité O(2^n) — exponentielle (arbre binaire complet)
 * ===================================================== */

int rec1(int n) {
    if (n == 0) return 1;
    return 2 * rec1(n - 1);
}

int rec2(int n) {
    if (n == 0) return 1;
    return rec2(n - 1) + rec2(n - 1);
}

/* =====================================================
 * PROGRAMME PRINCIPAL
 * ===================================================== */

int main() {
    int i;

    /* --- Exercice 1 --- */
    printf("=== TD2 - Exercice 1 : Indice du minimum ===\n");
    int tab[] = {5, 2, 4, 2, 1, 7, 9, 4, 1, 1};
    int N = sizeof(tab) / sizeof(tab[0]);

    printf("Tableau : ");
    for (i = 0; i < N; i++) printf("%d ", tab[i]);
    printf("\n");
    printf("Indice de la 1ere occurrence du min : %d\n", indiceMin(tab, N));
    printf("(Complexite : O(n))\n\n");

    /* --- Exercice 2 --- */
    printf("=== TD2 - Exercice 2 : MiniMax ===\n");
    int matrice[3][10] = {
        {2, 3, 4, 0, 0, 0, 0, 0, 0, 0},
        {5, 1, 7, 0, 0, 0, 0, 0, 0, 0},
        {8, 9, 6, 0, 0, 0, 0, 0, 0, 0}
    };
    printf("Matrice 3x3 :\n");
    int r, c;
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) printf("%d ", matrice[r][c]);
        printf("\n");
    }
    printf("MiniMax = %d\n", MiniMax(matrice, 3, 3));
    printf("(Complexite : O(n*m))\n\n");

    /* --- Exercice 3 --- */
    printf("=== TD2 - Exercice 3 : Puissance ===\n");
    printf("puissance(2, 10) = %d  [O(n)]\n",  puissance(2, 10));
    printf("expRapide(2, 10) = %d  [O(log n)]\n", expRapide(2, 10));
    printf("somme(2, 5)      = %d  [O(n^2)]  (1+2+4+8+16+32=63)\n", somme(2, 5));

    /* --- Exercice 4 --- */
    printf("\n=== TD2 - Exercice 4 : rec1 et rec2 ===\n");
    printf("rec1(8) = %d  [calcule 2^n, complexite O(n)]\n",   rec1(8));
    printf("rec2(8) = %d  [calcule 2^n, complexite O(2^n)]\n", rec2(8));
    printf("\nComparaison :\n");
    printf("  rec1 : arbre lineaire -> n multiplications\n");
    printf("  rec2 : arbre binaire  -> 2^n - 1 additions (tres couteux !)\n");

    return 0;
}

/*
 * TD4 : Arbres Binaires de Recherche (ABR)
 * Exercice 1 : Insertion, Recherche, Occurrences, Parcours, Liste triée, Tri
 * Exercice 2 : Tester si un arbre est un ABR
 * Exercice 3 : Plus petit élément
 * Filières : IISD & IDRS - Semestre 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =====================================================
 * STRUCTURE ABR
 * ===================================================== */

typedef int ElementType;

typedef struct TreeNode {
    ElementType element;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef TreeNode *SEARCH_TREE;

/* =====================================================
 * LISTE (réutilisée depuis TD3)
 * ===================================================== */

typedef struct Elem {
    int val;
    struct Elem *suivant;
} LISTE;

int InsererEnFin(LISTE **L, int valeur) {
    LISTE *e = (LISTE *)malloc(sizeof(LISTE));
    if (!e) return 0;
    e->val = valeur; e->suivant = NULL;
    if (!*L) { *L = e; return 1; }
    LISTE *p = *L;
    while (p->suivant) p = p->suivant;
    p->suivant = e;
    return 1;
}

void AfficherListe(LISTE *L) {
    printf("[ ");
    while (L) { printf("%d ", L->val); L = L->suivant; }
    printf("]\n");
}

int InsererEnTete(LISTE **L, int valeur) {
    LISTE *e = (LISTE *)malloc(sizeof(LISTE));
    if (!e) return 0;
    e->val = valeur; e->suivant = *L; *L = e;
    return 1;
}

/* =====================================================
 * EXERCICE 1.1 : Insérer une valeur dans un ABR
 * Complexité : O(h) où h = hauteur de l'arbre
 *              O(log n) en moyenne, O(n) au pire
 * ===================================================== */

SEARCH_TREE Inserer(ElementType x, SEARCH_TREE T) {
    if (T == NULL) {
        T = (SEARCH_TREE)malloc(sizeof(TreeNode));
        if (!T) { printf("Espace memoire insuffisant!\n"); exit(0); }
        T->element = x;
        T->left = T->right = NULL;
    } else if (x <= T->element) {
        T->left  = Inserer(x, T->left);
    } else {
        T->right = Inserer(x, T->right);
    }
    return T;
}

/* =====================================================
 * EXERCICE 1.2 : Chercher si une valeur appartient à l'ABR
 * Complexité : O(h)
 * ===================================================== */

TreeNode *Rechercher(SEARCH_TREE T, ElementType e) {
    if (!T)              return NULL;
    if (e == T->element) return T;
    if (e > T->element)  return Rechercher(T->right, e);
    return                      Rechercher(T->left,  e);
}

/* =====================================================
 * EXERCICE 1.3 : Compter les occurrences de X dans l'ABR
 * Complexité : O(n) (parcours complet car doublons des deux côtés)
 * ===================================================== */

void NombreOccurrences(SEARCH_TREE A, ElementType e, int *nombre) {
    if (A) {
        NombreOccurrences(A->left,  e, nombre);
        if (A->element == e) (*nombre)++;
        NombreOccurrences(A->right, e, nombre);
    }
}

/* =====================================================
 * EXERCICE 1.4 : Parcours infixé (affiche les clés triées)
 * Complexité : O(n)
 * ===================================================== */

void ParcoursInfixe(SEARCH_TREE T) {
    if (T) {
        ParcoursInfixe(T->left);
        printf("%d ", T->element);
        ParcoursInfixe(T->right);
    }
}

/* Parcours préfixé (pour affichage de la structure) */
void ParcoursPrefixe(SEARCH_TREE T) {
    if (T) {
        printf("%d ", T->element);
        ParcoursPrefixe(T->left);
        ParcoursPrefixe(T->right);
    }
}

/* =====================================================
 * EXERCICE 1.5 : Construire une liste triée depuis un ABR
 * Complexité : O(n)
 * ===================================================== */

void ConstListeTriee(SEARCH_TREE A, LISTE **L) {
    if (A) {
        ConstListeTriee(A->left, L);
        InsererEnFin(L, A->element);
        ConstListeTriee(A->right, L);
    }
}

/* =====================================================
 * EXERCICE 1.6 : Construire un ABR depuis une liste
 * Complexité : O(n log n) en moyenne
 * ===================================================== */

SEARCH_TREE ArbreDepuisListe(LISTE *L) {
    SEARCH_TREE A = NULL;
    while (L) {
        A = Inserer(L->val, A);
        L = L->suivant;
    }
    return A;
}

/* =====================================================
 * EXERCICE 1.7 : Tri d'une liste via un ABR (Tree Sort)
 * Complexité : O(n log n) en moyenne
 * ===================================================== */

LISTE *TrierListe(LISTE *L) {
    SEARCH_TREE A   = ArbreDepuisListe(L);
    LISTE      *tri = NULL;
    ConstListeTriee(A, &tri);
    return tri;
}

/* =====================================================
 * EXERCICE 2 : Tester si un arbre binaire est un ABR
 * Méthode : parcours infixé → la liste résultante doit être triée
 * Complexité : O(n)
 * ===================================================== */

int EstABR(SEARCH_TREE A) {
    if (!A) return 0;
    if (!A->left && !A->right) return 1;

    LISTE *L = NULL;
    ConstListeTriee(A, &L);

    while (L && L->suivant) {
        if (L->val > L->suivant->val) return 0;
        L = L->suivant;
    }
    return 1;
}

/* =====================================================
 * EXERCICE 3 : Plus petit élément d'un ABR
 * Le minimum est le nœud le plus à gauche
 * Complexité : O(h)
 * ===================================================== */

ElementType LePlusPetit(SEARCH_TREE A) {
    if (!A) { printf("Arbre vide!\n"); exit(1); }
    while (A->left) A = A->left;
    return A->element;
}

/* =====================================================
 * PROGRAMME PRINCIPAL
 * ===================================================== */

int main() {
    SEARCH_TREE A = NULL;
    int i, nbre;

    srand((unsigned int)time(NULL));

    printf("=== TD4 - Arbres Binaires de Recherche ===\n\n");

    /* Créer un ABR avec 10 entiers aléatoires */
    printf("--- Creation ABR avec 10 entiers aleatoires ---\n");
    for (i = 0; i < 10; i++)
        A = Inserer(rand() % 20, A);

    printf("Parcours infixe  (croissant) : ");
    ParcoursInfixe(A); printf("\n");
    printf("Parcours prefixe (structure) : ");
    ParcoursPrefixe(A); printf("\n\n");

    /* Recherche */
    printf("--- Recherche ---\n");
    int cherche = 10;
    TreeNode *res = Rechercher(A, cherche);
    if (res)
        printf("Valeur %d trouvee dans l'arbre.\n", cherche);
    else
        printf("Valeur %d NON trouvee dans l'arbre.\n", cherche);

    /* Occurrences */
    nbre = 0;
    NombreOccurrences(A, cherche, &nbre);
    printf("Nombre d'occurrences de %d : %d\n\n", cherche, nbre);

    /* Liste triée depuis ABR */
    printf("--- Liste triee depuis ABR ---\n");
    LISTE *LT = NULL;
    ConstListeTriee(A, &LT);
    printf("Liste triee : ");
    AfficherListe(LT);

    /* Créer liste non triée et la trier via ABR */
    printf("\n--- Tri d'une liste via ABR (Tree Sort) ---\n");
    LISTE *L = NULL;
    for (i = 0; i < 10; i++) InsererEnTete(&L, rand() % 100);
    printf("Avant tri : "); AfficherListe(L);
    LISTE *Ltri = TrierListe(L);
    printf("Apres tri : "); AfficherListe(Ltri);

    /* Exercice 2 : Est-ce un ABR ? */
    printf("\n--- Exercice 2 : Test ABR ---\n");
    printf("L'arbre A est-il un ABR ? %s\n", EstABR(A) ? "OUI" : "NON");

    /* Arbre non-ABR (construit manuellement) */
    SEARCH_TREE fakeABR = (SEARCH_TREE)malloc(sizeof(TreeNode));
    fakeABR->element = 5;
    fakeABR->left    = (SEARCH_TREE)malloc(sizeof(TreeNode));
    fakeABR->right   = (SEARCH_TREE)malloc(sizeof(TreeNode));
    fakeABR->left->element  = 10; /* violation! */
    fakeABR->right->element = 3;  /* violation! */
    fakeABR->left->left = fakeABR->left->right = NULL;
    fakeABR->right->left = fakeABR->right->right = NULL;
    printf("L'arbre non-conforme est-il un ABR ? %s\n", EstABR(fakeABR) ? "OUI" : "NON");

    /* Exercice 3 : Plus petit élément */
    printf("\n--- Exercice 3 : Plus petit element ---\n");
    printf("Le plus petit element de A : %d\n", LePlusPetit(A));

    return 0;
}

/*
 * TD3 : Listes, Piles, Files
 * Exercice 1 : Création d'une liste
 * Exercice 2 : Recherche de valeur
 * Exercice 3 : Suppression de l'élément minimal
 * Exercice 4 : Fusion de deux listes
 * Exercice 5 : Destruction d'une liste
 * Exercice 6 : Piles (PairImpair)
 * Exercice 7 : Files (Palindrome)
 * Filières : IISD & IDRS - Semestre 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* =====================================================
 * LISTE CHAÎNÉE
 * ===================================================== */

typedef struct Element {
    int val;
    struct Element *suivant;
} LISTE;

/* Insérer en tête — O(1) */
int InsererEnTete(LISTE **L, int valeur) {
    LISTE *elem = (LISTE *)malloc(sizeof(LISTE));
    if (!elem) { printf("Erreur malloc\n"); return 0; }
    elem->val     = valeur;
    elem->suivant = *L;
    *L = elem;
    return 1;
}

/* Insérer en fin — O(n) */
int InsererEnFin(LISTE **L, int valeur) {
    LISTE *elem = (LISTE *)malloc(sizeof(LISTE));
    if (!elem) { printf("Erreur malloc\n"); return 0; }
    elem->val     = valeur;
    elem->suivant = NULL;

    if (*L == NULL) { *L = elem; return 1; }

    LISTE *ptr = *L;
    while (ptr->suivant) ptr = ptr->suivant;
    ptr->suivant = elem;
    return 1;
}

/* Afficher une liste */
void AfficherListe(LISTE *L) {
    printf("[ ");
    while (L) { printf("%d ", L->val); L = L->suivant; }
    printf("]\n");
}

/* ===================================================
 * EXERCICE 1 : Créer une liste de 100 entiers aléatoires [0,100[
 * Complexité : O(n)
 * =================================================== */
LISTE *CreerListeAleatoire(int n) {
    LISTE *L = NULL;
    int i;
    for (i = 0; i < n; i++)
        InsererEnTete(&L, rand() % 100);
    return L;
}

/* ===================================================
 * EXERCICE 2 : Rechercher une valeur — O(n)
 * =================================================== */
int RechercherValeur(LISTE *L, int valeur) {
    while (L) {
        if (L->val == valeur) return 1;
        L = L->suivant;
    }
    return 0;
}

/* ===================================================
 * EXERCICE 3 : Supprimer le nœud de valeur minimale — O(n)
 * =================================================== */
int SupprimerMin(LISTE **L) {
    if (!*L) return 0;

    LISTE *ptr = *L, *pMin = NULL, *pPrec = NULL;
    int minim = (*L)->val;

    /* Cas : liste à 1 élément */
    if (!ptr->suivant) {
        *L = NULL; free(ptr); return 1;
    }

    /* Trouver le précédent du minimum */
    while (ptr->suivant) {
        if (minim > ptr->suivant->val) {
            minim = ptr->suivant->val;
            pMin  = ptr;
        }
        ptr = ptr->suivant;
    }

    if (!pMin) {
        /* Le min est en tête */
        ptr = *L;
        *L  = (*L)->suivant;
        free(ptr);
    } else {
        ptr = pMin->suivant;
        pMin->suivant = pMin->suivant->suivant;
        free(ptr);
    }
    return 1;
}

/* ===================================================
 * EXERCICE 4 : Fusion alternée de deux listes — O(m+n)
 * =================================================== */
LISTE *FusionnerListes(LISTE *L1, LISTE *L2) {
    LISTE *res = NULL;
    LISTE *p1  = L1, *p2 = L2;

    if (!L1) return L2;
    if (!L2) return L1;

    while (p1 && p2) {
        InsererEnFin(&res, p1->val);
        InsererEnFin(&res, p2->val);
        p1 = p1->suivant;
        p2 = p2->suivant;
    }
    while (p1) { InsererEnFin(&res, p1->val); p1 = p1->suivant; }
    while (p2) { InsererEnFin(&res, p2->val); p2 = p2->suivant; }

    return res;
}

/* ===================================================
 * EXERCICE 5 : Détruire une liste — O(n)
 * =================================================== */
void DetruireListe(LISTE **L) {
    LISTE *ptr;
    while (*L) {
        ptr = *L;
        *L  = (*L)->suivant;
        free(ptr);
    }
}

/* =====================================================
 * PILES (liste chaînée)
 * ===================================================== */

typedef struct Pile {
    int data;
    struct Pile *next;
} PILE;

void push(PILE **head, int value) {
    PILE *node = (PILE *)malloc(sizeof(PILE));
    if (!node) { fprintf(stderr, "Erreur malloc pile\n"); exit(1); }
    node->data = value;
    node->next = *head;
    *head = node;
}

int pop(PILE **head) {
    if (!*head) { fprintf(stderr, "Pile vide!\n"); exit(1); }
    PILE *top = *head;
    int val   = top->data;
    *head     = top->next;
    free(top);
    return val;
}

int pileVide(PILE *head) { return head == NULL; }

void afficherPile(PILE *P) {
    printf("Pile (sommet -> bas) : ");
    while (P) { printf("%d ", P->data); P = P->next; }
    printf("\n");
}

/* ===================================================
 * EXERCICE 6 : PairImpair
 * Déplacer les pairs sous les impairs dans P2 — O(n)
 * =================================================== */
PILE *PairImpair(PILE *P1) {
    PILE *P2 = NULL, *P3 = NULL;
    int val;

    while (!pileVide(P1)) {
        val = pop(&P1);
        if (val % 2 == 0) push(&P2, val);
        else               push(&P3, val);
    }
    /* Mettre les impairs (P3) sur les pairs (P2) */
    while (!pileVide(P3)) {
        val = pop(&P3);
        push(&P2, val);
    }
    return P2;
}

/* =====================================================
 * FILE (queue)
 * ===================================================== */

typedef struct QueueNode {
    char data;
    struct QueueNode *next;
} QNODE;

typedef struct {
    QNODE *first;
    QNODE *last;
} QUEUE;

int enqueue(QUEUE *q, char value) {
    QNODE *node = (QNODE *)malloc(sizeof(QNODE));
    if (!node) return 1;
    node->data = value;
    node->next = NULL;
    if (!q->first) { q->first = q->last = node; }
    else           { q->last->next = node; q->last = node; }
    return 0;
}

int dequeue(QUEUE *q, char *value) {
    if (!q->first) { *value = 0; return 1; }
    *value = q->first->data;
    QNODE *tmp = q->first;
    if (q->first == q->last) q->first = q->last = NULL;
    else                     q->first = q->first->next;
    free(tmp);
    return 0;
}

/* Pile de caractères */
typedef struct PileChar {
    char data;
    struct PileChar *next;
} PILEC;

void pushC(PILEC **head, char value) {
    PILEC *node = (PILEC *)malloc(sizeof(PILEC));
    node->data  = value;
    node->next  = *head;
    *head = node;
}

char popC(PILEC **head) {
    if (!*head) { fprintf(stderr, "Pile vide!\n"); exit(1); }
    PILEC *top = *head;
    char val   = top->data;
    *head      = top->next;
    free(top);
    return val;
}

/* ===================================================
 * EXERCICE 7 : EcrireMessage et EstPalindrome
 * =================================================== */
QUEUE *EcrireMessage(char chaine[]) {
    int i, taille = (int)strlen(chaine);
    QUEUE *q = (QUEUE *)malloc(sizeof(QUEUE));
    if (!q) { printf("Erreur malloc\n"); exit(0); }
    q->first = q->last = NULL;
    for (i = 0; i < taille; i++) enqueue(q, chaine[i]);
    return q;
}

int EstPalindrome(char chaine[]) {
    int len = (int)strlen(chaine);
    int demi = len / 2;
    int impair = len % 2;
    int i;
    char val, c1, c2;

    PILEC *p = NULL;
    QUEUE *Q = EcrireMessage(chaine);

    /* Empiler la première moitié */
    for (i = 0; i < demi; i++) {
        dequeue(Q, &val);
        pushC(&p, val);
    }
    /* Sauter le caractère central si longueur impaire */
    if (impair) dequeue(Q, &val);

    /* Comparer la seconde moitié avec la pile */
    for (i = 0; i < demi; i++) {
        dequeue(Q, &c1);
        c2 = popC(&p);
        if (c1 != c2) { free(Q); return 0; }
    }
    free(Q);
    return 1;
}

/* =====================================================
 * PROGRAMME PRINCIPAL
 * ===================================================== */

int main() {
    srand((unsigned int)time(NULL));
    int i;

    /* --- Exercice 1 : Création --- */
    printf("=== TD3 - Ex1 : Creation liste de 10 elements aleatoires ===\n");
    LISTE *L = CreerListeAleatoire(10);
    AfficherListe(L);

    /* --- Exercice 2 : Recherche --- */
    printf("\n=== TD3 - Ex2 : Recherche ===\n");
    int val = 50;
    printf("Valeur %d dans la liste : %s\n", val, RechercherValeur(L, val) ? "OUI" : "NON");
    val = L->val; /* chercher le premier élément */
    printf("Valeur %d dans la liste : %s\n", val, RechercherValeur(L, val) ? "OUI" : "NON");

    /* --- Exercice 3 : Suppression du min --- */
    printf("\n=== TD3 - Ex3 : Suppression du minimum ===\n");
    printf("Avant : "); AfficherListe(L);
    SupprimerMin(&L);
    printf("Apres : "); AfficherListe(L);

    /* --- Exercice 4 : Fusion --- */
    printf("\n=== TD3 - Ex4 : Fusion de deux listes ===\n");
    LISTE *A = NULL, *B = NULL;
    for (i = 0; i < 4; i++) InsererEnFin(&A, i + 1);
    for (i = 0; i < 6; i++) InsererEnFin(&B, (i + 1) * 10);
    printf("Liste A : "); AfficherListe(A);
    printf("Liste B : "); AfficherListe(B);
    LISTE *C = FusionnerListes(A, B);
    printf("Fusion  : "); AfficherListe(C);

    /* --- Exercice 5 : Destruction --- */
    printf("\n=== TD3 - Ex5 : Destruction ===\n");
    DetruireListe(&L);
    printf("Liste detruite. L = %s\n", L == NULL ? "NULL" : "non NULL");

    /* --- Exercice 6 : Piles PairImpair --- */
    printf("\n=== TD3 - Ex6 : PairImpair ===\n");
    PILE *P1 = NULL;
    for (i = 1; i <= 9; i++) push(&P1, i);
    printf("P1 initiale : "); afficherPile(P1);
    PILE *P2 = PairImpair(P1);
    printf("P2 (impairs dessus, pairs dessous) : "); afficherPile(P2);

    /* --- Exercice 7 : Palindrome --- */
    printf("\n=== TD3 - Ex7 : Palindrome ===\n");
    char *mots[] = {"radar", "level", "bonjour", "kayak", "hello"};
    int nb = sizeof(mots) / sizeof(mots[0]);
    for (i = 0; i < nb; i++) {
        printf("'%s' : %s\n", mots[i], EstPalindrome(mots[i]) ? "PALINDROME" : "PAS un palindrome");
    }

    return 0;
}

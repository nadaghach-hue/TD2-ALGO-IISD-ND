# Compte Rendu — TP Complexité & Structures de Données Abstraites

**Filières :** IISD & IDRS  
**Semestre :** 2

---

## TD1 — Les Structures

### Exercice 1 : Structure Point

Nous avons défini la structure `Point` avec deux champs entiers `abs` et `ord` représentant les coordonnées cartésiennes d'un point dans le plan.

```c
typedef struct {
    int abs;
    int ord;
} Point;
```

**Fonctions implémentées :**

- `SaisirPoint()` : lit les coordonnées depuis l'entrée standard et retourne un `Point`.
- `AfficherPoint(Point p)` : affiche le point au format `(x, y)`.
- `DistanceParValeur(Point p)` : calcule √(x² + y²) en passant la structure par valeur.
- `DistanceParAdresse(Point *p)` : même calcul, mais en passant un pointeur (plus efficace pour les grandes structures).
- `TrierParDistance(Point t[], int n)` : tri par sélection des points selon leur distance à l'origine, complexité **O(n²)**.

**Tableaux statique et dynamique :**  
Le tableau statique utilise un espace connu à la compilation (`#define TMAX 20`), tandis que le tableau dynamique est alloué avec `malloc` selon la taille saisie à l'exécution.

**Résultat de test :**  
Pour le point (3, 4), la distance calculée est **5.00** (triangle rectangle de Pythagore), correcte dans les deux versions (valeur et adresse).

---

### Exercice 2 : Structure Heure

```c
typedef struct {
    int hh;
    int mm;
    int ss;
} Heure;
```

**Fonctions :**

| Fonction | Description |
|----------|-------------|
| `HeureEnSecondes(h)` | Convertit hh:mm:ss en entier de secondes |
| `SecondesEnHeure(sec)` | Reconstruction d'une Heure depuis des secondes |
| `AddHeures(h1, h2)` | Addition via conversion en secondes |
| `DiffHeures(h1, h2)` | Différence absolue entre deux instants |

**Exemple :** `01:30:45 + 00:45:20 = 02:16:05`  
La stratégie de conversion en secondes puis reconstruction simplifie l'implémentation et évite les erreurs de report (carry).

---

## TD2 — Complexité & Récursivité

### Exercice 1 : Indice du minimum

**Algorithme :** Parcours linéaire unique du tableau en conservant l'indice courant du minimum.

**Calcul de complexité :**
- 1 initialisation
- n-1 comparaisons
- Au plus n-1 affectations
- **T(n) = 4n - 2 → O(n)**

**Test :** Pour le tableau `{5,2,4,2,1,7,9,4,1,1}`, l'indice du minimum (valeur 1) est **4**. ✓

---

### Exercice 2 : MiniMax d'une matrice

**Algorithme :** Pour chaque ligne, calculer le maximum. Puis retourner le minimum de ces maxima.

**Complexité :** T(n,m) = 4·n·m + 3·n - 2 → **O(n×m)**  
Si n = m : **O(n²)**

**Test :** Pour la matrice `{{2,3,4},{5,1,7},{8,9,6}}`, les maxima par ligne sont 4, 7, 9. Le MiniMax est **4**. ✓

---

### Exercice 3 : Puissance récursive

**Version simple :**
```
T(0) = 0
T(n) = 1 + T(n-1) = n → O(n)
```

**Exponentiation rapide (fast power) :**
La clé est de remarquer que `aⁿ = (aⁿ/²)²` si n est pair. Cela divise le problème par 2 à chaque appel :
```
T(n) = T(n/2) + O(1) → O(log n)
```

**Somme des puissances S(a,n) = Σaⁱ (i=0 à n) :**  
Chaque terme fait appel à `puissance` en O(n), et il y a n termes → **O(n²)**

---

### Exercice 4 : rec1 vs rec2

Les deux fonctions calculent **2ⁿ**, mais avec des complexités radicalement différentes :

| Fonction | Structure | Complexité |
|----------|-----------|------------|
| `rec1(n)` | Arbre de récursion linéaire (chaîne) | **O(n)** |
| `rec2(n)` | Arbre binaire complet (2 appels récursifs) | **O(2ⁿ)** |

**Analyse de rec2 :**
```
T(0) = 0
T(n) = 1 + 2·T(n-1)
     = 1 + 2 + 4 + ... + 2ⁿ⁻¹ = 2ⁿ - 1
```
`rec2` est exponentiellement plus coûteuse que `rec1` malgré un résultat identique. C'est un exemple classique de **redondance de calculs** dans la récursivité.

---

## TD3 — Listes Chaînées, Piles, Files

### Structure de base

```c
typedef struct Element {
    int val;
    struct Element *suivant;
} LISTE;
```

### Exercice 1 : Création — O(n)

Chaque insertion en tête est en O(1), donc n insertions sont en **O(n)**.

### Exercice 2 : Recherche — O(n)

Parcours séquentiel de la liste. Dans le pire cas (valeur absente), on visite tous les n nœuds.

### Exercice 3 : Suppression du minimum — O(n)

Un seul parcours suffit pour trouver le précédent du nœud minimum et effectuer la suppression. Trois cas à traiter : liste vide, liste à un élément, minimum en tête ou ailleurs.

### Exercice 4 : Fusion alternée — O(m + n)

On intercale les éléments des deux listes puis on concatène le reste de la plus longue.  
**Test :** `A=[1,2,3,4]`, `B=[10,20,30,40,50,60]` → `C=[1,10,2,20,3,30,4,40,50,60]` ✓

### Exercice 5 : Destruction — O(n)

Libération successive de chaque nœud avec `free()`. Le pointeur tête est mis à NULL.

### Exercice 6 : PairImpair (Pile)

**Stratégie :** Dépiler P1, envoyer les pairs dans P2 et les impairs dans P3. Puis vider P3 dans P2 (les impairs se retrouvent au-dessus).

**Test :** `P1 = {9,8,7,6,5,4,3,2,1}` → `P2 = {9,7,5,3,1,2,4,6,8}` (impairs au sommet, pairs à la base) ✓

### Exercice 7 : Palindrome (File + Pile)

**Algorithme :**
1. Stocker le message dans une file (EcrireMessage).
2. Défiler la première moitié et empiler les caractères.
3. Sauter le caractère central (si longueur impaire).
4. Comparer la seconde moitié (défilée) avec la pile (dépilée).

**Résultats :**

| Mot | Résultat |
|-----|----------|
| `radar` | PALINDROME ✓ |
| `level` | PALINDROME ✓ |
| `kayak` | PALINDROME ✓ |
| `bonjour` | NON ✓ |
| `hello` | NON ✓ |

---

## TD4 — Arbres Binaires de Recherche

### Propriété fondamentale

Pour tout nœud N d'un ABR : tous les nœuds du sous-arbre gauche sont ≤ N, et tous les nœuds du sous-arbre droit sont > N.

### Exercice 1

**Insertion (O(h)) :** Descente récursive selon la propriété ABR jusqu'à une feuille NULL.

**Recherche (O(h)) :** Même logique de descente. Beaucoup plus rapide qu'une liste chaînée en moyenne.

**Occurrences (O(n)) :** Un parcours infixé complet est nécessaire car des doublons peuvent apparaître dans les deux sous-arbres (selon la règle d'insertion utilisée).

**Parcours infixé (O(n)) :** Visite Gauche → Racine → Droite. Produit les clés dans l'ordre croissant. Propriété remarquable des ABR.

**Liste triée depuis ABR (O(n)) :** Le parcours infixé produit naturellement une liste triée par ordre croissant.

**Tri par ABR — Tree Sort (O(n log n) moyen) :**
1. Construire l'ABR depuis la liste non triée : O(n log n) en moyenne.
2. Parcours infixé pour reconstruire la liste triée : O(n).
3. Total : **O(n log n)** en moyenne, **O(n²)** dans le pire cas (liste déjà triée → arbre dégénéré).

### Exercice 2 : Vérification ABR — O(n)

**Méthode :** Effectuer le parcours infixé et vérifier que la liste obtenue est triée par ordre croissant. Si un élément est supérieur au suivant, l'arbre n'est pas un ABR.

### Exercice 3 : Plus petit élément — O(h)

**Méthode :** Descendre dans le sous-arbre gauche jusqu'à ne plus pouvoir. Le nœud le plus à gauche est le minimum.

---

## Bilan des complexités

| Structure | Accès | Insertion | Suppression | Recherche |
|-----------|-------|-----------|-------------|-----------|
| Tableau | O(1) | O(n) | O(n) | O(n) |
| Liste chaînée | O(n) | O(1) tête | O(n) | O(n) |
| ABR (moyen) | O(log n) | O(log n) | O(log n) | O(log n) |
| ABR (pire) | O(n) | O(n) | O(n) | O(n) |

---

## Conclusion

Ce TP a permis d'implémenter et d'analyser les structures de données fondamentales en C :

- Les **structures** permettent de regrouper des données hétérogènes de manière logique.
- La **récursivité** est puissante mais peut mener à des complexités exponentielles si mal utilisée (`rec2` vs `rec1`).
- Les **listes chaînées** offrent une flexibilité mémoire mais un accès séquentiel lent.
- Les **piles et files** sont des abstractions simples aux cas d'usage très variés (palindrome, tri, parsing…).
- Les **ABR** offrent un excellent compromis entre flexibilité et efficacité, avec O(log n) en moyenne pour les opérations principales.

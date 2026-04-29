# TP — Complexité & Structures de Données Abstraites
**Filières : IISD & IDRS — Semestre 2**

---

## Structure du projet

```
.
├── TD1/
│   └── td1.c          # Structures : Point et Heure
├── TD2/
│   └── td2.c          # Complexité et récursivité
├── TD3/
│   └── td3.c          # Listes chaînées, Piles, Files
├── TD4/
│   └── td4.c          # Arbres Binaires de Recherche (ABR)
├── compte_rendu.md    # Rapport complet du TP
└── README.md
```

---

## Compilation et exécution

### Prérequis
- GCC (ou tout compilateur C standard)
- Bibliothèque mathématique `-lm` pour TD1

### Compiler chaque TD

```bash
# TD1
gcc TD1/td1.c -o TD1/td1 -lm
./TD1/td1

# TD2
gcc TD2/td2.c -o TD2/td2
./TD2/td2

# TD3
gcc TD3/td3.c -o TD3/td3
./TD3/td3

# TD4
gcc TD4/td4.c -o TD4/td4
./TD4/td4
```

---

## Contenu des TDs

### TD1 — Les Structures
- **Exercice 1** : Structure `Point` (coordonnées entières), saisie, affichage, distance à l'origine, tri par distance
- **Exercice 2** : Structure `Heure` (hh/mm/ss), conversion en secondes, addition, différence

### TD2 — Complexité & Récursivité
| Exercice | Description | Complexité |
|----------|-------------|------------|
| Ex1 | Indice du minimum dans un tableau | O(n) |
| Ex2 | MiniMax d'une matrice | O(n×m) |
| Ex3 | Puissance récursive simple | O(n) |
| Ex3 | Exponentiation rapide | O(log n) |
| Ex3 | Somme des puissances | O(n²) |
| Ex4 | `rec1(n)` — calcule 2ⁿ | O(n) |
| Ex4 | `rec2(n)` — calcule 2ⁿ | O(2ⁿ) |

### TD3 — Listes, Piles, Files
| Exercice | Description | Complexité |
|----------|-------------|------------|
| Ex1 | Création d'une liste de n éléments aléatoires | O(n) |
| Ex2 | Recherche d'une valeur | O(n) |
| Ex3 | Suppression du minimum | O(n) |
| Ex4 | Fusion alternée de deux listes | O(m+n) |
| Ex5 | Destruction d'une liste | O(n) |
| Ex6 | PairImpair avec piles | O(n) |
| Ex7 | Détection de palindrome (file + pile) | O(n) |

### TD4 — Arbres Binaires de Recherche
| Exercice | Description | Complexité |
|----------|-------------|------------|
| Ex1.1 | Insertion | O(h) |
| Ex1.2 | Recherche | O(h) |
| Ex1.3 | Nombre d'occurrences | O(n) |
| Ex1.4 | Parcours infixé | O(n) |
| Ex1.5 | Construction liste triée depuis ABR | O(n) |
| Ex1.6 | Construction ABR depuis liste | O(n log n) moy. |
| Ex1.7 | Tri de liste via ABR (Tree Sort) | O(n log n) moy. |
| Ex2 | Vérification ABR | O(n) |
| Ex3 | Plus petit élément | O(h) |

> h = hauteur de l'arbre. En moyenne h = O(log n), au pire h = O(n).

---

## Résultats des tests

Tous les programmes compilent et s'exécutent sans erreur avec GCC.

```
TD1 : OK — Points triés par distance, conversions d'heures correctes
TD2 : OK — Indice min = 4, MiniMax = 4, 2^10 = 1024
TD3 : OK — Palindromes détectés, fusion et tri corrects
TD4 : OK — ABR valide détecté, tri par ABR fonctionnel
```

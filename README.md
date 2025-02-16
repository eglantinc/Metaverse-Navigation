# Metaverse-Navigation

## Contexte

Un agent se déplace dans un univers virtuel représenté par une grille de taille **N × N**. L'agent a une couleur de départ et chaque cellule possède une couleur. Il ne peut pas se déplacer sur une cellule ayant la même couleur que lui, mais il peut changer sa couleur pour un coût de 10. Ce projet a été complété dans le cadre du cours Structure de données et Algorithmes (INF3105) à l'Université du Québec à Montréal.

## Auteure
**Nom : [Églantine Clervil]**  

Les déplacements sont possibles horizontalement et verticalement avec un coût de 1.

## Problématique

L'algorithme de **Dijkstra** est utilisé pour optimiser les déplacements de l'agent.

Une technique d’optimisation consiste à "dupliquer" l’univers : un univers pour chaque couleur. Chaque agent peut changer d'univers en changeant de couleur pour un coût de 10.

Ainsi, à partir d'une position **(x, y, c)** :
- Il peut accéder à **(x, y, c')** pour toute autre couleur "c'" avec un coût de 10.
- Il peut se déplacer à droite, gauche, haut ou bas si la couleur de la cellule cible est différente, avec un coût de 1.

## Compilation

Votre projet doit pouvoir être compilé avec la commande suivante :
```bash
make
```

**Syntaxe d'appel du programme :**
```bash
./tp3 univers.txt X_Depart Y_Depart CouleurAgent_Depart X_Destination Y_Destination
```

### Format du fichier d'univers

Le fichier **univers.txt** suit cette structure :
```
N C
couleur_0_0 couleur_0_1 ... couleur_0_n-1
...
couleur_n-1_0 couleur_n-1_1 ... couleur_n-1_n-1
```
- **N** : taille de la grille
- **C** : nombre de couleurs

Exemple :
```
20 3
0 1 1 1 ...
0 1 1 0 ...
...
```

## Format de sortie

Le programme produit une liste d'actions menant à la destination avec un coût minimum. Les actions possibles sont :
- **d** : droite
- **g** : gauche
- **h** : haut
- **b** : bas
- **c** : changer de couleur

Exemple de sortie :
```
c d d d d d d d d d d c d d d d d d b c d b d 50
```




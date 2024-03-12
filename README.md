# **Projet so_long**

<div align="center">
  <img src="https://github.com/byaliego/42-project-badges/blob/main/badges/so_longm.png" alt="Badge du projet so_long">
</div>

##
<div align="center">
  <img src="https://github.com/Omisev/so_long/blob/main/so_long_representation.webp" alt="representation">
</div>

##
<div align="center">
  <img src="https://github.com/Omisev/so_long/blob/main/screenshot.png" alt="sreenshot">
</div>


## Description
Ce projet consiste à créer un jeu simple en utilisant la bibliothèque MinilibX. Le joueur doit récupérer tous les objets et atteindre la sortie.

## Tableau des Composants du Projet

| Fichier             | Description                                                             | Responsabilité                                  | Statut    |
|---------------------|-------------------------------------------------------------------------|-------------------------------------------------|-----------|
| `main.c`            | Fichier principal, contient la logique de haut niveau                   | Initialisation, boucle de jeu                   | Complet   |
| `init_game.c`       | Initialise les structures et les variables                              | Initialisation                                  | Complet   |
| `render.c`          | Gère l'affichage des éléments sur l'écran                               | Affichage                                       | Complet   |
| `events.c`          | Gère les événements clavier                                             | Déplacement, sortie                             | Complet   |
| `map_parser.c`      | Lit et valide la carte du jeu                                           | Parsing de la carte                             | Complet   |
| `utils.c`           | Fonctions utilitaires                                                    | Fonctions auxiliaires                           | Complet   |
| `Makefile`          | Fichier pour compiler le projet                                          | Compilation                                      | Complet   |
| `so_long.h`         | Fichier d'en-tête contenant les déclarations et les macros               | Déclarations                                    | Complet   |


## Installation et Compilation
```
git clone git@github.com:Omisev/so_long.git
cd so_long
```

## Utilisation
```
make
./so_long maps/mandatory/map1.ber
```

## Options
```
make bonus
./so_long_bonus maps/bonus/map1.ber
```



## Caractéristiques
- Utilisation de la bibliothèque graphique MinilibX
- Gestion des événements clavier
- Absence de fuites de mémoire
- Respect des normes de l'école 42

## Fonctions externes autorisées
- malloc
- free
- read
- write
- exit

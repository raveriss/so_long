# so_long - École 42 | Paris

<div align="center">
  <img src="https://img.shields.io/badge/graphics-MinilibX-green" alt="MinilibX">
  <img src="https://img.shields.io/badge/school-42-blue" alt="42">
  <img src="https://img.shields.io/badge/project-so_long-orange" alt="so_long">
  <img src="https://img.shields.io/badge/language-C-blue" alt="Language">
  <img src="https://img.shields.io/badge/norm-42-green" alt="42 Norm">
  <img src="https://img.shields.io/badge/library-Libft-orange" alt="Libft">
  <img src="https://img.shields.io/badge/objective-2D%20game-yellowgreen" alt="2D Game">
  <img src="https://img.shields.io/badge/assets-sprites-lightblue" alt="Sprites">
  <img src="https://img.shields.io/badge/feature-pathfinding-9cf" alt="Pathfinding">
  <img src="https://img.shields.io/badge/feature-keyboard%20controls-ff69b4" alt="Keyboard Controls">
  <img src="https://img.shields.io/badge/repo_size-3.33%20MiB-blue" alt="Repo Size">
  <img src="https://img.shields.io/badge/last_commit-14%20March%202024-lightgrey" alt="Last Commit">
</div>

###
<div align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/refs/heads/main/badges/so_longe.png?raw=true" alt="Badge du projet push_swap">
</div>

##
<div align="center">
  <img src="https://github.com/Omisev/so_long/blob/main/so_long_representation.webp" alt="representation">
</div>

## Description

Le projet **`so_long`** consiste à créer un petit jeu en vue `2D`, reposant sur la **MiniLibX**. L’objectif est d’afficher une carte, représentée par un fichier `.ber`, dans laquelle un personnage peut se déplacer afin de collecter des objets et atteindre une sortie. Le jeu propose une mécanique simple de déplacement, la prise en compte de collisions, ainsi qu’un système d’interactions élémentaires (collecte, détection de victoire, gestion d’ennemis optionnels, etc.).

Le but est d’apprendre à manipuler la **MiniLibX**, à gérer des textures, la lecture et validation de fichiers de configuration, et à mettre en œuvre une logique de jeu simple, tout en respectant les normes et contraintes de l’École `42`.

## Objectifs

- Afficher une grille de jeu en `2D` à partir d’une carte `.ber`.
- Gérer le déplacement du joueur dans un environnement fermé.
- Collecter tous les objets (collectibles) avant d’atteindre la sortie.
- Assurer une validation robuste du contenu de la carte (bords, format, nombre de collectibles, position du joueur et de la sortie).
- Respecter les règles imposées par **`MinilibX`** et l’écosystème `42`.
- Optionnel (bonus) : Ajouter des ennemis, un compteur de mouvements à l’écran, des animations, ou d’autres fonctionnalités avancées.

## Fonctionnalités

- **Moteur 2D basique** : Affiche chaque case de la carte avec la texture correspondante (murs, sol, collectibles, sortie, joueur).
- **Validation des cartes** : Vérification stricte des fichiers `.ber` (format, présence des éléments obligatoires, validation par flood-fill, etc.).
- **Collecte d’objets & condition de victoire** : Le joueur doit récupérer tous les objets avant de pouvoir sortir.
- **Mouvements du joueur** : Contrôle du déplacement via le clavier, gestion des collisions, et affichage du compteur de mouvements.
- **Version bonus** : Support d’ennemis, animations supplémentaires, effets visuels, comptage du temps ou affichage sur la fenêtre, etc.

## Structure du Projet

```bash
.
├── includes
│   ├── so_long.h
│   └── so_long_bonus.h
├── Makefile
├── maps
│   ├── mandatory
│   │   └── map1.ber
│   └── bonus
│       └── map1.ber
├── README.md
├── screenshot.png
├── so_long_representation.webp
├── srcs
│   ├── border_and_character_checks.c
│   ├── collectible_assets_handler.c
│   ├── collectible_exit_map_validation.c
│   ├── elements_positioning.c
│   ├── error_and_exit_handler.c
│   ├── grid_regularity_check.c
│   ├── keyboard_controls_and_movement.c
│   ├── main.c
│   ├── map_allocation_and_reading.c
│   ├── map_ber_file_check.c
│   ├── map_flood_fill_check.c
│   ├── move_counter_display.c
│   ├── player_actions_and_game_update.c
│   ├── resource_cleanup.c
│   ├── set_and_win_init.c
│   ├── texture_file_existence_check.c
│   ├── texture_init.c
│   ├── texture_loader.c
│   └── texture_positioning.c
├── srcs_bonus
│   ├── border_and_character_checks_bonus.c
│   ├── collectible_assets_handler_bonus.c
│   ├── collectible_exit_map_validation_bonus.c
│   ├── elements_positioning_bonus.c
│   ├── error_and_exit_handler_bonus.c
│   ├── grid_regularity_check_bonus.c
│   ├── keyboard_controls_and_movement_bonus.c
│   ├── main_bonus.c
│   ├── map_allocation_and_reading_bonus.c
│   ├── map_ber_file_check_bonus.c
│   ├── map_flood_fill_check_bonus.c
│   ├── move_counter_display_bonus.c
│   ├── player_actions_and_game_update_bonus.c
│   ├── resource_cleanup_bonus.c
│   ├── set_and_win_init_bonus.c
│   ├── texture_file_existence_check_bonus.c
│   ├── texture_init_bonus.c
│   ├── texture_loader_bonus.c
│   └── texture_positioning_bonus.c
└── xpm
    ├── border_bottom.xpm
    ├── border_left.xpm
    ├── border_right.xpm
    ├── border_top.xpm
    ├── collectible*.xpm
    ├── corner_*.xpm
    ├── exit_*.xpm
    ├── ground_texture.xpm
    ├── lethal_enemies_*.xpm
    ├── player_*.xpm
    └── wall_texture.xpm
```
-  (Note : Le symbole `*` indique de multiples variantes de fichiers similaires.)

## Installation
```
git clone git@github.com:raveriss/so_long.git
cd so_long
```
## Compilation
**Utilisez le Makefile pour compiler le projet avec les options requises (`-Wall` `-Wextra` `-Werror`).**

Commandes disponibles :

```bash
make        # Compile la version mandatory
make clean  # Supprime les fichiers objets
make fclean # Supprime les fichiers objets et binaires
make re     # Recompile le projet
make bonus  # Compile la version bonus du projet
```
## Lancement du Jeu

Argument :
`<path_to_map.ber>` : Chemin vers une carte valide au format `.ber`.

## Mandatory

  ```
  ./so_long <path_to_map.ber>
  ```
  
  Exemple :
  
  ```bash
  ./so_long maps/mandatory/map1.ber
  ```

## Bonus
```
./so_long_bonus `<path_to_map.ber>`
```

  Exemple :
  ```bash
  ./so_long_bonus maps/bonus/map1.ber
  ```

## Aperçu
<div align="center">
  <img src="https://github.com/Omisev/so_long/blob/main/screenshot.png" alt="sreenshot">
</div>

## Tester le Projet
- Cartes valides : Testez avec les cartes du dossier `maps/mandatory/` pour vérifier le bon fonctionnement.
- Cartes invalides : Créez des cartes invalides ou modifiez les exemples pour tester la robustesse de la validation (trous dans la carte, pas de collectibles, pas de sortie, fichier corrompu, etc.).

## Contrôles

| Key / Input    | Action                       |
|----------------|------------------------------|
|   `W` / `Z`	 | Déplacer vers le haut        |
|   `A` / `Q`	 | Déplacer vers la gauche      |
|      `S`	 | Déplacer vers le bas         |
|      `D`	 | Déplacer vers la droite      |
| `ESC` / `Croix`| Quitter le jeu               |

(Adapter les touches suivant le clavier `AZERTY`/`QWERTY` si besoin.)

## Débogage et Diagnostic
Vérifiez l'absence de fuites de mémoire et autres erreurs :

```bash
valgrind ./so_long <path_to_map.ber>
```

## Gestion des Erreurs et Validation
- **Fichiers .ber invalides** : Testez les scénarios où le fichier n’existe pas, est corrompu ou ne se termine pas par `.ber`.
- **Validation de la carte** : Vérifiez les erreurs liées au placement du `joueur`, des `murs`, des `collectibles`, et de la `sortie`.
- **Manque d’éléments essentiels** : Assurez-vous que le programme signale l’absence du `joueur`, de la `sortie` ou des `collectibles`.

## Fonctionnalités Bonus
- Ajout d’ennemis mobiles ou statiques.
- Animations avancées (mouvement du `joueur`, changement de `texture`, etc.).
- Affichage du compteur de mouvements à l’écran.
- Détection de collisions plus complexes ou introduction de mécanismes additionnels.

## Contributeurs
[raveriss](https://github.com/raveriss) 

## Ressources Utilisées
- [Documentation de la MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx)
- [minilibx](https://github.com/42Paris/minilibx-linux)
- [Raycasting / Rendering 2D Basics](https://lodev.org/cgtutor/)
- [Pixel drawing with the minilibx](https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx)
- [Game art 2D](https://www.gameart2d.com/freebies.html)
- [Algorithme de remplissage par diffusion](https://fr.wikipedia.org/wiki/Algorithme_de_remplissage_par_diffusion)


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:18:43 by raveriss          #+#    #+#             */
/*   Updated: 2023/06/01 15:54:06 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"

/* Lib for exit, malloc */
# include <stdlib.h>

/* Lib for open */
# include <fcntl.h>

/* Lib for write */
# include <unistd.h>
# define VALID_CHARACTERS "01CEP\n"
# define ERR_INVALID_EXTENSION "Invalid extension. Use .ber only\n"
# define ERR_INVALID_MAP_ENTITIES "Invalid map. Check 'E', 'C' and 'P'.\n"
# define ERR_MAP_NOT_SURROUNDED "file not surrounded by '1'\n"
# define ERR_FILE_CHECK_ERROR "An error occurred while checking the .ber file\n"
# define ERR_IRREGULAR_GRID "file does not represent a regular 2D grid\n"
# define ERR_INVALID_CHARS_IN_FILE "Invalid characters found in the .ber file\n"
# define ERR_INVALID_ARGUMENT "Invalid argument\n"
# define ERR_FILE_UNREADABLE "Le fichier n'est pas readable\n"
# define ERR_INSUFFICIENT_ARGUMENTS "Pas assez d'arguments\n"
# define ERR_UNWINNABLE "Unwinnable game. Verify map.\n"
# define ANIMATE_COLLECT_IMG 12
# define XPM_IMG_COUNT 30
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_ESCAPE 65307

/*
** Structure : s_map
**
** Description : Représente les informations relatives à la carte du jeu.
**
** Champs :
**     - height (int) : Hauteur de la carte.
**     - width (int) : Largeur de la carte.
**     - player_spot (int) : Position du joueur sur la carte.
**     - player_count (int) : Nombre de joueurs sur la carte.
**     - exit_spot (int) : Position de la sortie sur la carte.
**     - exit_count (int) : Nombre de sorties sur la carte.
**     - sum_lines (int) : Somme des lignes de la carte.
**     - sum_columns (int) : Somme des colonnes de la carte.
**     - colect_count (int) : Nombre total de collectibles sur la carte.
**     - check_colect_count (int) : Nombre de collectibles vérifiés sur la
**       carte.
**     - check_map (char*) : Pointeur vers une chaîne de caractères
**                           représentant la carte vérifiée.
**     - play_map (char*) : Pointeur vers une chaîne de caractères représentant
**                          la carte de jeu.
**     - check_exit_reach (int) : Position de la sortie vérifiée sur la carte.
**
** Note : La structure `s_map` contient les informations relatives à la carte du
**        jeu. Elle comprend des champs pour représenter la taille de la
**        carte, les positions du joueur et de la sortie, le nombre de joueurs
**        et de sorties, les compteurs de collectibles, ainsi que des
**        pointeurs vers les chaînes de caractères représentant la carte
**        vérifiée et la carte de jeu. Le champ `check_exit_reach`
**        représente la position de la sortie vérifiée sur la carte.
*/
typedef struct s_map
{
	int		height;
	int		width;
	int		player_spot;
	int		player_count;
	int		exit_spot;
	int		exit_count;
	int		sum_lines;
	int		sum_columns;
	int		colect_count;
	int		check_colect_count;
	char	*check_map;
	char	*play_map;
	int		check_exit_reach;
}			t_map;

/*
** Structure : s_textures
**
** Description : Représente les textures utilisées dans le jeu.
**
** Champs :
**     - wall (void*) : Texture du mur.
**     - player (void*) : Texture du joueur.
**     - colect (void*) : Texture du collectible.
**     - killer (void*) : Texture de l'obstacle.
**     - ground (void*) : Texture du sol.
**     - corner_top_left (void*) : Texture du coin supérieur gauche.
**     - corner_top_right (void*) : Texture du coin supérieur droit.
**     - corner_bottom_left (void*) : Texture du coin inférieur gauche.
**     - corner_bottom_right (void*) : Texture du coin inférieur droit.
**     - border_top (void*) : Texture de la bordure supérieure.
**     - border_bottom (void*) : Texture de la bordure inférieure.
**     - border_left (void*) : Texture de la bordure gauche.
**     - border_right (void*) : Texture de la bordure droite.
**     - exit (void*) : Texture de la sortie.
**     - collect[ANIMATE_COLLECT_IMG] (void*) : Tableau de textures animées
**                                              pour les collectibles.
**
** Note : La structure `s_textures` contient les pointeurs vers les différentes
**        textures utilisées dans le jeu. Chaque champ représente une texture
**        spécifique, telle que le mur, le joueur, le collectible, etc.
**        Le champ `collect` est un tableau de textures animées pour les
**        collectibles, avec une taille définie par la constante
**        `ANIMATE_COLLECT_IMG`.
*/
typedef struct s_textures
{
	void	*wall;
	void	*player;
	void	*colect;
	void	*killer;
	void	*ground;
	void	*corner_top_left;
	void	*corner_top_right;
	void	*corner_bottom_left;
	void	*corner_bottom_right;
	void	*border_top;
	void	*border_bottom;
	void	*border_left;
	void	*border_right;
	void	*exit;
	void	*collect[ANIMATE_COLLECT_IMG];
}			t_textures;

/*
** Structure : s_player
**
** Description : Représente les propriétés du joueur dans le jeu.
**
** Champs :
**     - animation_counter (int) : Compteur d'animation du joueur.
**     - moves_count (int) : Nombre de déplacements effectués par le joueur.
**     - itoa_result (char*) : Résultat de la conversion de l'entier en chaîne
**                             de caractères lors de l'affichage.
**
** Note : La structure `s_player` contient les propriétés spécifiques du joueur
**        dans le jeu. Le champ `animation_counter` est utilisé pour le
**        comptage des animations du joueur. Le champ `moves_count` représente
**        le nombre de déplacements effectués par le joueur. Le champ
**        `itoa_result` est utilisé pour stocker le résultat de la conversion
**        de l'entier en chaîne de caractères lors de l'affichage du nombre de
**        déplacements.
*/
typedef struct s_player
{
	int		animation_counter;
	int		moves_count;
	char	*itoa_result;
}			t_player;

/*
** Structure : s_game
**
** Description : Représente l'état du jeu et ses composants.
**
** Champs :
**     - map (t_map) : Structure contenant les informations sur la carte du
**                     jeu.
**     - textures (t_textures) : Structure contenant les textures utilisées
**                               dans le jeu.
**     - player (t_player) : Structure contenant les propriétés du joueur.
**     - mlx (void*) : Pointeur vers la fenêtre MLX (MiniLibX) utilisée pour
**                     le jeu.
**     - win1 (void*) : Pointeur vers la fenêtre de jeu.
**
** Note : La structure `s_game` est utilisée pour représenter l'état du jeu et
**        ses différents composants. Le champ `map` contient les informations
**        relatives à la carte du jeu. Le champ `textures` stocke les textures
**        utilisées pour le rendu graphique. Le champ `player` contient les
**        propriétés du joueur. Les champs `mlx` et `win1` sont des pointeurs
**        vers la fenêtre MLX (MiniLibX) et la fenêtre de jeu respectivement.
**        Ces champs sont utilisés pour l'initialisation et la gestion de la
**        fenêtre de jeu.
*/
typedef struct s_game
{
	t_map		map;
	t_textures	textures;
	t_player	player;
	void		*mlx;
	void		*win1;
}				t_game;

/*
** Énumération : e_position
**
** Description : Représente les différentes positions possibles.
**
** Valeurs :
**     - CENTER : Position centrale.
**     - TOP_LEFT : Coin supérieur gauche.
**     - TOP_RIGHT : Coin supérieur droit.
**     - BOTTOM_LEFT : Coin inférieur gauche.
**     - BOTTOM_RIGHT : Coin inférieur droit.
**     - TOP : Position en haut.
**     - BOTTOM : Position en bas.
**     - LEFT : Position à gauche.
**     - RIGHT : Position à droite.
**
** Note : L'énumération `e_position` définit les différentes positions
**        possibles dans le contexte du jeu. Chaque valeur représente une
**        position spécifique telle que le centre, les coins, le haut, le
**        bas, la gauche et la droite. Ces positions sont utilisées pour le
**        placement et le positionnement des éléments dans le jeu.
*/
typedef enum e_position
{
	CENTER,
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
}			t_position;

void	initialize_game(t_game *game, char **argv );
void	edit_map(t_game *game, char *path);
int		check_file(t_game *game, char *file);
int		print_error(t_game *game, char *message);
int		check_flood_fill(char *argv, t_game *game);
void	put_error_message(t_game *game, char *message);
void	draw_element(t_game *game, int i, char element, void *texture);
void	draw_border(t_game *game, int i, t_position position);
void	draw_position_texture(t_game *game, int i, void	*texture);
void	free_resources(t_game *game);
int		close_window(void *param);
void	update_game_state(int delta, int key, t_game *game);
void	draw_elements(t_game *game, int i);
void	draw_moves_count(t_game *game);
int		key_press(int key, t_game *game);
int		check_grid(t_game *game, char *file);
int		check_map(t_game *game, char *file);
void	check_images_exist(t_game *game);
void	load_textures(t_game *game);
int		validate_map(t_game *game);
void	update_texture(t_game *game, void **texture, char *filename);
int		loop(t_game *game);
void	initialize_game_textures(t_game *game);
void	initialize_game_corner_textures(t_game *game);
void	initialize_game_border_textures(t_game *game);
void	initialize_game_exit_texture(t_game *game);
void	load_collect_images(t_game *game);
void	draw_position_texture(t_game *game, int i, void	*texture);

#endif

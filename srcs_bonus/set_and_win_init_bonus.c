/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_win_init_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:48:07 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:25:45 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/*
** Description : Cette fonction initialise les fenêtres du jeu en
**               réinitialisant les pointeurs de la bibliothèque minilibx à
**               NULL.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient les pointeurs de
**          fenêtres utilisés par la minilibx.
**
** Cette fonction ne renvoie pas de valeur. Elle initialise les pointeurs de la
** fenêtre principale (mlx) et de la fenêtre de jeu (win1) à NULL.
**
** Remarque : Cette fonction est généralement appelée au début du programme
**            pour s'assurer que les pointeurs de fenêtres sont initialisés à
**            NULL avant d'être utilisés par d'autres fonctions de la minilibx.
*/
static void	initialize_game_window(t_game *game)
{
	game->mlx = NULL;
	game->win1 = NULL;
}

/*
** Fonction : get_sum_columns
**
** Description : Calcule et renvoie le nombre total de colonnes dans la
**               première ligne du fichier correspondant au chemin d'accès
**               donné. Cette fonction suppose que toutes les lignes ont la
**               même longueur.
**
** Arguments :
**     - game (t_game *) : Pointeur sur la structure du jeu. Non utilisé
**                         dans cette fonction, mais inclus pour la
**                         cohérence de l'interface de la fonction.
**     - path (char *) : Le chemin d'accès au fichier pour lequel compter
**                       les colonnes.
**
** Valeur de retour :
**     - (int) : Retourne le nombre total de colonnes dans la première ligne
**               du fichier, ou -1 si le fichier ne peut pas être ouvert.
**
** Effets de bord :
**     - Ouverture et lecture d'un fichier.
**
** Note : Cette fonction suppose que le chemin du fichier est valide. Si le
**        fichier ne peut pas être ouvert pour une quelconque raison, la
**        fonction retournera -1.
*/
int	get_sum_columns(char *path)
{
	int		fd;
	char	c;
	int		sum_columns;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	sum_columns = 0;
	while (read(fd, &c, 1) && c != '\n')
	{
		sum_columns++;
	}
	close(fd);
	return (sum_columns);
}

/*
** Fonction : get_sum_lines
**
** Description : Calcule et renvoie le nombre total de lignes dans le fichier
**               correspondant au chemin d'accès donné.
**
** Arguments :
**     - game (t_game *) : Pointeur sur la structure du jeu. Non utilisé
**                         dans cette fonction, mais inclus pour la
**                         cohérence de l'interface de la fonction.
**     - path (char *) : Le chemin d'accès au fichier pour lequel compter
**                       les lignes.
**
** Valeur de retour :
**     - (int) : Retourne le nombre total de lignes dans le fichier, ou -1
**               si le fichier ne peut pas être ouvert.
**
** Effets de bord :
**     - Ouverture et lecture d'un fichier.
**
** Note : Cette fonction suppose que le chemin du fichier est valide. Si le
**        fichier ne peut pas être ouvert pour une quelconque raison, la
**        fonction retournera -1.
*/
int	get_sum_lines(char *path)
{
	int		fd;
	char	c;
	int		sum_lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	sum_lines = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			sum_lines++;
	}
	close(fd);
	return (sum_lines);
}

/*
** Description : Cette fonction initialise les propriétés du jeu en
**               réinitialisant toutes les variables de la structure du jeu à
**               leurs valeurs par défaut. Cela permet de remettre le jeu dans
**               un état initial avant de commencer une nouvelle partie.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient les différentes
**          propriétés du jeu.
**
** Cette fonction ne renvoie pas de valeur. Elle met à zéro les différentes
** variables de la structure du jeu, réinitialise les compteurs et pointeurs,
** et déclare les pointeurs de la carte à NULL.
**
** Remarque : Cette fonction est généralement appelée au début du programme ou
**            avant de commencer une nouvelle partie pour s'assurer que toutes
**            les propriétés du jeu sont correctement initialisées.
*/
static void	initialize_game_properties(t_game *game, char **argv )
{
	game->map.height = 0;
	game->map.width = 0;
	game->map.player_spot = 0;
	game->map.player_count = 0;
	game->map.exit_spot = 0;
	game->map.exit_count = 0;
	game->map.sum_lines = get_sum_lines(argv[1]);
	game->map.sum_columns = get_sum_columns(argv[1]);
	game->map.colect_count = 0;
	game->map.check_colect_count = 0;
	game->map.check_map = NULL;
	game->map.play_map = NULL;
	game->player.animation_counter = 0;
	game->player.moves_count = 0;
	game->player.itoa_result = NULL;
}

/*
** Description : Cette fonction initialise toutes les propriétés, fenêtres et
**               textures du jeu en appelant les fonctions d'initialisation
**               correspondantes.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient toutes les données
**          et les propriétés nécessaires au bon fonctionnement du jeu.
**
** Cette fonction ne renvoie pas de valeur. Elle appelle séquentiellement les
** fonctions d'initialisation pour mettre en place les propriétés du jeu, les
** fenêtres et les textures nécessaires.
**
** Remarque : Cette fonction est généralement appelée au début du programme ou
**            avant de commencer une nouvelle partie pour initialiser toutes les
**            structures et les ressources du jeu.
*/
void	initialize_game(t_game *game, char **argv )
{
	initialize_game_properties(game, argv);
	initialize_game_window(game);
	initialize_game_textures(game);
	initialize_game_corner_textures(game);
	initialize_game_border_textures(game);
	initialize_game_exit_texture(game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:05:26 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:07:19 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Description : Cette fonction est le cœur de la boucle principale du jeu.
**               Elle est appelée à chaque itération de la boucle et se charge
**               de mettre à jour l'affichage du jeu et de gérer les
**               animations.
**
** Paramètre :
** - game : Un pointeur vers la structure de jeu (t_game) contenant les
**          informations du jeu.
**
** Cette fonction prend en paramètre un pointeur vers la structure de jeu
** 'game'. Elle initialise les variables 'i' à 0 et 'delay_us' à 100000 pour
** contrôler la vitesse d'animation du jeu. Ensuite, elle entre dans une
** boucle qui itère sur chaque élément de la carte du jeu en utilisant les
** variables 'i', 'game->map.sum_lines' et 'game->map.sum_columns'. À chaque
** itération, elle appelle la fonction 'draw_elements' pour dessiner les
** éléments du jeu à leur position respective. Après avoir parcouru tous les
** éléments de la carte, elle incrémente le compteur
** 'game->player.animation_counter' pour
** gérer les animations du joueur. Ensuite, elle appelle la fonction
** 'draw_moves_count' pour afficher le nombre de mouvements effectués par le
** joueur à l'écran. Elle utilise 'mlx_do_sync' pour synchroniser l'affichage
** avec le rendu graphique de la fenêtre du jeu. Enfin, elle utilise 'usleep'
** pour introduire un délai de 'delay_us' microsecondes avant de passer à
** l'itération suivante de la boucle. La fonction retourne 0 à la fin de
** l'exécution.
**
** Remarque : Cette fonction est responsable de la mise à jour de l'affichage
**            et de l'animation du jeu. Elle est appelée à chaque itération de
**            la boucle principale du jeu.
*/
int	loop(t_game *game)
{
	int	i;
	int	delay_us;

	i = 0;
	delay_us = 100000;
	while (i < game->map.sum_lines * game->map.sum_columns)
	{
		draw_elements(game, i);
		i++;
	}
	game->player.animation_counter++;
	draw_moves_count(game);
	mlx_do_sync(game->mlx);
	usleep(delay_us);
	return (0);
}

/*
** Initialise et exécute la boucle de jeu.
**
** Cette fonction est responsable de l'initialisation et de l'exécution de la
** boucle principale du jeu, en utilisant les fonctions fournies par la minilibx.
**
** @param t_game *game - Pointeur vers la structure du jeu contenant toutes les
** informations nécessaires pour exécuter le jeu, telles que le contexte mlx,
** la fenêtre et l'état du jeu.
**
** La fonction enregistre plusieurs gestionnaires d'événements avec minilibx :
** - mlx_loop_hook pour gérer la boucle principale du jeu.
** - mlx_hook pour gérer les événements de pression de touche.
** - mlx_hook pour gérer l'événement de fermeture de la fenêtre.
** Ensuite, elle lance la boucle principale du jeu avec mlx_loop.
*/
static void	run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, loop, game);
	mlx_hook(game->win1, 2, 1L << 0, key_press, game);
	mlx_hook(game->win1, 17, 0L, close_window, game);
	mlx_loop(game->mlx);
}

/*
** Crée une nouvelle fenêtre pour le jeu en utilisant minilibx.
**
** Cette fonction crée une nouvelle fenêtre pour le jeu à l'aide de la fonction
** mlx_new_window de minilibx, en utilisant la largeur et la hauteur calculées
** à partir du nombre de colonnes et de lignes de la carte du jeu,
** respectivement.
**
** @param t_game *game - Pointeur vers la structure du jeu contenant toutes les
** informations nécessaires pour créer la fenêtre, comme le contexte mlx et les
** dimensions de la carte du jeu.
**
** Si la création de la fenêtre échoue (mlx_new_window renvoie NULL), la fonction
** retourne immédiatement.
*/
static void	create_window(t_game *game)
{
	game->win1 = mlx_new_window(game->mlx, game->map.sum_columns
			* game->map.width,
			game->map.sum_lines * game->map.height, "So_long");
	if (game->win1 == NULL)
		return ;
}

/*
** Fonction : check_arg_map
**
** Description : Vérifie les arguments de ligne de commande relatifs à la
**               carte du jeu.
**
** Arguments :
**     - game (t_game *) : Pointeur vers la structure de jeu (t_game).
**     - file (char *) : Chaîne de caractères représentant le fichier de la
**                        carte du jeu.
**
** Retour :
**     - (int) : 1 si les arguments de la carte sont valides, 0 sinon.
**
** Note : La fonction appelle différentes fonctions de vérification pour
**        valider les différents aspects de la carte. Elle utilise la fonction
**        "check_file" pour vérifier l'existence et l'extension du fichier,
**        la fonction "check_grid" pour vérifier si la carte forme une grille
**        régulière, et la fonction "check_map" pour effectuer des vérifications
**        spécifiques sur la carte du jeu en utilisant la structure de jeu
**        (t_game). Si toutes les vérifications réussissent, la fonction renvoie
**        1 pour indiquer que les arguments de la carte sont valides. Sinon, elle
**        renvoie 0.
*/
int	check_arg_map(t_game *game, char *file)
{
	if (check_file(game, file))
		return (1);
	if (check_grid(game, file))
		return (1);
	if (check_map(game, file))
		return (1);
	return (0);
}

/*
** Fonction : main
**
** Description : Fonction principale du programme qui exécute le jeu.
**
** Arguments :
**     - argc (int) : Nombre d'arguments de ligne de commande.
**     - argv (char **) : Tableau de chaînes de caractères contenant les
**                        arguments de ligne de commande.
**
** Note : La fonction vérifie d'abord si le nombre d'arguments est égal à 2.
**        Si c'est le cas, elle initialise la structure de jeu (t_game),
**        édite la carte en utilisant la fonction "edit_map", vérifie la
**        validité de la carte en utilisant la fonction "check_arg_map",
**        initialise la connexion avec la bibliothèque graphique en utilisant
**        "mlx_init", charge les textures en utilisant "load_textures",
**        vérifie la validité des textures en utilisant "check_textures",
**        crée la fenêtre du jeu en utilisant "create_window", exécute le jeu
**        en utilisant "run_game", libère les ressources du jeu en utilisant
**        "free_resources", puis retourne 0 pour indiquer une exécution
**        réussie. Si le nombre d'arguments est différent de 2, la fonction
**        renvoie une erreur indiquant un nombre d'arguments insuffisant.
*/
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		initialize_game(&game, argv);
		edit_map(&game, argv[1]);
		if (check_arg_map(&game, argv[1]))
		{
			close_window(&game);
			exit (1);
		}
		check_images_exist(&game);
		game.mlx = mlx_init();
		if (game.mlx == NULL)
			return (1);
		load_textures(&game);
		create_window(&game);
		run_game(&game);
		free_resources(&game);
		return (0);
	}
	else
		write(2, "Pas assez d'arguments\n", 23);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions_and_game_update.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:15:55 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:08:28 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Gestion des mouvements dans le jeu.
**
** Cette fonction met à jour la texture du joueur, déplace le joueur sur la
** carte et gère la collecte d'objets.
**
** @param t_game *game - Pointeur vers la structure du jeu contenant les
** informations sur la carte, le joueur et les textures.
**
** @param int delta - Déplacement à effectuer par le joueur sur la carte.
**
** @param char *filename - Nom du fichier XPM pour la nouvelle texture du joueur.
**
** Si le joueur se déplace sur un objet, cet objet est collecté, le compteur
** d'objets à collecter est décrémenté. Si tous les objets ont été collectés,
** l'image de la sortie est mise à jour pour indiquer une sortie ouverte.
*/
static void	handle_move(t_game *game, int delta, char *filename)
{
	update_texture(game, &game->textures.player, filename);
	if (game->map.play_map[game->map.player_spot + delta] == 'C')
	{
		game->map.play_map[game->map.player_spot] = '0';
		game->map.colect_count--;
		if (game->map.colect_count == 0)
		{
			mlx_destroy_image(game->mlx, game->textures.exit);
			game->textures.exit = mlx_xpm_file_to_image(game->mlx,
					"xpm/exit_open.xpm", &game->map.width, &game->map.height);
		}
	}
	else
		game->map.play_map[game->map.player_spot] = '0';
	game->map.play_map[game->map.player_spot + delta] = 'P';
}

/*
** Gestion de la sortie fermée dans le jeu.
**
** Cette fonction vérifie s'il reste des objets à collecter sur la carte.
** Si c'est le cas, la fonction retourne immédiatement sans rien faire.
**
** @param t_game *game - Pointeur vers la structure de jeu contenant entre
** autres l'état de la carte et le compteur de mouvements du joueur.
**
** Si tous les objets ont été collectés, le compteur de mouvements du joueur
** est incrémenté, et la fonction close_window est appelée pour fermer la
** fenêtre du jeu.
*/
static void	handle_closed_exit(t_game *game)
{
	if (game->map.colect_count > 0)
	{
		return ;
	}
	game->player.moves_count++;
	close_window(game);
}

/*
** Description : Cette fonction est appelée lorsque le joueur meurt dans le
**               jeu. Elle est responsable de la gestion des actions à
**               effectuer lorsqu'une collision mortelle se produit. Elle met
**               à jour la position du joueur sur la carte, redessine les
**               textures correspondantes, exécute une boucle de jeu
**               supplémentaire pour afficher l'état mis à jour, introduit un
**               délai de 200000 microsecondes pour afficher l'animation de
**               mort, puis ferme la fenêtre du jeu.
**
** Paramètres :
** - game : Un pointeur vers la structure de jeu (t_game) contenant les
**          informations du jeu.
** - shift : Le décalage à appliquer à la position du joueur sur la carte pour
**           indiquer sa nouvelle position après la collision mortelle.
**
** Cette fonction prend en paramètre un pointeur vers la structure de jeu
** 'game' et un entier 'shift' qui représente le décalage à appliquer à la
** position du joueur sur la carte. Elle utilise la variable 'old_player_spot'
** pour stocker l'ancienne position du joueur sur la carte. Ensuite, elle met
** à jour la position du joueur en ajoutant 'shift' à la position actuelle sur
** la carte. Elle modifie les éléments correspondants sur la carte en remplaçant
** l'ancienne position du joueur par le symbole '0' pour le sol et en mettant
** à jour la nouvelle position du joueur avec le symbole 'P'. Elle utilise la
** fonction 'draw_position_texture' pour redessiner la texture du sol à
** l'ancienne position du joueur. Ensuite, elle détruit l'image de la texture
** actuelle du joueur avec 'mlx_destroy_image' et charge une nouvelle image
** pour représenter l'animation de mort avec 'mlx_xpm_file_to_image'. Elle
** exécute ensuite une boucle de jeu supplémentaire en appelant 'loop' pour
** afficher l'état mis à jour du jeu.
** Après un délai de 200000 microsecondes (0.2 seconde), elle ferme la fenêtre
** du jeu en appelant 'close_window'.
**
** Remarque : Cette fonction est responsable de la gestion de la mort du
**            joueur, de l'affichage de l'animation de mort et de la fermeture
**            de la fenêtre du jeu.
*/
void	player_dies(t_game *game, int shift)
{
	int	old_player_spot;

	old_player_spot = game->map.player_spot;
	game->map.player_spot += shift;
	game->map.play_map[old_player_spot] = '0';
	game->map.play_map[game->map.player_spot] = 'P';
	draw_position_texture(game, old_player_spot, game->textures.ground);
	mlx_destroy_image(game->mlx, game->textures.player);
	game->textures.player = mlx_xpm_file_to_image(game->mlx,
			"xpm/player_dies.xpm",
			&game->map.width, &game->map.height);
	loop(game);
	usleep(200000);
	close_window(game);
}

/*
** Récupère la texture du joueur en fonction de la direction de mouvement.
**
** Cette fonction renvoie le nom du fichier XPM correspondant à la texture
** du joueur en fonction de la touche pressée.
**
** @param int key - La touche pressée par l'utilisateur.
**
** Les touches possibles sont : KEY_DOWN (retourne "player_down.xpm"),
** KEY_UP (retourne "player_up.xpm"), KEY_RIGHT (retourne "player_right.xpm"),
** et toute autre touche retourne "player_left.xpm".
*/
static char	*get_player_texture(int key)
{
	if (key == KEY_DOWN)
		return ("xpm/player_down.xpm");
	else if (key == KEY_UP)
		return ("xpm/player_up.xpm");
	else if (key == KEY_RIGHT)
		return ("xpm/player_right.xpm");
	else
		return ("xpm/player_left.xpm");
}

/*
** Met à jour l'état du jeu après un mouvement du joueur.
**
** Cette fonction est appelée après qu'un mouvement du joueur ait été déterminé.
** Elle gère les différentes interactions possibles avec la cellule cible :
** rencontre avec 'K' (joueur meurt), 'E' (sortie fermée) et déplacement
** normal (autre cas).
**
** @param int delta - Le déplacement du joueur.
**
** @param int key - La touche pressée par l'utilisateur.
**
** @param t_game *game - Pointeur vers la structure du jeu contenant entre
** autres les informations sur la carte et la position du joueur.
**
** La fonction gère les interactions en fonction du type de cellule cible,
** met à jour le nombre de mouvements du joueur et gère les déplacements
** du joueur.
*/
void	update_game_state(int delta, int key, t_game *game)
{
	char	future_cell;
	char	*player_texture;

	future_cell = game->map.play_map[game->map.player_spot + delta];
	player_texture = get_player_texture(key);
	if (future_cell == 'K')
	{
		game->player.moves_count++;
		player_dies(game, delta);
	}
	else if (future_cell == 'E')
		handle_closed_exit(game);
	else
	{
		handle_move(game, delta, player_texture);
		game->map.play_map[game->map.player_spot] = '0';
		game->map.player_spot += delta;
		game->player.moves_count++;
	}
}

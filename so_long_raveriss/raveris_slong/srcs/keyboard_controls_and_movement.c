/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_controls_and_movement.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:22:16 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 11:31:09 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Déplace le joueur en fonction de la touche pressée.
**
** Cette fonction prend en entrée une touche et un pointeur vers l'état du jeu,
** et retourne le delta de déplacement du joueur sur la carte en fonction de
** la touche pressée.
**
** @param int key - La touche pressée par l'utilisateur.
**
** @param t_game *game - Pointeur vers la structure de jeu contenant entre
** autres les informations sur la carte et la position du joueur.
**
** Les déplacements possibles sont : vers le bas (touche vers le bas), vers
** le haut (touche vers le haut), vers la droite (touche vers la droite) et
** vers la gauche (touche vers la gauche), en respectant les limites de la carte.
** Si aucune de ces touches n'est pressée, aucun déplacement n'est effectué.
*/
static int	move_player(int key, t_game *game)
{
	if (key == KEY_DOWN)
		return (game->map.sum_columns);
	else if (key == KEY_UP)
		return (-(game->map.sum_columns));
	else if (key == KEY_RIGHT
		&& game->map.player_spot
		% game->map.sum_columns < game->map.sum_columns - 1)
		return (1);
	else if (key == KEY_LEFT && game->map.player_spot
		% game->map.sum_columns > 0)
		return (-1);
	return (0);
}

/*
** Vérifie si le joueur peut se déplacer dans la direction souhaitée.
**
** Cette fonction détermine si un mouvement dans la direction indiquée par la
** touche pressée est possible sans heurter un obstacle ('1' sur la carte).
**
** @param int key - La touche pressée par l'utilisateur.
**
** @param t_game *game - Pointeur vers la structure de jeu contenant entre
** autres les informations sur la carte et la position du joueur.
**
** Le mouvement est possible si la case cible n'est pas un obstacle.
** La fonction retourne 1 si le mouvement est possible, et 0 sinon.
*/
int	can_move(int key, t_game *game)
{
	int	can_move;
	int	new_spot;

	can_move = 0;
	new_spot = game->map.player_spot;
	if (key == KEY_DOWN)
		new_spot += game->map.sum_columns;
	else if (key == KEY_UP)
		new_spot -= game->map.sum_columns;
	else if (key == KEY_RIGHT && game->map.player_spot
		% game->map.sum_columns < game->map.sum_columns - 1)
		new_spot += 1;
	else if (key == KEY_LEFT && game->map.player_spot
		% game->map.sum_columns > 0)
		new_spot -= 1;
	if (game->map.play_map[new_spot] != '1')
		can_move = 1;
	return (can_move);
}

/*
** Gère les actions basées sur la touche pressée par l'utilisateur.
**
** Cette fonction traite les différentes actions possibles selon la touche
** pressée : KEY_ESCAPE ferme la fenêtre et quitte le programme, toutes les
** autres touches sont traitées pour tenter de déplacer le joueur.
**
** @param int key - La touche pressée par l'utilisateur.
**
** @param t_game *game - Pointeur vers la structure du jeu contenant entre
** autres les informations sur la carte et la position du joueur.
**
** @param int *delta - Pointeur vers la variable dans laquelle la fonction
** stocke le déplacement du joueur, s'il est possible.
**
** Si le mouvement est possible (déterminé par la fonction can_move), la
** fonction move_player est appelée pour déterminer le déplacement du joueur
** et le stocke dans delta.
*/
void	handle_key(int key, t_game *game, int *delta)
{
	if (key == KEY_ESCAPE)
	{
		close_window(game);
		exit(0);
	}
	else if (can_move(key, game))
		*delta = move_player(key, game);
}

/*
** Gère les événements de pression de touches dans le jeu.
**
** Cette fonction est un gestionnaire d'événements pour la pression de touche.
** Elle détermine si le mouvement du joueur est possible et, le cas échéant,
** met à jour l'état du jeu en fonction du mouvement.
**
** @param int key - La touche pressée par l'utilisateur.
**
** @param t_game *game - Pointeur vers la structure du jeu contenant entre
** autres les informations sur la carte et la position du joueur.
**
** Lorsqu'une touche est pressée, la fonction détermine le déplacement
** correspondant (s'il y en a un) et met à jour l'état du jeu en conséquence.
** La fonction retourne toujours 0, conformément aux spécifications de la
** fonction de rappel MLX.
*/
int	key_press(int key, t_game *game)
{
	int	delta;

	delta = 0;
	handle_key(key, game, &delta);
	if (delta != 0)
		update_game_state(delta, key, game);
	return (0);
}

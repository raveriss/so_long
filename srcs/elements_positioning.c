/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_positioning.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:09:38 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 11:30:55 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/*
** Description : Cette fonction détermine la position inférieure d'un objet
**               dans le jeu en fonction de son index. Elle utilise la
**               structure du jeu et l'index de la carte pour déterminer cette
**               position.
**
** Paramètres :
** - game : Pointeur vers la structure du jeu, qui contient la carte et
**          d'autres informations de jeu.
** - i    : Index de l'objet sur la carte.
**
** Retour :
** - BOTTOM_LEFT  : si l'index est égal à la première position de la dernière
**                  ligne (bas gauche), indiquant que l'objet est dans le coin
**                  inférieur gauche.
** - BOTTOM_RIGHT : si l'index est égal à la dernière position de la dernière
**                  ligne (bas droite), indiquant que l'objet est dans le coin
**                  inférieur droit.
** - BOTTOM       : dans tous les autres cas, indiquant que l'objet est
**                  ailleurs sur la ligne inférieure.
*/
t_position	get_bottom_position(t_game *game, int i)
{
	int	bottom_left;

	bottom_left = game->map.sum_columns * (game->map.sum_lines - 1);
	if (i == bottom_left)
		return (BOTTOM_LEFT);
	if (i == bottom_left + game->map.sum_columns - 1)
		return (BOTTOM_RIGHT);
	return (BOTTOM);
}

/*
** Description : Cette fonction détermine la position médiane d'un objet dans
**               le jeu en fonction de son index. Elle utilise la structure du
**               jeu et l'index de la carte pour déterminer cette position.
**
** Paramètres :
** - game : Pointeur vers la structure du jeu, qui contient la carte et
**          d'autres informations de jeu.
** - i    : Index de l'objet sur la carte.
**
** Retour :
** - LEFT   : si l'index modulé par le nombre de colonnes est égal à 0, ce qui
**            indique que l'objet est situé sur le côté gauche.
** - RIGHT  : si l'index modulé par le nombre de colonnes est égal au nombre de
**            colonnes moins 1, ce qui indique que l'objet est sur le côté
**            droit.
** - CENTER : dans tous les autres cas, indiquant que l'objet est dans la
**            partie médiane de la carte.
*/
t_position	get_middle_position(t_game *game, int i)
{
	if (i % game->map.sum_columns == 0)
		return (LEFT);
	if (i % game->map.sum_columns == game->map.sum_columns - 1)
		return (RIGHT);
	return (CENTER);
}

/*
** Description : Cette fonction détermine la position supérieure d'un objet
**               dans le jeu basé sur son index. Elle utilise la structure du
**               jeu et l'index de la carte pour déterminer la position.
**
** Paramètres :
** - game : Pointeur vers la structure du jeu, qui contient la carte et
**          d'autres informations de jeu.
** - i    : Index de l'objet sur la carte.
**
** Retour :
** - TOP_LEFT  : si l'index est 0, indiquant que l'objet est dans le coin
**               supérieur gauche.
** - TOP_RIGHT : si l'index est égal au nombre de colonnes moins 1, indiquant
**               que l'objet est dans le coin supérieur droit.
** - TOP       : dans tous les autres cas, indiquant que l'objet est ailleurs
**               sur la ligne supérieure.
*/
t_position	get_top_position(t_game *game, int i)
{
	if (i == 0)
		return (TOP_LEFT);
	if (i == game->map.sum_columns - 1)
		return (TOP_RIGHT);
	return (TOP);
}

/*
** Description : Cette fonction détermine la position d'un objet dans le jeu en
**               fonction de son index. Elle utilise la structure du jeu et
**               l'index de la carte pour déterminer cette position, appelant
**               d'autres fonctions pour déterminer la position spécifique.
**
** Paramètres :
** - game : Pointeur vers la structure du jeu, qui contient la carte et
**          d'autres informations de jeu.
** - i    : Index de l'objet sur la carte.
**
** Retour :
** - get_top_position     : si l'index est inférieur au nombre de colonnes, ce
**                          qui indique que l'objet est sur la ligne du haut.
** - get_bottom_position  : si l'index est supérieur ou égal à la première
**                          position de la dernière ligne, indiquant que
**                          l'objet est sur la ligne du bas.
** - get_middle_position  : dans tous les autres cas, indiquant que l'objet
**                          est sur une ligne médiane de la carte.
*/
t_position	get_position(t_game *game, int i)
{
	if (i < game->map.sum_columns)
		return (get_top_position(game, i));
	if (i >= game->map.sum_columns * (game->map.sum_lines - 1))
		return (get_bottom_position(game, i));
	return (get_middle_position(game, i));
}

/*
** Description : La fonction draw_elements est utilisée pour dessiner les
**               différents éléments du jeu à une position spécifique de la
**               carte.
**
** Paramètres :
** - game : Pointeur vers la structure du jeu, qui contient les informations
**          de la fenêtre, de la carte et des autres données du jeu.
** - i    : Index de la position sur la carte où les éléments doivent être
**          dessinés.
**
** Cette fonction ne renvoie pas de valeur. Elle commence par récupérer la
** position sur la carte correspondant à l'index i, puis dessine les éléments
** du jeu (joueur, sortie, ennemi, pomme) si leur représentation caractère
** correspond à la position i sur la carte.
**
** Si la position i correspond à un mur ('1'), la fonction dessine également la
** bordure et le mur lui-même si la position est au centre de la carte.
**
** Si la position i correspond à du terrain libre ('0'), la fonction dessine
** simplement le sol.
**
** Remarque : L'index i doit correspondre à une position valide sur la carte.
*/
void	draw_elements(t_game *game, int i)
{
	t_position	position;

	position = get_position(game, i);
	draw_element(game, i, 'P', game->textures.player);
	draw_element(game, i, 'E', game->textures.exit);
	draw_element(game, i, 'K', game->textures.killer);
	draw_element(game, i, 'C', game->textures.collect[
		game->player.animation_counter % ANIMATE_COLLECT_IMG]);
	if (game->map.play_map[i] == '1')
	{
		draw_border(game, i, position);
		if (position == CENTER)
			draw_position_texture(game, i, game->textures.wall);
	}
	else if (game->map.play_map[i] == '0')
		draw_position_texture(game, i, game->textures.ground);
}

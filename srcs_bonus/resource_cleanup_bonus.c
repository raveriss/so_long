/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_cleanup_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:29:06 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:25:43 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/*
** Description : Cette fonction libère les ressources des textures utilisées
**               par le jeu, en détruisant les images correspondantes et en
**               libérant la mémoire allouée.
**
** Paramètres :
** - game : Pointeur vers la structure du jeu, qui contient les pointeurs des
**          textures.
** - texture_index : Indice de la texture à libérer (commence par la valeur 13
**                   pour la dernière texture et décroît jusqu'à 0).
**
** Cette fonction ne renvoie pas de valeur. Elle libère récursivement les
** textures du jeu en utilisant un tableau de pointeurs pour accéder aux
** textures. Elle détruit les images correspondantes à l'aide de la fonction
** mlx_destroy_image() de la minilibx, puis appelle récursivement la fonction
** en diminuant l'indice de texture jusqu'à ce que toutes les textures soient
** libérées.
**
** Remarque : Cette fonction est généralement appelée à la fin du programme ou
**            lorsque les textures ne sont plus nécessaires, afin de libérer
**            la mémoire occupée par les images et de prévenir les fuites de
**            mémoire.
*/
static void	free_textures(t_game *game, int texture_index)
{
	void	*textures[14];

	textures[0] = game->textures.wall;
	textures[1] = game->textures.player;
	textures[2] = game->textures.colect;
	textures[3] = game->textures.killer;
	textures[4] = game->textures.ground;
	textures[5] = game->textures.corner_top_left;
	textures[6] = game->textures.corner_top_right;
	textures[7] = game->textures.corner_bottom_left;
	textures[8] = game->textures.corner_bottom_right;
	textures[9] = game->textures.border_top;
	textures[10] = game->textures.border_bottom;
	textures[11] = game->textures.border_left;
	textures[12] = game->textures.border_right;
	textures[13] = game->textures.exit;
	if (texture_index < 0)
		return ;
	if (textures[texture_index])
		mlx_destroy_image(game->mlx, textures[texture_index]);
	free_textures(game, texture_index - 1);
}

/*
** Description : Cette fonction libère les ressources des images des pommes
**               utilisées par le jeu, en détruisant les images
**               correspondantes et en libérant la mémoire allouée.
**
** Paramètres :
** - game : Pointeur vers la structure du jeu, qui contient les pointeurs des
**          images des pommes.
** - index : Indice de l'image de pomme à libérer (commence par la valeur la
**           plus élevée et décroît jusqu'à 0).
**
** Cette fonction ne renvoie pas de valeur. Elle libère récursivement les
** images des pommes en utilisant la fonction mlx_destroy_image() de la
** minilibx pour détruire les images correspondantes. La fonction est appelée
** de manière récursive en diminuant l'indice de l'image de pomme jusqu'à ce
** que toutes les images soient libérées.
**
** Remarque : Cette fonction est généralement appelée à la fin du programme ou
**            lorsque les images de pommes ne sont plus nécessaires, afin de
**            libérer la mémoire occupée par les images et de prévenir les
**            fuites de mémoire.
*/
static void	free_collect_imgs(t_game *game, int index)
{
	if (index < 0)
		return ;
	if (game->textures.collect[index])
		mlx_destroy_image(game->mlx, game->textures.collect[index]);
	free_collect_imgs(game, index - 1);
}

/*
** Description : Cette fonction libère les ressources de la fenêtre principale
**               du jeu ainsi que l'affichage associé en détruisant la fenêtre
**               et l'affichage.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient le pointeur de la
**          fenêtre principale et le contexte d'affichage.
**
** Cette fonction ne renvoie pas de valeur. Elle vérifie d'abord si la fenêtre
** principale existe (non NULL) et, le cas échéant, détruit la fenêtre en
** utilisant la fonction mlx_destroy_window() de la minilibx. Ensuite, elle
** détruit l'affichage en utilisant la fonction mlx_destroy_display(). Ces
** étapes permettent de libérer les ressources allouées pour la fenêtre et
** l'affichage du jeu.
**
** Remarque : Cette fonction est généralement appelée à la fin du programme
**            pour libérer la fenêtre et l'affichage avant de quitter le
**            programme. Cela permet de prévenir les fuites de mémoire et de
**            fermer proprement la fenêtre du jeu.
*/
static void	free_win1_and_display(t_game *game)
{
	if (game->win1)
		mlx_destroy_window(game->mlx, game->win1);
	mlx_destroy_display(game->mlx);
}

/*
** Description : Cette fonction libère toutes les ressources utilisées par le
**               jeu, y compris la mémoire allouée pour la carte, les
**               textures, les images des pommes, la fenêtre et l'affichage.
**
** Paramètre :
** - game : Pointeur vers la structure du jeu, qui contient toutes les
**          ressources à libérer.
**
** Cette fonction ne renvoie pas de valeur. Elle vérifie d'abord si le
** pointeur de la minilibx (game->mlx) est valide. Si ce n'est pas le cas, la
** fonction se termine immédiatement. Sinon, elle libère la mémoire allouée
** pour la carte (game->map.play_map) en utilisant la fonction free(), puis
** appelle les fonctions free_textures() et free_collect_imgs() pour libérer
** les textures et les images des pommes respectivement.Ensuite, elle appelle
** la fonction free_win1_and_display() pour libérer la fenêtre et l'affichage.
** Enfin, elle libère le pointeur de la minilibx (game->mlx) lui-même en
**utilisant la fonction free().
**
** Remarque : Cette fonction est généralement appelée à la fin du programme ou
**            lorsque toutes les ressources du jeu ne sont plus nécessaires,
**            afin de libérer la mémoire occupée et de prévenir les fuites de
**            mémoire.
*/
void	free_resources(t_game *game)
{
	if (game->map.play_map)
		free(game->map.play_map);
	if (game->map.check_map)
		free(game->map.check_map);
	if (!game->mlx)
		return ;
	free_textures(game, 13);
	free_collect_imgs(game, ANIMATE_COLLECT_IMG - 1);
	free_win1_and_display(game);
	free(game->mlx);
}

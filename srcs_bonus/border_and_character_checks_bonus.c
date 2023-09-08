/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_and_character_checks_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:38:57 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:24:58 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/*
** Fonction : update_counts
**
** Description : Met à jour les compteurs pour les objets de jeu 'Exit',
**               'Collectible' et 'Player' dans la structure de jeu.
**
** Arguments :
**     - game (t_game *) : Pointeur sur la structure du jeu dont les
**                         compteurs doivent être mis à jour.
**     - c (char) : Le caractère représentant l'objet de jeu pour lequel
**                  le compteur doit être incrémenté. 'E' pour 'Exit',
**                  'C' pour 'Collectible', 'P' pour 'Player'.
**
** Valeur de retour : Aucune
**
** Effets de bord :
**     - Modifie les valeurs des compteurs correspondants dans la structure
**       de jeu.
**
** Note : Cette fonction suppose que le caractère entré est valide et
**        correspond à un objet de jeu. Aucune vérification d'erreur n'est
**        effectuée.
*/
void	update_counts(t_game *game, char c)
{
	if (c == 'E')
		game->map.exit_count++;
	else if (c == 'C')
		game->map.check_colect_count++;
	else if (c == 'P')
		game->map.player_count++;
}

/*
** Fonction : is_character_count_valid
**
** Description : Vérifie que le nombre d'objets 'Exit', 'Collectible' et
**               'Player' dans la carte du jeu est valide. Pour être valide,
**               il doit y avoir exactement un 'Exit' et un 'Player', et au
**               moins un 'Collectible'.
**
** Arguments :
**     - path (char *) : Le chemin vers le fichier qui contient la carte du jeu.
**     - game (t_game *) : Pointeur sur la structure du jeu où les compteurs
**                         d'objets seront mis à jour.
**
** Valeur de retour :
**     - (int) : Retourne 1 si les comptes d'objets sont valides, sinon 0.
**
** Effets de bord :
**     - Modifie les valeurs des compteurs dans la structure de jeu.
**     - Ouverture et lecture d'un fichier.
**
** Note : Cette fonction suppose que le chemin du fichier est valide. Si le
**        fichier ne peut pas être ouvert pour une quelconque raison, la
**        fonction retournera 0.
*/
int	is_character_count_valid(char *path, t_game *game)
{
	int		fd;
	char	c;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	while (read(fd, &c, 1))
	{
		update_counts(game, c);
	}
	close(fd);
	if (game->map.exit_count == 1
		&& game->map.check_colect_count >= 1
		&& game->map.player_count == 1)
		return (1);
	else
		return (0);
}

/*
** Fonction : check_border_ones
**
** Description : Vérifie que les bords du plateau de jeu sont bien
**               composés de '1', comme prévu pour le jeu So Long. Le
**               plateau de jeu est représenté par une matrice linéaire.
**
** Arguments :
**     - game (t_game *) : Pointeur sur la structure du jeu, contenant
**                         entre autres le plateau de jeu à vérifier.
**
** Valeur de retour :
**     - (int) : Renvoie 1 si les bords sont correctement formés de '1',
**               renvoie 0 sinon. En cas d'échec, un message "erreur de
**               map" est affiché sur la sortie standard.
**
** Effets de bord :
**     - Affichage d'un message en cas d'erreur.
**
** Note : Cette fonction suppose que les dimensions du plateau sont
**        correctes. Si ce n'est pas le cas, le comportement est
**        indéfini.
*/
int	check_border_ones(t_game *game)
{
	int	i;
	int	repeat_value;

	i = 0;
	repeat_value = game->map.sum_lines - 2;
	while (i < game->map.sum_columns)
	{
		if (game->map.play_map[i++] != '1')
			return (0);
	}
	while (repeat_value > 0)
	{
		if (game->map.play_map[i] != '1'
			|| game->map.play_map[i + game->map.sum_columns - 1] != '1')
			return (0);
		i = i + game->map.sum_columns;
		repeat_value--;
	}
	while (game->map.play_map[i] != '\0')
	{
		if (game->map.play_map[i++] != '1')
			return (0);
	}
	return (1);
}

/*
** Fonction : check_map
**
** Description : Vérifie la validité de la carte du jeu.
**
** Arguments :
**     - game (t_game *) : Pointeur vers la structure de jeu (t_game).
**     - file (char *) : Chaîne de caractères représentant le fichier de la
**                        carte du jeu.
**
** Retour :
**     - (int) : 0 si la carte est valide, sinon une valeur d'erreur
**               correspondante est renvoyée.
**
** Note : La fonction effectue différentes vérifications sur la carte du jeu
**        en utilisant d'autres fonctions de validation. Elle vérifie si les
**        bords de la carte sont cocheck_maprectement entourés de murs en
**        appelant la fonction "check_border_ones". Ensuite, elle vérifie si
**        le nombre de caractères de la carte est valide en appelant la
**        fonction "is_character_count_valid". Enfin, elle effectue un
**        remplissage par inondation sur la carte en appelant la fonction
**        "check_flood_fill" pour vérifier si la carte est jouable jusqu'à la
**        sortie. Si toutes les vérifications réussissent, la fonction renvoie
**        0 pour indiquer que la carte est valide. Sinon, elle renvoie une
**        valeur d'erreur correspondante qui est imprimée via la fonction
**        "print_error".
*/
int	check_map(t_game *game, char *file)
{
	if (!check_border_ones(game))
		return (print_error(game, ERR_MAP_NOT_SURROUNDED));
	if (!is_character_count_valid(file, game))
		return (print_error(game, ERR_INVALID_MAP_ENTITIES));
	if (!check_flood_fill(file, game))
		return (print_error(game, ERR_UNWINNABLE));
	return (0);
}

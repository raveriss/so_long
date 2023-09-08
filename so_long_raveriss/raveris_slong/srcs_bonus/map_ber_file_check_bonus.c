/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ber_file_check_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:01:19 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:25:31 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/*
** Fonction : is_valid_character
**
** Description : Vérifie si un caractère donné est valide en le comparant
**               avec une liste prédéfinie de caractères valides.
**
** Arguments :
**     - c (char) : Le caractère à vérifier.
**
** Valeur de retour :
**     - (int) : 1 si le caractère est valide, 0 sinon.
**
** Note : Cette fonction suppose l'existence d'une liste prédéfinie
**        `VALID_CHARACTERS` contenant les caractères considérés comme
**        valides. Assurez-vous que cette liste est correctement définie
**        avant d'utiliser cette fonction.
*/
int	is_valid_character(char c)
{
	int	i;

	i = 0;
	while (VALID_CHARACTERS[i] != '\0')
	{
		if (c == VALID_CHARACTERS[i])
			return (1);
		i++;
	}
	return (0);
}

/*
** Fonction : check_valid_characters
**
** Description : Vérifie si tous les caractères du fichier spécifié sont
**               valides en utilisant la fonction is_valid_character. La
**               validité de chaque caractère est vérifiée séquentiellement.
**
** Arguments :
**     - path (char *) : Chemin vers le fichier à vérifier.
**
** Valeur de retour :
**     - (int) : 1 si tous les caractères du fichier sont valides,
**               0 si au moins un caractère est invalide, ou si le fichier
**               ne peut pas être ouvert.
**
** Note : Cette fonction suppose que la fonction is_valid_character est
**        correctement définie et prête à être utilisée. Elle gère la
**        fermeture du fichier en cas d'erreur ou à la fin de la lecture.
*/
int	check_valid_characters(char *path)
{
	int		fd;
	char	buf;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	while (read(fd, &buf, 1))
	{
		if (!is_valid_character(buf))
		{
			close(fd);
			return (0);
		}
	}
	close(fd);
	return (1);
}

/*
** Fonction : check_file_extension
**
** Description : Vérifie si le chemin du fichier spécifié a une extension
**               valide. Cette fonction vérifie si l'extension est ".ber"
**               en comparant les derniers caractères du chemin.
**
** Arguments :
**     - path (char *) : Chemin vers le fichier à vérifier.
**
** Valeur de retour :
**     - (int) : 1 si le chemin du fichier a une extension valide (".ber"),
**               0 sinon.
**
** Note : Cette fonction suppose que le chemin du fichier est une chaîne
**        de caractères terminée par un caractère nul ('\0'). Elle ne
**        vérifie pas si le fichier existe réellement, uniquement si son
**        extension est correcte.
*/
int	check_file_extension(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i < 4 || path[i - 4] != '.' || path[i - 3] != 'b'
		|| path[i - 2] != 'e' || path[i - 1] != 'r')
		return (0);
	return (1);
}

/*
** Fonction : is_readable
** ---------------------
** Vérifie si un fichier est lisible.
**
** path : Le chemin vers le fichier à vérifier.
**
** Cette fonction tente d'ouvrir un fichier en mode lecture seule. Si
** l'ouverture réussit, cela signifie que le fichier est lisible et la fonction
** ferme alors le fichier et renvoie 1. Si l'ouverture échoue (par exemple, si
** le fichier n'existe pas ou si les permissions de lecture ne sont pas
** accordées), la fonction renvoie 0.
**
** Il est important de noter que cette fonction vérifie uniquement si le
** fichier est lisible au moment de l'appel. Les permissions du fichier peuvent
** changer ultérieurement, et cette fonction n'offre aucune garantie contre de
** telles modifications.
**
** Retourne : 1 si le fichier est lisible, 0 sinon.
*/
int	is_readable(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

/*
** Fonction : check_file
**
** Description : Vérifie la validité du fichier de la carte du jeu.
**
** Arguments :
**     - file (char *) : Chaîne de caractères représentant le nom du fichier
**                        de la carte du jeu.
**
** Retour :
**     - (int) : 0 si le fichier est valide, sinon une valeur d'erreur
**               correspondante est renvoyée.
**
** Note : La fonction `check_file` effectue plusieurs vérifications sur le
**        fichier de la carte du jeu. Elle utilise les fonctions auxiliaires
**        `is_readable`, `check_file_extension` et `check_valid_characters`
**        pour effectuer ces vérifications.
**
**        La première vérification consiste à vérifier si le fichier est
**        lisible en utilisant la fonction `is_readable`. Si le fichier n'est
**        pas lisible, la fonction renvoie une valeur d'erreur correspondante
**        qui est imprimée via la fonction `print_error`.
**
**        Ensuite, la fonction vérifie si l'extension du fichier est valide
**        en utilisant la fonction `check_file_extension`. Si l'extension n'est
**        pas valide, une valeur d'erreur correspondante est renvoyée et
**        imprimée via la fonction `print_error`.
**
**        Enfin, la fonction vérifie si le contenu du fichier contient des
**        caractères valides en utilisant la fonction `check_valid_characters`.
**        Si des caractères invalides sont détectés, une valeur d'erreur
**        correspondante est renvoyée et imprimée via la fonction `print_error`.
**
**        Si toutes les vérifications sont réussies, la fonction renvoie 0
**        pour indiquer que le fichier est valide.
*/
int	check_file(t_game *game, char *file)
{
	if (!is_readable(file))
		return (print_error(game, ERR_FILE_UNREADABLE));
	if (!check_file_extension(file))
		return (print_error(game, ERR_INVALID_EXTENSION));
	if (!check_valid_characters(file))
		return (print_error(game, ERR_INVALID_CHARS_IN_FILE));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit_handler_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:24:53 by raveriss          #+#    #+#             */
/*   Updated: 2023/05/31 14:25:15 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/*
** Description : Cette fonction est utilisée comme rappel (callback) lorsqu'une
**               demande de fermeture de la fenêtre est effectuée. Elle libère
**               toutes les ressources du jeu en appelant la fonction
**               free_resources() puis termine le programme en appelant la
**               fonction exit().
**
** Paramètre :
** - param : Pointeur générique vers les données du jeu (typiquement un
**           pointeur vers la structure t_game).
**
** Renvoie : La valeur 0 (int).
**
** Cette fonction est un rappel (callback) utilisé avec la minilibx pour gérer
** la fermeture de la fenêtre. Elle est appelée lorsque l'utilisateur demande
** la fermeture de la fenêtre.La fonction commence par convertir le paramètre
** générique (void *) en un pointeur vers la structure t_game (t_game *) afin
** d'accéder aux données du jeu. Ensuite, elle appelle la fonction
** free_resources() pour libérer toutes les ressources du jeu, puis termine le
** programme en appelant la fonction exit() avec le code de sortie 0.
**
** Remarque : Cette fonction est généralement utilisée avec la fonction
**            mlx_hook() pour détecter la demande de fermeture de la fenêtre
**            et effectuer les opérations nécessaires avant de quitter
**            proprement le programme.
*/
int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_resources(game);
	exit(0);
}

/*
** Fonction : print_error
**
** Description : Affiche un message d'erreur sur le flux d'erreur standard.
**
** Argument :
**     - message (char *) : Le message d'erreur à afficher.
**
** Valeur de retour :
**     - Toujours 0 : Ce choix a été fait pour permettre l'utilisation de la
**       fonction dans des expressions conditionnelles, comme par exemple dans
**       le cas d'une erreur lors d'une allocation mémoire.
**
** Effet de bord :
**     - Cette fonction écrit sur STDERR_FILENO, ce qui signifie que le
**       message sera visible dans la console, mais ne sera pas renvoyé à la
**       ligne suivante de code qui s'exécute.
*/
int	print_error(t_game *game, char *message)
{
	size_t	len;

	len = 0;
	while (message[len] != '\0')
		len++;
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, message, len);
	close_window(game);
	exit (1);
}

/*
** Fonction : put_error_message
**
** Description : Affiche un message d'erreur spécifique sur le flux d'erreur
**               standard, puis termine le programme.
**
** Argument :
**     - message (char *) : Information supplémentaire à afficher après le
**                          message d'erreur prédéfini.
**
** Valeur de retour :
**     - Aucune. Cette fonction utilise exit() pour terminer le programme en
**       cas d'erreur.
**
** Effet de bord :
**     - Cette fonction écrit sur STDERR_FILENO (2), donc le message sera
**       visible dans la console.
**     - Cette fonction termine le programme avec un statut d'échec
**       (EXIT_FAILURE),
**       indépendamment de l'endroit où elle est appelée.
**     - Le message d'erreur prédéfini est "Failed to load collect image: ".
*/
void	put_error_message(t_game *game, char *message)
{
	char	*error_message;
	int		i;

	error_message = "Error\nFailed to load collect image: ";
	i = 0;
	while (error_message[i] != '\0')
	{
		write(2, &error_message[i], 1);
		i++;
	}
	i = 0;
	while (message[i] != '\0')
	{
		write(2, &message[i], 1);
		i++;
	}
	write(2, "\n", 1);
	close_window(game);
}

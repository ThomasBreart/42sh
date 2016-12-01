/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:51:38 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/22 08:43:32 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		builtin_bonus(void)
{
	ft_putchar('\n');
	ft_putendl("\\o_ And now: the bonus _o/");
	ft_putchar('\n');
	ft_putendl("- Operateur &&");
	ft_putendl("- Operateur ||");
	ft_putendl("- Touche supp");
	ft_putendl("- Gestion des metacharacter : '~'");
	ft_putendl("- Gestion des metacharacter : '$' (echo $VAR)");
	ft_putendl("- Prompt dynamique (change_prompt)");
	ft_putendl("- Split d'une commande via le backslash (\\)");
	ft_putendl("- Gestion des \"\"");
	ft_putendl("- Gestion de cd -, env -u");
	ft_putendl("- Gestion de l'etat du fils (segfault)");
	ft_putendl("- SHLVL");
	ft_putchar('\n');
	return (1);
}

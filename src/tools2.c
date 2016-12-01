/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/24 01:26:46 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/09 15:37:25 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	Cherche dans l'env la valeur correspondant a la cle passee;
**	SI dup == 1, duplique la chaine cle/valeur trouvee et retourne l adresse
**	SINON retourne l'ADRESSE
*/

char	*ft_getenvfull(char *key, char **env, int dup)
{
	char	*value;
	char	**tmp;

	tmp = env;
	value = NULL;
	while (*tmp != NULL)
	{
		if (ft_strncmp_complete(*tmp, key,
					len_before_thischar(*tmp, '=')) == 0)
		{
			if (dup == 1)
				value = s_strdup(*tmp, __FILE__);
			else
				value = *tmp;
			break ;
		}
		tmp++;
	}
	return (value);
}

/*
** Same as ft_getenvfull, mais retourne l'adresse du la string du tab env
*/

char	**ft_getenvadress(char *key, char **env)
{
	char	**tmp;

	tmp = env;
	if (key == NULL)
		return (NULL);
	while (*tmp != NULL)
	{
		if (ft_strncmp_complete(*tmp, key,
					len_before_thischar(*tmp, '=')) == 0)
			break ;
		tmp++;
	}
	if (*tmp == NULL)
		return (NULL);
	return (tmp);
}

char	*ft_getenv(char *name, char **env)
{
	char	*value;
	char	**tmp;
	int		i;

	tmp = env;
	value = NULL;
	while (*tmp != NULL)
	{
		if (ft_strncmp_complete(*tmp, name,
					len_before_thischar(*tmp, '=')) == 0)
		{
			i = len_after_thischar(*tmp, '=');
			value = s_strdup(*tmp + i, __FILE__);
			break ;
		}
		tmp++;
	}
	return (value);
}

int		is_just_spaces(char *cmd)
{
	int		i;

	i = 0;
	while (*cmd == ' ')
	{
		i++;
		cmd++;
	}
	if (*cmd == '\0')
		return (i);
	return (0);
}

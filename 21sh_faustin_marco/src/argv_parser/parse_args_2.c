/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:47:43 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/26 16:47:45 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		*ft_strtrim_quotes(char *s)
{
	char	*ref;
	char	*ret;
	int		tmp;

	ref = s;
	ret = ref;
	while (*s)
	{
		if (*s != '\'' && *s != '\"')
			*(ref++) = *(s++);
		else
		{
			tmp = *(s++);
			while (*s != tmp)
				*(ref++) = *(s++);
			s++;
		}
	}
	*ref = 0;
	return (ret);
}

void		replace_tilde(char **origin, int *index, char **environ)
{
	char	*ret;
	char	*var;
	int		var_len;

	if (!(var = return_env(environ, "HOME")))
		var = "\0";
	var_len = ft_strlen(var);
	ret = ft_strnew(var_len + ft_strlen(*origin));
	*((*origin) + (*index)) = 0;
	ft_strcpy(ret, *origin);
	ft_strcpy(ret + (*index), var);
	ft_strcpy(ret + (*index) + var_len, *origin + (*index) + 1);
	free(*origin);
	*index += var_len - 1;
	*origin = ret;
	if (var_len)
		free(var);
}

static void	replace_environ(char **origin, int *index,
			char **environ, char *str)
{
	char	*ret;
	char	*var;
	int		var_len;

	if (!(var = return_env(environ, str)))
		var = "\0";
	var_len = ft_strlen(var);
	ret = ft_strnew(var_len + ft_strlen(*origin));
	*((*origin) + (*index)) = 0;
	ft_strcpy(ret, *origin);
	ft_strcpy(ret + (*index), var);
	ft_strcpy(ret + (*index) + var_len,
		*origin + (*index) + ft_strlen(str) + 1);
	free(*origin);
	*index += var_len - 1;
	*origin = ret;
	if (var_len)
		free(var);
}

void		replace_dollar(char **av, int *i, char **environ)
{
	char	*token;

	token = get_token(&(*av)[(*i) + 1]);
	replace_environ(av, i, environ, token);
	free(token);
}

void		check_tilde_and_dollar(char **environ, char **av)
{
	int		i;
	int		j;
	int		dquote;

	i = 0;
	j = 0;
	dquote = 0;
	while (av[i])
	{
		check_tilde_and_dollar__str(environ, &av[i], j, dquote);
		ft_strtrim_quotes(av[i]);
		i++;
	}
}

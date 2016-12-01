/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read_append_to_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:04:33 by mfamilar          #+#    #+#             */
/*   Updated: 2016/11/07 18:56:24 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** S'il y a plus de clés que de variables, la dernière varible
** héritera de toutes les clés restantes.
*/

static char	*convert_values_to_one_value(char **values, int i)
{
	char		*str;

	str = reverse_split(values, i);
	return (str);
}

static char	**create_key_plus_value(char **keys, char **values, int *j, int i)
{
	char **ret;
	char *str;

	str = NULL;
	ret = NULL;
	*j += 1;
	if (keys[i + 1])
		ret = fake_argv(keys[i], values[i]);
	else
	{
		str = convert_values_to_one_value(values, i);
		ret = fake_argv(keys[i], str);
	}
	ft_memdel((void**)&str);
	return (ret);
}

static void	add_keys_to_env(char **keys, char **values, char ***env)
{
	int		i;
	int		j;
	char	**ret;

	ret = NULL;
	j = 0;
	i = 0;
	while (keys[i])
	{
		free_double_tab(ret);
		if (values[j])
			ret = create_key_plus_value(keys, values, &j, i);
		else
			ret = fake_argv(keys[i], NULL);
		if (ret)
			builtin_setenv(ret, env, 0);
		i++;
	}
	free_double_tab(ret);
}

/*
**	Si des variables sont données en paramètre, on les
** ajoute dans l'environnement avec les clés correspondantes.
*/

void		make_copies(char *argv, char ***env, int flag)
{
	char	**values;
	char	*str;
	char	**keys;

	keys = s_strsplit(argv, ' ', __FILE__);
	str = return_one_line(flag);
	values = s_strsplit(str, ' ', __FILE__);
	ft_memdel((void**)&str);
	add_keys_to_env(keys, values, env);
	free_double_tab(keys);
	free_double_tab(values);
}

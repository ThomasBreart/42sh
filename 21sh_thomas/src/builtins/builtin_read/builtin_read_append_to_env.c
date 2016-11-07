/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read_append_to_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:04:33 by mfamilar          #+#    #+#             */
/*   Updated: 2016/11/07 16:17:53 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	get_size(char **argv)
{
	int		i;
	int		len;

	len = 0;
	i = 1;
	while (argv[i])
	{
		len += ft_strlen(argv[i]);
		i++;
	}
	len += --i;
	return (len);
}

static char	*reverse_split(char **argv, int i)
{
	char	*ret;
	int		len;

	len = get_size(argv);
	ret = (char*)ft_memalloc(sizeof(char) * (len + 1));
	while (argv[i])
	{
		ft_strcat(ret, argv[i]);
		if (argv[i + 1])
			ft_strcat(ret, " ");
		i++;
	}
	return (ret);
}

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
			builtin_setenv(ret, env);
		i++;
	}
	free_double_tab(ret);
}

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

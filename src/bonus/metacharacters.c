/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 13:44:39 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/25 23:29:57 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		edit_line_meta(char **entry, char *value, int pos_key, int len_key)
{
	char	*new_s;
	char	*tmp;
	int		len_value;

	if (value == NULL)
		len_value = 0;
	else
		len_value = ft_strlen(value);
	new_s = s_strnew(ft_strlen(*entry) + len_value - len_key, __FILE__);
	tmp = *entry;
	ft_strncpy(new_s, *entry, pos_key);
	if (value != NULL)
		ft_strcpy(new_s + pos_key, value);
	ft_strcpy(new_s + pos_key + len_value, *entry + pos_key + len_key);
	free(*entry);
	*entry = new_s;
}

static void	tab_del_empty_index_create_newtab(t_list *elem, int free, int len)
{
	char	**tmp;
	char	**tmp2;
	char	**neew;

	neew = (char**)s_memalloc(sizeof(char*) * (len + 1), __FILE__);
	tmp = elem->argv;
	tmp2 = neew;
	while (*tmp != NULL)
	{
		if (ft_strlen(*tmp) > 0)
		{
			*tmp2 = s_strdup(*tmp, __FILE__);
			tmp2++;
		}
		tmp++;
	}
	*tmp2 = NULL;
	if (free == 1)
		free_double_tab(elem->argv);
	elem->argv = neew;
}

static int	tab_del_empty_index(t_list *elem, int free)
{
	char	**tmp;
	int		len;

	tmp = elem->argv;
	len = 0;
	while (*tmp != NULL)
	{
		if (ft_strlen(*tmp) > 0)
			len++;
		tmp++;
	}
	if (len == ft_tablen(elem->argv))
		return (1);
	if (len == 0)
	{
		if (free == 1)
			free_double_tab(elem->argv);
		elem->argv = NULL;
		return (0);
	}
	tab_del_empty_index_create_newtab(elem, free, len);
	return (1);
}

int			convert_metacharacters(t_list *elem, char **env)
{
	char	**tmp;

	tmp = elem->argv;
	while (*tmp != NULL)
	{
		check_shell_variable(tmp, *tmp, env);
		check_tild(tmp);
		tmp++;
	}
	free(elem->content);
	if (tab_del_empty_index(elem, 1) == 0)
	{
		elem->content = NULL;
		return (0);
	}
	elem->content = s_strdup(elem->argv[0], __FILE__);
	return (1);
}

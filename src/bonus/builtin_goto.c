/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_goto.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 18:40:17 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/08 17:48:38 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	check_goto_errors(char **argv)
{
	int		index;
	int		i;

	if (argv[1] == NULL || argv[2] != NULL)
	{
		ft_putendl_fd("usage: goto [index_hisory]", STDERR_FILENO);
		return (-1);
	}
	if (argv[1][0] == '-')
	{
		ft_putendl_fd("goto: index_hisory is negative", STDERR_FILENO);
		return (-1);
	}
	i = 0;
	while (ft_isdigit(argv[1][i]))
		i++;
	if (argv[1][i] != '\0')
	{
		ft_putendl_fd("goto: index_hisory is not a number", STDERR_FILENO);
		return (-1);
	}
	index = ft_atoi(argv[1]);
	return (index);
}

static char	*goto_index_tab(int index)
{
	char	***tab_hist;
	char	**tmp;
	int		i;

	tab_hist = get_tab_hist();
	tmp = *tab_hist;
	i = 0;
	while (*tmp != NULL && i < index)
	{
		i++;
		tmp++;
	}
	if (*tmp != NULL)
		return (s_strdup(*tmp, __FILE__));
	ft_putendl_fd("goto: this index don't exist", STDERR_FILENO);
	return (NULL);
}

int			builtin_goto(t_list *elem, char ***env)
{
	t_list		*root;
	int			ret;
	int			index;
	char		*entry;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	ret = -1;
	if ((index = check_goto_errors(elem->argv)) == -1)
		return (-1);
	if ((entry = goto_index_tab(index)) == NULL)
		return (-1);
	if ((root = cmd_analysis(&entry)) != NULL)
		ret = exec_cmd(root->left, env);
	free_memory(&entry, termcaps, &root, 0);
	return (ret);
}

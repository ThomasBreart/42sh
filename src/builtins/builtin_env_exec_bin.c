/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exec_bin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:19:23 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/02 14:20:56 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_list	*create_fake_elem(char **argv)
{
	t_list	*fake_elem;

	fake_elem = s_lstnew(NULL, __FILE__);
	fake_elem->content = s_strdup(*argv, __FILE__);
	fake_elem->fullcontent = ft_implode(argv);
	fake_elem->argv = s_tabdup(argv, __FILE__);
	fake_elem->type = -1;
	fake_elem->aggr_fd = -1;
	fake_elem->parent = NULL;
	fake_elem->prev = NULL;
	fake_elem->next = NULL;
	fake_elem->left = NULL;
	fake_elem->right = NULL;
	return (fake_elem);
}

static int		env_error(char *name_bin)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(name_bin, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (-1);
}

int				env_exec_bin(char **argv, char **cpenv, char **env)
{
	int			ret;
	t_save_fd	save;
	t_list		*fake_elem;
	char		*name_bin;

	save_fd(&save);
	name_bin = s_strdup(*argv, __FILE__);
	fake_elem = create_fake_elem(argv);
	if (ft_getenvfull("PATH", cpenv, 0) != NULL)
		find_fullpath_bin(fake_elem, cpenv);
	else
		find_fullpath_bin(fake_elem, env);
	if (fake_elem->content == NULL)
		ret = env_error(name_bin);
	else
		ret = cmd_simple_prog(fake_elem, cpenv, &save);
	del_tlist(fake_elem);
	free(name_bin);
	restore_fd(&save);
	close_fd(&save);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 09:06:09 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/14 15:53:40 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*del_parenthesis(char *str)
{
	char	*new_str;
	int		len;

	len = ft_strlen(str);
	new_str = s_strndup((str + 1), (len - 2), __FILE__);
	return (new_str);
}

int		exec_subshell(t_list *elem)
{
	char	*new_entry;
	int		ret;
	int		child_pid;
	t_list	*root;

	new_entry = del_parenthesis(elem->content);
	child_pid = fork();
	if (child_pid == -1)
		return (internal_error("exec_subshell", "fork", 0));
	else if (child_pid == 0)
	{
		root = cmd_analysis(&new_entry);
		ret = exec_cmd(root->left, get_env());
		exit(ret);
	}
	else
	{
		waitpid(child_pid, &ret, 0);
		if (WEXITSTATUS(ret) == 1)
			return (1);
		else
			return (-1);
	}
	return (-1);
}

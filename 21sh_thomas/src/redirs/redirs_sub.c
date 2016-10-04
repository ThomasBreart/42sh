/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 10:18:46 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/23 20:26:40 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	find_redir(t_list *elem, t_list *tmp, t_save_fd *save_sub)
{
	int		fd_sub;

	fd_sub = 42;
	if (elem->type == LEX_L_R)
		fd_sub = redir_file_lc(tmp, save_sub);
	else if (elem->type == LEX_LL_R)
		fd_sub = redir_file_llc(tmp, save_sub);
	else if (elem->type == LEX_R_R)
		fd_sub = redir_file_rc(tmp, save_sub);
	else if (elem->type == LEX_RR_R)
		fd_sub = redir_file_rrc(tmp, save_sub);
	return (fd_sub);
}

int			exec_redir_sub(t_list *elem, t_save_fd *save, t_list **current)
{
	int			ret;
	int			fd_sub;
	t_list		*tmp;
	int			fd_not_standard;

	fd_not_standard = -1;
	*current = elem->right;
	ret = 42;
	fd_sub = -1;
	check_fd_parent(elem->content, save);
	if (is_a_redir(elem->right->type) || elem->right->type == LEX_PIPE)
		tmp = elem->right->left;
	else
		tmp = elem->right;
	if ((fd_sub = find_redir(elem, tmp, save)) == -1)
		return (-1);
	if (is_a_redir(elem->right->type))
		ret = exec_redir_sub(elem->right, save, current);
	return (ret);
}

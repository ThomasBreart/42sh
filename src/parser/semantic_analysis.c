/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:47:20 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/19 16:40:45 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	pipe_exp ::= cmd [OPE_PIPE pipe_exp]?
*/

static int	read_pipe_redir_exp(t_list **root, t_list **token, t_list **parent)
{
	t_list	*tmp;

	tmp = *token;
	if (tmp == NULL)
		return (-1);
	if (lex_is_cmd(tmp))
	{
		if (lex_is_ope_pipe_or_redir(tmp->next))
		{
			*root = tmp->next;
			(*root)->parent = *parent;
			*token = (*token)->next->next;
			read_pipe_redir_exp(&(*root)->right, token, root);
			parent = root;
			(*root)->left = tmp;
			(*root)->left->parent = *parent;
		}
		else
		{
			*root = tmp;
			(*root)->parent = *parent;
		}
	}
	return (0);
}

/*
**	or_and_exp ::= pipe_exp [OPE_AND/OR or_and_exp]
*/

static void	read_or_and(t_list **root, t_list **tmp, t_list **parent)
{
	t_list	*svg;

	read_pipe_redir_exp(root, tmp, parent);
	if (lex_is_ope_or_and((*tmp)->next))
	{
		svg = *root;
		*root = (*tmp)->next;
		(*root)->parent = *parent;
		(*root)->left = svg;
		*tmp = (*tmp)->next->next;
		read_or_and(&(*root)->right, tmp, root);
	}
}

static void	read_coma(t_list **root, t_list *tmp, t_list **parent)
{
	t_list	*svg;

	read_or_and(root, &tmp, parent);
	if (lex_is_ope_coma(tmp->next))
	{
		svg = *root;
		*root = tmp->next;
		(*root)->parent = *parent;
		(*root)->left = svg;
		read_coma(&(*root)->right, tmp->next->next, root);
	}
}

t_list		*semantic_analysis(t_list *first)
{
	t_list	*root;

	root = s_lstnew("Start!", __FILE__);
	root->right = NULL;
	read_coma(&root->left, first, &root);
	return (root);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_cmd_general.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 22:46:09 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/03 19:47:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			is_a_redir(int type)
{
	if (type == LEX_L_R || type == LEX_LL_R || type == LEX_R_R ||
			type == LEX_RR_R)
		return (1);
	return (0);
}

static int	check_missing_word(t_list *elem)
{
	int			ret;

	ret = 1;
	if (elem == NULL || (elem->type != LEX_WORD && elem->type != LEX_SUBSH))
	{
		ft_putendl_fd("Invalid command.", STDERR_FILENO);
		return (-1);
	}
	while (elem != NULL)
	{
		if (elem->type == LEX_COMA || (elem->type >= 2 && elem->type <= 4))
		{
			ret = check_missing_word(elem->next);
			break ;
		}
		else if (elem->type >= 5 && elem->type <= 8)
			if (elem->next == NULL || elem->next->type != 1)
			{
				ft_putendl_fd("Missing name for redirect.", STDERR_FILENO);
				return (-1);
			}
		elem = elem->next;
	}
	return (ret);
}

static int	useless_comas(t_list **first)
{
	t_list *elem;
	t_list *tmp;

	elem = *first;
	while (elem != NULL)
	{
		tmp = NULL;
		if (elem->type == LEX_COMA)
		{
			if (elem->prev == NULL || elem->prev->type == LEX_COMA ||
					elem->next == NULL || elem->next->type == LEX_COMA)
				tmp = elem;
		}
		elem = elem->next;
		if (tmp != NULL)
		{
			if (*first == tmp)
				*first = (*first)->next;
			del_elem_list(tmp);
		}
	}
	if (*first == NULL)
		return (-1);
	return (1);
}

static int	formatting_file(t_list *first)
{
	t_list *elem;

	elem = first;
	while (elem != NULL)
	{
		if (is_a_redir(elem->type) == 1)
		{
			if (ft_tablen(elem->next->argv) > 1)
			{
				ft_putendl_fd("file bad formatted", STDERR_FILENO);
				return (-1);
			}
		}
		elem = elem->next;
	}
	return (1);
}

int			formatting_cmd_general(t_list **first)
{
	int		ret;
	t_list	*tmp;

	ret = -1;
	ret = find_aggregator_fd(*first);
	if (ret != -1)
		ret = useless_comas(first);
	if (ret != -1)
		ret = check_missing_word(*first);
	if (ret != -1)
		ret = check_word_and_subsh(*first);
	if (ret != -1)
		ret = formatting_file(*first);
	if (ret == -1)
	{
		while ((*first) != NULL)
		{
			tmp = *first;
			*first = (*first)->next;
			del_tlist(tmp);
		}
	}
	return (ret);
}

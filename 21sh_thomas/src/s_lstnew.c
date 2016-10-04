/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 15:48:49 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/19 17:33:20 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_list	*s_lstnew(char const *content, const char *filename)
{
	t_list *newlist;

	newlist = (t_list *)s_memalloc(sizeof(t_list), filename);
	newlist->next = NULL;
	newlist->prev = NULL;
	newlist->parent = NULL;
	newlist->left = NULL;
	newlist->right = NULL;
	newlist->argv = NULL;
	if (content == NULL)
		newlist->content = NULL;
	else
	{
		newlist->content = s_strnew(ft_strlen(content), filename);
		ft_memcpy((newlist->content), content, ft_strlen(content));
	}
	return (newlist);
}

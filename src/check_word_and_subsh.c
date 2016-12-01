/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word_and_subsh.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 05:43:23 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 05:44:30 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		check_word_and_subsh(t_list *first)
{
	while (first != NULL)
	{
		if (first->type == LEX_WORD)
		{
			if (first->next != NULL && first->next->type == LEX_SUBSH)
			{
				ft_putendl_fd("Invalid command.", STDERR_FILENO);
				return (-1);
			}
		}
		first = first->next;
	}
	return (1);
}

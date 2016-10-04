/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_changeprompt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 01:31:44 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/19 15:41:23 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		builtin_change_prompt(t_list *elem)
{
	t_historic	*termcaps;

	if (ft_tablen(elem->argv) != 2)
	{
		ft_putendl_fd("Usage: change_prompt [new name prompt]", STDERR_FILENO);
		return (-1);
	}
	termcaps = get_termcaps();
	free(termcaps->prompt);
	termcaps->prompt = s_strdup(elem->argv[1], __FILE__);
	termcaps->len_prompt = ft_strlen(termcaps->prompt);
	termcaps->prompt_current = termcaps->prompt;
	return (1);
}

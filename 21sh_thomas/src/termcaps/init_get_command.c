/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_get_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 18:25:58 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/13 13:57:17 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	init_var_cmd(t_historic *termcaps, char **entry)
{
	termcaps->in_getcmd = 1;
	termcaps->entry = entry;
	*entry = NULL;
	termcaps->cmd_inprogress = NULL;
	termcaps->hist = 0;
	termcaps->bslash_split = NULL;
	termcaps->len_prompt = ft_strlen(termcaps->prompt_current);
}
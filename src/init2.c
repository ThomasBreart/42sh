/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 06:45:56 by tbreart           #+#    #+#             */
/*   Updated: 2016/08/14 17:38:31 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void		init_proc(void)
{
	t_proc		*proc;
	int			i;

	i = 0;
	proc = get_proc();
	proc->index = 0;
	while (i < 100)
	{
		proc->tab_pid[i] = 0;
		++i;
	}
}

void		init_var_aggrfd(t_historic *termcaps)
{
	termcaps->index_tab_aggrfd = 0;
	termcaps->stdout_modified = 0;
}

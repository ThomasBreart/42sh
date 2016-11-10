/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 06:33:16 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/22 06:48:09 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	save_pid(pid_t pid)
{
	t_proc		*proc;

	proc = get_proc();
	proc->tab_pid[proc->index] = pid;
	proc->index = proc->index + 1;
}

void	kill_process_still_in_progress(void)
{
	t_proc		*proc;
	int			i;

	proc = get_proc();
	i = 0;
	while (proc->tab_pid[i] != 0)
	{
		kill(proc->tab_pid[i], SIGKILL);
		proc->tab_pid[i] = 0;
		++i;
	}
	proc->index = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:23:56 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/22 06:48:22 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_historic	*get_termcaps(void)
{
	static t_historic	termcaps;

	return (&termcaps);
}

char		***get_env(void)
{
	static char		**env;

	return (&env);
}

t_proc		*get_proc(void)
{
	static t_proc	proc;

	return (&proc);
}

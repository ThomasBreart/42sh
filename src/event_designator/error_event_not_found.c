/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_event_not_found.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 12:21:27 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/06 12:23:17 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		error_event_not_found(char *str, int error)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (error == E_NOT_FOUND)
		ft_putendl_fd(" event not found", STDERR_FILENO);
	else if (error == E_NO_PREVSUB)
		ft_putendl_fd(" no previous substitution", STDERR_FILENO);
	ft_strdel(&str);
	return (-1);
}

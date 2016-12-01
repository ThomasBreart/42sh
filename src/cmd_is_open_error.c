/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_open_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 19:44:46 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/11 19:46:53 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		cmd_is_open_error(char error)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
	ft_putstr_fd("Parse error near '", STDERR_FILENO);
	ft_putchar_fd(error, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	ft_putstr(termcaps->prompt);
	return (-1);
}

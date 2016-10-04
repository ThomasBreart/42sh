/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 07:08:59 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/07 07:09:25 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		check_fd_parent(char *s, t_save_fd *save)
{
	int		x;

	x = -1;
	if (s[0] == '>')
		x = 1;
	else if (s[0] == '<')
		x = 0;
	else if (ft_isdigit(s[0]))
		x = s[0] - '0';
	else if (s[0] == '&')
		x = '&';
	save->fd_parent = x;
	return (1);
}

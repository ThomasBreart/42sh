/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_termios.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 07:34:27 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/14 14:46:23 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		set_termios(struct termios *term, t_save_fd *save)
{
	int		ret;
	int		save_stdin;

	if (save != NULL)
	{
		save_stdin = fcntl(STDIN_FILENO, F_DUPFD, 10);
		dup2(save->save_stdin, STDIN_FILENO);
	}
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, term) == -1)
		ret = -1;
	else
		ret = 1;
	if (save != NULL)
	{
		if (save_stdin == -1)
			close(STDIN_FILENO);
		else
			dup2(save_stdin, STDIN_FILENO);
		close(save_stdin);
	}
	return (ret);
}

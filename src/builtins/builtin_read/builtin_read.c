/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 16:15:00 by mfamilar          #+#    #+#             */
/*   Updated: 2016/11/12 13:24:48 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	put_cooked_mode(t_save_fd *save)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	set_termios(&termcaps->term, save);
}

static void	put_raw_mode(t_save_fd *save)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	set_termios(&termcaps->save, save);
}

char		*return_one_line(int flag)
{
	char		*str;
	int			fd_tmp;
	t_historic	*termcaps;

	str = NULL;
	termcaps = get_termcaps();
	termcaps->in_read = 1;
	fd_tmp = fcntl(STDIN_FILENO, F_DUPFD, 10);
	get_next_line(STDIN_FILENO, &str);
	dup2(fd_tmp, STDIN_FILENO);
	close(fd_tmp);
	termcaps->in_read = 0;
	if (!flag && str != NULL)
		remove_onelvl_escape_backslash(&str);
	return (str);
}

/*
** S'il n'y a pas de variables données en paramètre, on ajoute
** la clé à la valeur par défaut : "REPLY".
*/

static void	put_on_reply(char ***env, int flag)
{
	char	**ret;
	char	*str;

	if ((str = return_one_line(flag)) == NULL)
		return ;
	ret = fake_argv("REPLY", str);
	builtin_setenv(ret, env, 0);
	ft_memdel((void**)&str);
	free_double_tab(ret);
}

/*
**	Built-in de la commande read
**	Elle lit une ligne depuis l'entrée standard et l'ajoute dans l'env.
**	Une seule option possible, "-r", qui lorsqu'elle est présente
** 	empêche les backslashes d'agir comme des caractères d'échappement.
*/

int			builtin_read(char **ar, t_save_fd *save, char ***env)
{
	char	*begin;
	char	*argv;
	int		flag;
	int		ret;

	ret = 0;
	flag = 0;
	argv = reverse_split(ar, 1);
	begin = argv;
	put_raw_mode(save);
	ret = parse_flag(&argv, &flag);
	if (!ret && *argv == '\0')
		put_on_reply(env, flag);
	else if (!ret)
		make_copies(argv, env, flag);
	put_cooked_mode(save);
	ft_memdel((void**)&begin);
	ret = (ret == 1) ? -1 : 1;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 16:15:00 by mfamilar          #+#    #+#             */
/*   Updated: 2016/11/07 18:31:26 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
	char	*str;

	get_next_line(STDIN_FILENO, &str);
	if (!flag)
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

	str = return_one_line(flag);
	ret = fake_argv("REPLY", str);
	builtin_setenv(ret, env);
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
	return (ret);
}

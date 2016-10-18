/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 17:47:40 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/18 15:39:07 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	history_anrw_error(void)
{
	ft_putstr_fd("42sh: history: cannot use more than one of -anrw\n", 2);
	return (1);
}

/*
** Viennent ensuite les flags 'a', 'n', 'r', 'w' qui sont de priorité égale.
** Ces flags ne peuvent pas être appelé en même temps.
*/

static int	check_flags_anrw(char *args, t_flags *flags)
{
	flags->argument = get_argument(args, 0);
	if (flags->flag_a && !flags->flag_n && !flags->flag_r && !flags->flag_w)
		ft_putstr("FLAG A is ON WITH FILENAME = %s\n");
	else if (flags->flag_n && !flags->flag_a && !flags->flag_r &&
			!flags->flag_w)
		ft_putstr("FLAG N is ON WITH FILENAME = %s\n");
	else if (flags->flag_r && !flags->flag_a && !flags->flag_n &&
			!flags->flag_w)
		flag_r(flags);
	else if (flags->flag_w && !flags->flag_a && !flags->flag_n &&
			!flags->flag_r)
		flag_w(flags);
	else
		return (history_anrw_error());
	return (0);
}

/*
** Dans l'ordre des priorité vient ensuite le 's' et le 'p'.
** Le 's' est supérieur au 'p'.
*/

static int	check_flags_s_and_p(char *args, t_flags flags, char **ar)
{
	int	ret;

	ret = 0;
	if (flags.flag_s || flags.flag_p)
		flags.argument = get_argument(args, 1);
	if (flags.flag_s)
		flag_s(args);
	else if (flags.flag_p)
		flag_p(ar);
	else
		ret = check_flags_anrw(args, &flags);
	ft_memdel((void**)&flags.argument);
	return (ret);
}

static int	handle_flag_d(t_flags flags, char *args)
{
	int	ret;

	ret = 0;
	if (flags.flag_d)
	{
		if (!(ret = flag_d(args, &flags)))
		{
			if (!flags.flag_c)
				ret = del_indice_history(flags);
		}
	}
	ft_memdel((void**)&flags.argument);
	return (ret);
}

/*
** Les deux flags prioritaires sur les autres sont le 'c' et le 'd'.
** Si l'un des deux est ativé, on ne se préocupe pas des autres options.
*/

int			check_history_flags(char *args, t_flags flags, char **ar)
{
	if (handle_flag_d(flags, args))
		return (1);
	if (flags.flag_c)
		flag_c();
	else if (!flags.flag_d && !flags.flag_c)
		if (check_flags_s_and_p(args, flags, ar))
			return (1);
	return (0);
}

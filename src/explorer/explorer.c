/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explorer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:00:08 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 02:00:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

void			set_args(t_file *root, t_args *arg, t_historic *t)
{
	arg->page = 0;
	arg->n = get_nbfile(root);
	if (t->ws.ws_row >= 3)
		arg->n_pages = arg->n / (t->ws.ws_row - 2);
	if (arg->n_pages == 0)
		arg->n_pages = 1;
	arg->y = 0;
}

static void		start(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_outc);
	tputs(tgetstr("ti", NULL), 1, ft_outc);
	tputs(tgetstr("vi", NULL), 1, ft_outc);
}

int				builtin_explorer(t_historic *t, char ***env)
{
	t_args	a;
	char	tabl[1024];

	t->in_explorer = 1;
	write(1, "\033[s", 3);
	ft_bzero(&a, sizeof(t_args));
	getcwd(tabl, sizeof(char) * 1024);
	a.env = env;
	start();
	ls(t, &a);
	tputs(tgetstr("te", NULL), 1, ft_outc);
	tputs(tgetstr("ve", NULL), 1, ft_outc);
	t->in_explorer = 0;
	return (1);
}

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

void		explorer_signal(int signum)
{
	(void)signum;
}

void		no_name(int fd, t_args *arg, t_historic *t, t_file *f)
{
	if (arg->new_page != arg->page)
	{
		arg->new_page = arg->page;
		write(fd, "\033c", 2);
		write(fd, "\033[s", 3);
		parcours(fd, &t->ws, arg, f);
	}
	write(fd, "\033[u", 3);
	print_at(fd, arg->y + 1);
}

static void		set_rawmode(struct termios *termios_p)
{
	termios_p->c_lflag &= ~(ECHO | ICANON);
	termios_p->c_cflag |= CS8;
	termios_p->c_cc[VMIN] = 1;
	termios_p->c_cc[VTIME] = 0;
}

void		start(t_historic *t)
{
	tcgetattr(0, &t->save);
	tcgetattr(0, &t->term);
	set_rawmode(&t->term);
	tputs(tgetstr("cl", NULL), 1, ft_outc);
	tputs(tgetstr("ti", NULL), 1, ft_outc);
	tputs(tgetstr("vi", NULL), 1, ft_outc);
	tcsetattr(0, 0, &t->term);
}

int			builtin_explorer(t_historic *t)
{
	t_args	a;
	char	tabl[1024];

	ft_bzero(&a, sizeof(t_args));
	getcwd(tabl, sizeof(char) * 1024);
	a.path = ft_strdup(tabl);
	start(t);
	ls(t, &a);
	tputs(tgetstr("te", NULL), 1, ft_outc);
	tputs(tgetstr("ve", NULL), 1, ft_outc);
	tcsetattr(0, 0, &t->save);
	chdir(a.path);
	free(a.path);
	return (1);
}

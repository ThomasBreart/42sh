/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:28:35 by fjacquem          #+#    #+#             */
/*   Updated: 2016/12/02 17:28:37 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

void		mykey_up(t_historic *t, t_args *arg)
{
	if (arg->y == 0)
		arg->y = arg->n - 1;
	else
		arg->y--;
	if (arg->y >= (t->ws.ws_row - 2))
	{
		arg->page++;
		arg->y = 0;
	}
	if (arg->page >= arg->n_pages)
		arg->page = 0;
	else if (arg->page < 0)
		arg->page = arg->n_pages - 1;
}

void		mykey_down(t_historic *t, t_args *arg)
{
	if (arg->y == arg->n - 1)
		arg->y = 0;
	else
		arg->y++;
	if (arg->y >= (t->ws.ws_row - 2))
	{
		arg->page++;
		arg->y = 0;
	}
	if (arg->page >= arg->n_pages)
		arg->page = 0;
	else if (arg->page < 0)
		arg->page = arg->n_pages - 1;
}

void		mykey_left(t_args *arg)
{
	if (arg->page == 0)
		arg->page = arg->n_pages - 1;
	else
		arg->page--;
}

void		mykey_right(t_args *arg)
{
	if (arg->page == arg->n_pages - 1)
		arg->page = 0;
	else
		arg->page++;
}

void		mykey_cd(int in, t_historic *t, t_args *arg, t_file **root)
{
	if (in == '\n' && open_folder(t, root, arg))
	{
		set_args(*root, arg, t);
		print_files(1, &t->ws, arg, *root);
	}
	else if (in == 127)
	{
		open_parent_folder(root, arg);
		set_args(*root, arg, t);
		print_files(1, &t->ws, arg, *root);
	}
}

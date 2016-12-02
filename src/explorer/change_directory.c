/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:28:23 by fjacquem          #+#    #+#             */
/*   Updated: 2016/12/02 17:28:25 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

int				open_folder(t_historic *t, t_file **root, t_args *arg)
{
	t_file		*folder;

	folder = get_file(*root, arg, t);
	if (folder)
	{
		if (S_IFDIR == (folder->s.st_mode & S_IFMT) ||
			S_IFLNK == (folder->s.st_mode & S_IFMT))
		{
			call_cd(folder->p.name, arg->env);
			del(root);
			*root = ft_open(arg, ".");
			return (1);
		}
	}
	return (0);
}

void			open_parent_folder(t_file **root, t_args *arg)
{
	del(root);
	call_cd("..", arg->env);
	*root = ft_open(arg, ".");
}

void			call_cd(char *path, char ***env)
{
	char		*args[3];

	args[0] = "cd";
	args[1] = path;
	args[2] = NULL;
	builtin_cd(args, env);
}

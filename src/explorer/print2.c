/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:56:14 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 02:56:17 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

void	print_type(mode_t mode, int fd)
{
	if (S_IFLNK == mode)
		write(fd, "l", 1);
	else if (S_IFDIR == mode)
		write(fd, "d", 1);
	else if (S_IFIFO == mode)
		write(fd, "p", 1);
	else if (S_IFBLK == mode)
		write(fd, "b", 1);
	else if (S_IFSOCK == mode)
		write(fd, "s", 1);
	else if (S_IFCHR == mode)
		write(fd, "c", 1);
	else
		write(fd, "-", 1);
}

void	print_spec(mode_t mode, int fd)
{
	if (mode & S_ISVTX && !(mode & S_IXOTH))
		write(fd, "T", 1);
	else if (mode & S_ISVTX && (mode & S_IXOTH))
		write(fd, "t", 1);
	else if (mode & 1 & 0x7)
		write(fd, "x", 1);
	else
		write(fd, "-", 1);
}

void	print_header(int blks, int page, t_args *a, int fd)
{
	write(fd, "  total ", 8);
	ft_putnbr_fd(blks, fd);
	write(fd, "  page[", 7);
	ft_putnbr_fd(page + 1, fd);
	write(fd, "/", 1);
	ft_putnbr_fd(a->n_pages, fd);
	write(fd, "]\n", 2);
}
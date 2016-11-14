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
/*
void	print_color_bis_bis(char **cl, int mode, int fd)
{
	if (S_IFLNK == (mode & S_IFMT))
	{
		ft_putansi_str(cl[2], fd);
		ft_putansi_str(cl[3], fd);
	}
	if (S_IFDIR == (mode & S_IFMT))
	{
		ft_putansi_str(cl[0], fd);
		ft_putansi_str(cl[1], fd);
	}
}

void	print_color_bis(char **cl, int mode, int fd)
{
	if ((S_IFMT & mode) == S_IFCHR)
	{
		ft_putansi_str(cl[12], fd);
		ft_putansi_str(cl[13], fd);
	}
	if (mode & S_ISUID && ((S_IXGRP & mode) || (S_IXUSR & mode)))
	{
		ft_putansi_str(cl[14], fd);
		ft_putansi_str(cl[15], fd);
	}
	if (S_ISGID & mode && ((S_IXGRP & mode) || (S_IXUSR & mode)))
	{
		ft_putansi_str(cl[16], fd);
		ft_putansi_str(cl[17], fd);
	}
	if (S_IFDIR == (mode & S_IFMT) && (mode & S_IWOTH) && (mode & S_ISVTX))
	{
		ft_putansi_str(cl[18], fd);
		ft_putansi_str(cl[19], fd);
	}
	if (S_IFDIR == (mode & S_IFMT) && (mode & S_IWOTH) && !(mode & S_ISVTX))
	{
		ft_putansi_str(cl[20], fd);
		ft_putansi_str(cl[21], fd);
	}
}

void	print_color(char **cl, int mode, int fd)
{
	if (S_IFSOCK == (mode & S_IFMT))
	{
		ft_putansi_str(cl[4], fd);
		ft_putansi_str(cl[5], fd);
	}
	if (S_IFIFO == (mode & S_IFMT))
	{
		ft_putansi_str(cl[6], fd);
		ft_putansi_str(cl[7], fd);
	}
	if ((S_IFDIR != (mode & S_IFMT)) && (S_IXUSR & mode))
	{
		ft_putansi_str(cl[8], fd);
		ft_putansi_str(cl[9], fd);
	}
	if (S_IFBLK == (mode & S_IFMT))
	{
		ft_putansi_str(cl[10], fd);
		ft_putansi_str(cl[11], fd);
	}
	print_color_bis(cl, mode, fd);
	print_color_bis_bis(cl, mode, fd);
}
*/

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:00:08 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 02:00:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <select.h>

int		get_fd(void)
{
	static int	fd = -1;

	if (fd == -1)
	{
		fd = open("/dev/tty", O_RDWR);
		if (fd < 0 || !isatty(fd))
			fd = 1;
	}
	return (fd);
}

int		term_putchar(int c)
{
	return (write(get_fd(), &c, 1));
}

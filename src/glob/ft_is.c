/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:54:42 by fjacquem          #+#    #+#             */
/*   Updated: 2016/11/14 10:54:43 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_iscntrl(int c)
{
	return (c >= 0 && c <= 31);
}

int			ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}

int			ft_isgraph(int c)
{
	if (c >= '!' && c <= '~')
		return (1);
	return (0);
}

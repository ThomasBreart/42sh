/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 16:15:00 by mfamilar          #+#    #+#             */
/*   Updated: 2016/11/04 15:37:18 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "stdio.h"

static int	get_size(char **argv)
{
	int		i;
	int		len;

	len = 0;
	i = 1;
	while (argv[i])
	{
		len += ft_strlen(argv[i]);
		i++;
	}
	len += --i;
	return (len);
}

static char		*reverse_split(char **argv)
{
	char	*ret;
	int		len;
	int		i;

	i = 1;
	len = get_size(argv);
	ret = (char*)ft_memalloc(sizeof(char) * (len + 1));
	while (argv[i])
	{
		ft_strcat(ret, argv[i]);
		if (argv[i + 1])
			ft_strcat(ret, " ");
		i++;
	}
	return (ret);
}

static void put_cooked_mode(t_save_fd *save)
{
  t_historic  *termcaps;

  termcaps = get_termcaps();
  set_termios(&termcaps->term, save);
}

static void put_raw_mode(t_save_fd *save)
{
  t_historic  *termcaps;

  termcaps = get_termcaps();
  set_termios(&termcaps->save, save);
}

void save_by_default(void) {
  char    *str;
  get_next_line(STDIN_FILENO, &str);
  printf("str = %s\n", str);
  ft_memdel((void**)&str);
}

int         builtin_read(char **ar, t_save_fd *save)
{
  char  *begin;
  char  *argv;
  int   flag;
  int   ret;

  ret = 0;
  flag = 0;
  argv = reverse_split(ar);
  begin = argv;
  put_raw_mode(save);
  if (*argv == '\0')
    save_by_default();
  else
  {
    ret = parse_flag(&argv, &flag);
    if (!ret)
      save_by_default();
  }
  put_cooked_mode(save);
  ft_memdel((void**)&begin);
  return (ret);
}

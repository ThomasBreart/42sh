/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:21:35 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:21:37 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITERM_H
# define MINITERM_H
# include <libft.h>
# include <implemt.h>
# include <print.h>
# include <unistd.h>
# include <fcntl.h>
# include <term.h>
# include <dirent.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <stdio.h>
# undef BUFF_SIZE
# define BUFF_SIZE 1
# define MSHELL_SHIFT 993090331
# define MSHELL_CTRL 993090331
# define MSHELL_DEFAULT_LINE_SIZE 1024
# define MSHELL_KEYUP 4283163
# define MSHELL_KEYDOWN 4348699
# define MSHELL_KEYRIGHT 4414235
# define MSHELL_KEYLEFT 4479771
# define MSHELL_SHIFT_KEYUP 16690
# define MSHELL_SHIFT_KEYDOWN 16946
# define MSHELL_SHIFT_KEYRIGHT 17209
# define MSHELL_SHIFT_KEYLEFT 17458
# define MSHELL_CTRL_KEYUP 16697
# define MSHELL_CTRL_KEYDOWN 16953
# define MSHELL_CTRL_KEYRIGHT 17205
# define MSHELL_CTRL_KEYLEFT 17465
# define MSHELL_SCTRL_KEYRIGHT 17462
# define MSHELL_SCTRL_KEYLEFT 17206
# define MSHELL_SPEC_COPY 2
# define MSHELL_SPEC_CUT 24
# define MSHELL_SPEC_PASTE 22
# define MSHELL_HOME 4738843
# define MSHELL_END 4607771
# define MSHELL_CTRL_KEYR 18
# define ENV_SEPARATOR ":"
# define HIST_UP 1
# define HIST_DOWN 2
# define HIST_ADD 3
# define HIST_INS 4
# define MSHELL_MASK_ALL 1023
# define MSHELL_MASK_COLOR_FGPROMT	1
# define MSHELL_MASK_COLOR_BGPROMT	2
# define MSHELL_MASK_COLOR_FGCMD	4
# define MSHELL_MASK_COLOR_BGCMD	8
# define MSHELL_MASK_COLOR_FGEXE	16
# define MSHELL_MASK_COLOR_BGEXE	32
# define MSHELL_MASK_COLOR_FGNAME	64
# define MSHELL_MASK_COLOR_BGNAME	128
# define MSHELL_MASK_HIS			256
# define MSHELL_MASK_ENV			512
#endif

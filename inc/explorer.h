/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explorer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:23:22 by fjacquem          #+#    #+#             */
/*   Updated: 2016/12/06 15:45:35 by jmaccion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPLORER_H
# define EXPLORER_H
# include <map.h>
# include <sys/ioctl.h>
# include "../libft/includes/libft.h"
# include <unistd.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <sys/ioctl.h>
# define PATH_SEPARATOR "/"
# define PATH_SEPARATOR_LEN 1
# define C_BLACK "030"
# define C_RED "031"
# define C_GREEN "032"
# define C_BROWN "033"
# define C_BLUE "034"
# define C_MAGENTA "035"
# define C_CYAN "036"
# define C_L_GREY "037"
# define C_B_BLACK "090"
# define C_B_RED "091"
# define C_B_GREEN "092"
# define C_B_BROWN "093"
# define C_B_BLUE "094"
# define C_B_MAGENTA "095"
# define C_B_CYAN "096"
# define C_B_L_GREY "097"
# define C_DEF "exfxcxdxbxegedabagacad"
# define C_1 C_BLACK "\0" C_RED "\0" C_GREEN "\0" C_BROWN "\0"
# define C_COLORS  C_1 C_BLUE "\0" C_MAGENTA "\0" C_CYAN "\0" C_L_GREY "\0"
# define C_2 C_B_BLACK "\0" C_B_RED "\0" C_B_GREEN "\0" C_B_BROWN "\0" C_B_BLUE
# define C_B_COLORS C_2 "\0" C_B_MAGENTA "\0" C_B_CYAN "\0" C_B_L_GREY "\0"
# define MONTH_I "Jan\0" "Feb\0" "Mar\0" "Apr\0" "May\0" "Jun\0"
# define MONTH_II "Jul\0" "Aug\0" "Sep\0" "Oct\0" "Nov\0" "Dec\0"
# define MONTH MONTH_I MONTH_II
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <string.h>
# include <errno.h>
# include <sys/acl.h>
# include <structs.h>
# include <termcaps.h>

typedef struct stat		t_stat;
typedef struct dirent	t_dir;

enum
{
	NUM_ID = 1,
	INIT_COLOR = 4,
	PRINT_TOTAL = 8,
	PRINT_LINE = 16,
	PRINT_PATH = 32,
	MTIME = 64,
	SIZE = 128,
	CRTIME = 256,
	RECURSIF = 512,
	LIST = 1024,
	ALL = 2048,
	REVERSE = 8192,
	COLOR = 16384,
	OUT_LINE = 32768
};

typedef struct			s_print
{
	mode_t				mode;
	int					alloc;
	char				attr;
	int					len_name;
	char				*name;
	int					len_nlink;
	char				*nlink;
	int					len_usr;
	char				*usr;
	int					len_grp;
	char				*grp;
	int					len_ma;
	int					len_mi;
	char				*maj;
	char				*min;
	int					len_size;
	char				*size;
	time_t				tim;
	struct timespec		sec;
	int					is_attr;
	char				lnk[1024];
}						t_print;

typedef struct			s_file
{
	t_stat				s;
	t_print				p;
	struct s_file		*next;
}						t_file;

typedef struct			s_args
{
	int					page;
	int					n_pages;
	int					n;
	int					y;
	int					n_item;
	int					offset[6];
	char				***env;
	int					mask;
}						t_args;

/*
**						ft_outc
*/
int						ft_outc(int c);

/*
**						addfile.c
*/
void					addfile(t_file **f, t_file *add, int rev);

/*
**						explorer.c
*/
int						builtin_explorer(t_historic *t, char ***env);
void					set_args(t_file *root, t_args *arg, t_historic *t);

/*
**						file.c
*/
t_file					*new_file(t_args *a, char *name);
t_file					*ft_open(t_args *a, char *dn);
void					del(t_file **f);

/*
**						file2.c
*/
int						get_nbfile(t_file *root);
void					print_at(int fd, int n);
t_file					*get_file(t_file *root, t_args *a, t_historic *t);

/*
**						initialize.c
*/
void					delete_print(t_print *p);
void					init_print(char *name, t_stat *s, int sort, t_print *p);

/*
**						ls.c
*/
int						ls(t_historic *t, t_args *arg);

/*
**						opts.c
*/
int						skip_pages(struct winsize *ws, int *cur, t_file **ptr,
						t_args *a);

/*
**						print.c
*/
void					print_stat(t_args *a, t_print *f, int fd);

/*
**						print2.c
*/
void					print_type(mode_t mode, int fd);
void					print_spec(mode_t mode, int fd);
void					print_header(int blks, int page, t_args *a, int fd);

/*
**						print_files.c
*/
void					print_files(int fd, struct winsize *ws, t_args *a,
						t_file *f);
void					print_offset(int offset, int c, int fd);
char					*set_filename(char *s1, char *s2, int add_sep);
int						prepare(t_args *a, t_file *root);

/*
**						extern
*/
int						builtin_cd(char **args, char ***env);
int						recalc_need_size(void *na, void *nf);
int						can_drawing(struct winsize *ws);

/*
**						inputs.c
*/
void					mykey_up(t_historic *t, t_args *arg);
void					mykey_down(t_historic *t, t_args *arg);
void					mykey_left(t_args *arg);
void					mykey_right(t_args *arg);
void					mykey_cd(int in, t_historic *t, t_args *arg,
						t_file **root);

/*
**						Change directory
*/
void					call_cd(char *path, char ***env);
int						open_folder(t_historic *t, t_file **root, t_args *arg);
void					open_parent_folder(t_file **root, t_args *arg);
#endif

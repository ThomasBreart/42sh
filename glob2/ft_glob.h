#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define DEBUG
#define GLOB__NO_MATCHES 1
#define GLOB__ERROR 2
#define GLOB__OK 0

typedef struct		s_pattern
{
	int				error;
	char			*pattern;
}					t_pattern;

typedef struct		s_globinfo
{
	char			*local;
	char			*name;
	char			*path;
	int				flags;
}					t_globinfo;

typedef struct		s_glob
{
	char			*pattern;
	t_list			*results;
	int				n_results;
	int				flags;
}					t_glob;

t_list	*ft_lstnew_noalloc(const void *cnt, size_t cnt_size);
int		ft_strcasecmp(const char *s1, const char *s2);
int		ft_isblank(int c);
int		ft_iscntrl(int c);
void	ft_lstadd_end(t_list **addr, t_list *lst);

void	glob__open_first_directory(t_globinfo g, char *pattern, t_list **results);
void	glob__open_directory(t_globinfo g, char *pattern, t_list **results);
int		glob__match(t_globinfo *g, char *filename, char *pattern, t_list **results);

int		get_patterns(t_list **patterns, char *pattern);
int		glob_brace(t_list *first);

char	*glob__create_string(t_list *results);
int		ft_glob(const char *pattern, t_glob *g);

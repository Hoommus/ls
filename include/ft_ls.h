#ifndef FT_LS_H
# define FT_LS_H

# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>

# include "../printf/include/ft_printf.h"
# include "../libft/libft.h"

# define F_LONG    1
# define F_ALL     2
# define F_SORTT   4
# define F_SORTR   8
# define F_RECUR  16
# define F_COLOR  32
# define F_NSORT 128

/*
** write
** opendir
** readdir
** closedir
** stat
** lstat
** getpwuid
** getgrgid
** listxattr
** getxattr
** time
** ctime
** readlink
** malloc
** free
** perror
** strerror
** exit
**
*/

short				g_flags;
struct s_params		g_params;

typedef struct		s_file
{
	char			*filename;
	char			*path;
	uid_t			uid;
	gid_t			gid;
	nlink_t			links;
	mode_t			mode;
	struct timespec	atime;
	struct timespec	mtime;
	struct timespec	ctime;
	struct timespec	btime;
	off_t			size;
	blkcnt_t		blocks;
	struct s_file	*next;
}					t_file;

typedef struct		s_params
{
	int				linkw;
	int				bytew;
	int				userw;
	int				groupw;
	int				namew;
}					t_params;

/*
** Generic Utilities
*/
char				*create_path(char *dirname, char *filename);
void				traverse_read_print(char **names);
/*
**
*/
void				free_file(t_file *f);
void				free_list(t_file *list);
void				free_array(char **array);
int					parse_flags(int count, char **str);

t_file				*get_directory_contents(char *dirname, DIR *dir);
t_file				*create_file(char *filename, struct stat *s, char *path);

/*
** List manipulations
*/
void				list_add(t_file **head, t_file **tail, t_file *to_add);
t_file				*list_swap(t_file *list, t_file *first, t_file *second);

/*
** Error Handling
*/
void				throw_generic_error(char *problem_name);
int					throw_illegal_option(char f);

/*
** Modes
*/
char				*get_readable_mode(mode_t mode);

/*
** Sorting
*/
t_file				*sort(t_file *list, int (*f)(t_file *a, t_file *b));

/*
** Output
*/
void				print_file(t_file *file);
void				print_directory(t_file *list);
void				print_total(t_file *list);
t_file				*set_widths(t_file *single);

#endif
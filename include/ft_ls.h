/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtarasiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 11:15:12 by vtarasiu          #+#    #+#             */
/*   Updated: 2018/07/13 17:15:31 by vtarasiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>

# include "../printf/include/ft_printf.h"
# include "../libft/libft.h"

# define F_LONG       1
# define F_ALL        2
# define F_SORTT      4
# define F_SORTR      8
# define F_RECUR     16
# define F_COLOR     32
# define F_DFILE     64
# define F_NSORT    128
# define F_SORTS    256
# define F_SORTA    512
# define F_SORTC   1024
# define F_SHOWE   2048
# define F_SHOWAT  4096
# define F_COLUMN  8192
# define F_ONEPER 16384
# define F_ACROSS 32768

# define IS_CURR(d) (ft_strlen(d) == 1 && (d)[0] == '.')

/*
** listxattr
** getxattr
** time
** ctime
** perror
** strerror
** exit
*/

unsigned int		g_flags;
struct s_params		g_param;

typedef struct		s_file
{
	char			*filename;
	char			*path;
	char			*full_name;
	char			*whereto;
	dev_t			dev;
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

struct				s_params
{
	int				linkw;
	int				bytew;
	int				userw;
	int				groupw;
	int				majorw;
	int				minorw;
	int				ttyw;
	int				ttycolumnw;
	int				ttyperline;
};

typedef int			(*t_sort_func)(t_file *, t_file *);

/*
** Generic Utilities
*/
char				*create_path(char *oldpath, char *filename);
void				stat_read_print(char **names);
int					does_cycle(char *pth);
/*
** Hello
*/
void				free_file(t_file *f);
void				free_list(t_file *list);
void				free_array(char **array);
int					parse_flags(int count, char **str);

t_file				*get_directory_contents(char *dirname, DIR *dir);
t_file				*create_file(struct stat *s, char *filename, char *path);
void				clear_widths(void);
char				*strings_join(char *delimiter, ...);
int					needs_dir_treatment(char *name, struct stat *s,
										int *status, int *is_ln);
int					needs_file_treatment(char *name, struct stat *s,
								const int *status, const int *is_ln);
int					is_link(char *name);
char				**filter_errors(char **names, int argc);
char				**filter_plain_files(char **names, int argc);
/*
** List manipulations
*/
void				list_add(t_file **head, t_file **tail, t_file *to_add);
t_file				*list_swap(t_file *list, t_file *first, t_file *second);

/*
** Error Handling
*/
int					throw_illegal_option(char f);

/*
** Modes
*/
char				*get_readable_mode(t_file *file);

/*
** Sorting
*/
t_sort_func			get_sort(void);
t_file				*sort(t_file *list, int (*compare)(t_file *a, t_file *b));
int					compare_by_filename(t_file *a, t_file *b);
int					compare_by_mtime(t_file *a, t_file *b);
int					compare_by_ctime(t_file *a, t_file *b);
int					compare_by_atime(t_file *a, t_file *b);
int					compare_by_size(t_file *a, t_file *b);

/*
** Output
*/
void				print_file(t_file *file);
void				print_directory(t_file *list);
void				print_in_columns(t_file *list);
t_file				*set_widths(t_file *single);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:07:05 by user42            #+#    #+#             */
/*   Updated: 2020/07/10 15:07:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# define SUCCESS			0
# define FAILURE			1
# define TRUE				1
# define FALSE				-1

# if __APPLE__
#  define FD_NONINT         250
#  define FD_DEBUG          251
# else
#  define FD_NONINT			259
#  define FD_DEBUG			260
# endif

# define PROJECT			"42sh"
# define NAME_SH			"42h-1.0$ "
# define COLOR_SH			"\e[0;32m"
# define COLOR_SUBPROMPT	"\e[0;31m"
# define USAGE				"Usage: 42sh -h [-d [path]] [file]\nexit\n"

/*
**********************************
************ ERROR ***************
**********************************
*/
# define STR_UNFOUND 		"Command not found"
# define STR_ISDIR			"Is a directory"
# define STR_ISNDIR			"Is not a directory"
# define STR_NOENT			"No such file or directory"
# define STR_ACCES			"Permission denied"
# define STR_LOOP			"Too many links"
# define STR_NTL			"File name too long"

/*
**********************************
************ FT_EX ***************
**********************************
*/
# define EX					"[Critical systeme error]\nexit\n"
# define EXMALLOC			"[Critical error] Cannot allocate memory\nexit\n"
# define EXEXEC				"[Critical Error] Execve fail\nexit\n"
# define EXFD				"[Critical Error] Bad file descriptor\nexit\n"
# define EXFD2				"Bad file descriptor\n"
# define EXUEPTD			"Unexpected error occurred... Shall leave\nexit\n"

# include "struct.h"
# include <stdint.h>
# include <stddef.h>

uint8_t		protect_fd(int8_t value);
void		print_ressource(char *rsc);
void		print_features(void);
void		init_builtin_map(t_hash_map *map);
void		build_prompt_ps1(uint8_t update);
int			lexer_routine(char **line, t_lexer *lexer);
int			parser_routine(t_lexer *lexer, t_parser *parser);
int			line_edition_routine(char **line);
int			eval_routine(t_parser *parser);
int			analyzer_routine(t_and_or *and_or);
void		set_var(t_cfg *shell);
void		exit_routine(t_cfg *shell, uint8_t ret);
void		ft_ex(char *error);
void		protect_malloc(void *malloc);
void		clean_cfg(t_cfg *shell);
void		del_struct_tvar(void *del, size_t u);
void		set_signal_ign(void);
t_cfg		*init_shell(char **env, char **av, int ac);
t_cfg		*init_cfg(char **env, char **av, int ac);
t_cfg		*cfg_shell(void);
uint32_t	path_errors(char *path, uint8_t check_dir, uint32_t right);
uint8_t		c_enametoolong(char *path);
uint8_t		c_isdir(char *path);
uint8_t		c_eacces(char *path, uint32_t right);
uint8_t		c_eloop(char *path);
uint8_t		c_enoent(char *path);
char		*create_abs_path(char *s);
uint32_t	check_access(char *path, int right);
void		set_signal_child(void);
void		set_signal_ign(void);

#endif

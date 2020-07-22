/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:07:05 by user42            #+#    #+#             */
/*   Updated: 2020/07/10 15:08:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdint.h>
# include <sys/types.h>
# include <termios.h>

# define L_BUFF_SIZE	256
# define EXP_BSIZE	200

typedef struct s_list	t_list;
typedef struct s_dlist	t_dlist;
typedef struct s_hash_map	t_hash_map;

typedef struct	s_cfg
{
	struct termios	term_origin;
	uint8_t			interactive;
	pid_t			pid;
	t_list			*env;
	t_list			*intern;
	t_list			*sp;
	t_list			*job;
	t_dlist			*history;
	t_hash_map		*map;
	t_hash_map		*input_map;
	t_hash_map		*test_bin;
	t_hash_map		*test_un;
	t_hash_map		*hist_map;
	t_hash_map		*builtin_map;
	uint32_t		cur_job;
	char			*file;
	uint8_t			active_job;
	int32_t			debug;
	int				hist_nb;
	int				hist_start;
	t_list			*alias;
	t_list			*alias_cpy;
	int				alias_rec;
	char			*clipboard;
}				t_cfg;

/*
** LEXER
*/
typedef enum	e_token_type
{
	TOKEN,
	WORD,
	ASSIGNMENT_WORD,
	NEWLINE,
	IO_NUMBER,
	AND_IF,
	AMP,
	OR_IF,
	PIPE,
	SEMI,
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	LESSAND,
	GREATAND,
	DLESSDASH,
}				t_token_type;

typedef enum	e_char_type
{
	C_INHIBITOR,
	C_CONTROL,
	C_REDIR,
	C_NEWLINE,
	C_DIGIT,
	C_EXP,
	C_BLANK,
	C_EOI,
	C_BRACK,
	C_EQU,
	C_HASH,
	C_OTHER,
}				t_char_type;

typedef enum	e_lexer_flag
{
	F_BLANK = 0,
	F_DQUOTE,
	F_SQUOTE,
	F_BSLASH,
	F_HEREDOC,
	F_PAREXP,
	F_BRACKEXP,
	F_HD_DELIM
}				t_lexer_flag;

typedef struct	s_token
{
	char				*str;
	t_token_type		type;
	size_t				len;
}				t_token;

typedef enum	e_lexer_state
{
	S_TK_START,
	S_HD_BODY,
	S_AMP_PIPE,
	S_TK_REDIR,
	S_EXP,
	S_TK_WORD,
	S_IO_NUMBER,
	S_FLAG,
	S_COMMENT
}				t_lexer_state;

typedef struct	s_here_queue
{
	t_token				*token;
	char				*delim;
}				t_here_queue;

typedef struct	s_lexer
{
	char				**src;
	char				*curr;
	t_lexer_state		state;
	t_list				*token_lst;
	t_token				*curr_token;
	char				buffer[L_BUFF_SIZE];
	int					buff_i;
	int					flags;
	t_list				*here_queue;
	t_here_queue		*curr_here;
	t_list				*flag_queue;
	t_lexer_flag		*curr_flag;
}				t_lexer;

/*
** PARSER
*/

typedef enum	e_parser_state
{
	S_PARSER_SYNTAX_ERROR,
	S_PARSER_TABLE_START,
	S_PARSER_CMD_START,
	S_PARSER_CMD_ARGS,
	S_PARSER_REDIR,
	S_PARSER_ASSIGN,
	S_PARSER_IO_NUMBER,
	S_PARSER_DELIM,
	S_PARSER_ARG_ASSIGN,
	S_PARSER_ANDIF_PIPE
}				t_parser_state;

typedef struct	s_assignment
{
	char			*var;
	char			*val;
}				t_assignment;

typedef struct	s_redir
{
	char			*delim;
	char			*io_num;
	t_token_type	type;
	char			*file;
}				t_redir;

typedef struct	s_simple_cmd
{
	char			*cmd_name;
	t_list			*args;
	char			**av;
	t_list			*redir;
	t_list			*curr_redir;
	t_list			*assign;
	t_list			*curr_assign;
}				t_simple_cmd;

typedef struct	s_and_or
{
	char			*str;
	t_list			*s_cmd;
	t_list			*curr_s_cmd;
	t_token_type	type;
	int				background;
}				t_and_or;

typedef struct	s_cmd_table
{
	t_list			*and_or;
	t_list			*curr_and_or;
}				t_cmd_table;

typedef struct	s_parser
{
	int				state;
	int				prev_state;
	int				space_flag;
	t_token_type	pmt_prefix;
	t_list			*table;
	t_list			*curr_table;
}				t_parser;

/*
** ANALYZER
*/

typedef struct	s_exp
{
	char			buf[EXP_BSIZE];
	int				i;
	int				quote;
	int				bs;
	int				assign;
	char			*param;
	char			*word;
	char			*res;
}				t_exp;

/*
** SELECT
*/

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_line_lst
{
	struct s_line_lst	*prev;
	struct s_line_lst	*next;
	char				*str;
	int					len;
	int					nb_lines;
}				t_line_lst;

typedef struct	s_cs_line
{
	int				line_col;
	int				col;
	int				row;
	int				min_col;
	int				min_row;
	int				scroll;
	int				max_scroll;
	int				tty;
	t_point			screen;
	char			*input;
	int				sig_int;
	int				sig_eof;
	int				ctrl_r;
	int				cr;
	char			*prompt;
	char			*prompt_color;
	t_dlist			*history;
	t_point			clipb;
	char			*old_history;
	int				read_error;
}				t_cs_line;

/*
** EXEC
*/

typedef enum	e_err_flag
{
	E_OK = 0,
	E_NAMETOOLONG,
	E_NOENT,
	E_LOOP,
	E_NOTDIR,
	E_ACCES,
}				t_err_flag;

typedef struct	s_var
{
	char		**ctab;
}				t_var;

typedef struct	s_pipe
{
	int32_t		fd[2];
	uint8_t		tmp;
}				t_pipe;

typedef struct	s_process
{
	char		*cmd;
	char		**av;
	char		*path;
	char		*message;
	pid_t		pid;
	uint8_t		ret;
	uint8_t		status;
	int16_t		std[2];
	uint32_t	setup;
	t_list		*fd;
	t_list		*redir;
	t_list		*env;
	t_list		*assign;
}				t_process;

typedef struct	s_job
{
	uint8_t			id;
	char			*cmd;
	t_list			*process;
	pid_t			pgid;
	uint8_t			fg;
	t_pipe			pipe;
	uint8_t			status;
	uint8_t			ret;
	int16_t			std[3];
	struct termios	term_eval;
}				t_job;

#endif

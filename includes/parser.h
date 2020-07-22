/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:07:05 by user42            #+#    #+#             */
/*   Updated: 2020/07/10 15:07:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"

int				ft_parser(t_lexer *lexer, t_parser *parser);
int				p_tokeniter(t_list *token, t_parser *parser,
		int (*table_builder[10][17])(t_token *, t_parser *));

int				p_expand_alias(t_token *token, t_parser *parser);
void			reset_alias_list(void);

t_cmd_table		*init_cmd_table(void);
t_and_or		*init_and_or(void);
t_simple_cmd	*init_simple_cmd(void);
t_assignment	*init_assignment(void);
t_redir			*init_redir(void);

int				p_cmd_name(t_token *token, t_parser *parser);
int				p_file_name(t_token *token, t_parser *parser);
int				p_add_arg(t_token *token, t_parser *parser);
int				p_add_assign_arg(t_token *token, t_parser *parser);

int				p_create_redir(t_simple_cmd *cmd);
int				p_add_io_num(t_token *token, t_parser *parser);
int				p_add_redir(t_token *token, t_parser *parser);
int				p_add_redir_delim(t_token *token, t_parser *parser);

int				p_add_assign(t_token *token, t_parser *parser);
int				p_assign_val(t_token *token, t_parser *parser);
int				p_assign_join(t_token *token, t_parser *parser);

int				p_add_and_or(t_token *token, t_parser *parser);

int				p_add_cmd(t_token *token, t_parser *parser);

void			print_cmd_table(t_list *table);
void			print_parser(t_parser *parser);
int				syn_err(t_token *token, t_parser *parser);

int				p_add_io_num(t_token *token, t_parser *parser);

int				p_add_table(t_parser *parser);

int				p_add_amp(t_token *token, t_parser *parser);

void			p_make_args_tab(t_parser *parser);

void			**lst_to_tab(t_list *lst);

int				is_digitstr(char *str);

void			del_assign(void *data, size_t size);
void			del_redir(void *data, size_t size);
void			del_simple_cmd(void *data, size_t size);
void			del_and_or(void *data, size_t size);
void			del_cmd_table(void *data, size_t size);

void			p_init_start_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_start_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_args_wait_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_redir_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_assign_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_io_nbr_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_delim_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_arg_assign_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_syn_err_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_andif_pipe_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_cmd_wait_state(int (*table_builder[10][17])(t_token *,
						t_parser *));
void			p_init_state_machine(int (*table_builder[10][17])(t_token *,
						t_parser *));

int				p_set_start_state(t_token *token, t_parser *parser);
int				p_skip(t_token *token, t_parser *parser);
int				p_add_redir_delim(t_token *token, t_parser *parser);
void			init_parser(t_parser *parser);

int				syn_err(t_token *token, t_parser *parser);
int				p_skip(t_token *token, t_parser *parser);
int				p_set_start_state(t_token *token, t_parser *parser);
char			*p_get_prompt_prefix(t_parser *parser);

#endif

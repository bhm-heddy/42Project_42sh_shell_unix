/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:07:03 by user42            #+#    #+#             */
/*   Updated: 2020/07/10 15:07:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYZER_H
# define ANALYZER_H

# include "struct.h"
# include <pwd.h>

int		analyzer_routine(t_and_or *and_or);

char	*get_redir_str(t_list *redir_lst);
char	*get_args_str(char **args);

void	a_set_jobs_str(t_and_or *and_or);

void	a_remove_leading_tabs(t_and_or *and_or);

int		a_make_args_tab(t_and_or *and_or);

void	**args_to_tab(t_list *lst, char *cmd);

int		exp_err(char *word);
int		print_error_parameter(t_exp *exp, char **str, char *param);

int		word_expansions(t_simple_cmd *cmd);
int		exp_main(char **word, int assign);

char	*exp_getenv(char *str, int type, int hash);

void	exp_substitute(t_exp *exp, char *str);
void	init_exp(t_exp *exp);
void	free_exp_content(t_exp *exp);
void	exp_flush_buf(t_exp *exp, char **str);
void	exp_add_to_buf(t_exp *exp, char **str, char **res);

void	field_splitting(t_simple_cmd *cmd);

int		parse_param_exp(char **word, t_exp exp);

int		rec_param_exp(t_exp *exp, char **str);

char	*resolve_parameter(char *str, int hash);
int		resolve_colon_param(char **str, t_exp *exp, char *param);
int		resolve_brace_param(char **str, t_exp *exp, char *param);
int		resolve_pattern_param(char **str, t_exp *exp, char *param);

int		substitute_parameter(t_exp *exp, char **str);
int		substitute_word(t_exp *exp, char **str);
int		assign_word(t_exp *exp, char **str, char *param);
int		substitute_null(t_exp *exp, char **str);
void	substitute_pattern(t_exp *exp, int type);

int		rec_word_parse(t_exp *exp, char **str);
int		skip_word(t_exp *exp, char **str);

void	find_tilde_exp(char **word, t_exp exp);
int		parse_tilde_exp(char **string, t_exp *exp, int assign);

void	find_tilde_exp_assign(char **word, t_exp exp);

char	*a_quote_removal(char **str);

#endif

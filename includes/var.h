/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:07:05 by user42            #+#    #+#             */
/*   Updated: 2020/07/10 15:07:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

# include <stdint.h>

typedef struct s_list	t_list;

t_list		*find_var(t_list *lst, char *var);
char		*find_var_value(t_list *env, char *name);
void		cpy_var_list(void *dst, void *src);
void		create_lst_var(t_list **lst, char **t);
void		setvar_update(t_list *lst, char *value);
void		setvar_add(t_list **lst, char *var, char *value);
void		unsetvar_del(void *delete, size_t size);
int32_t		unsetvar_find(void *elem, void *var);
char		**create_tab_var(t_list *list, int count);
uint8_t		several_setvar(t_list **var, char *str);
uint8_t		ft_print_var_lst(t_list *lst, uint8_t i);
uint8_t		ft_setvar(t_list **lst, char *name, char *value);

#endif

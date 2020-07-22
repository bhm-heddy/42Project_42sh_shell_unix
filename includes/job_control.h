/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:07:04 by user42            #+#    #+#             */
/*   Updated: 2020/07/10 15:07:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

uint8_t		ft_jobs2(t_job *j, t_process *p);
void		insert_running_job(t_cfg *shell, t_list *ljob, t_job *jc);
void		job_is_running(t_job *j);
uint8_t		find_target(t_list *ljob, char *wanted, t_job **target, char *blt);
int32_t		focus_job(void *data1, void *data2);
void		nb_job_active(t_cfg *shell);
void		job_become_cur(t_cfg *shell, t_job **j);
void		one_process_change(t_process *p);
int32_t		job_has_finish(void *job, void *status);
void		add_job_cfg(t_job *job);
void		set_job_background(t_job *job);
void		ft_cpy_job(t_job *job, t_job *copy);
void		check_child(t_cfg *shell, t_list *lstjob);
void		aplylyse_wstatus(t_process *p, int wstatus);
void		update_process(t_list *lst, pid_t child, int wstatus);
t_process	*find_process_by_status(t_list *lst, uint8_t want);
t_process	*find_process_by_pid(t_list *lst, pid_t child);
void		update_listjob(t_cfg *shell);
int16_t		get_job(t_list *ljob, char *ope, t_job **j, uint8_t *curr);

#endif

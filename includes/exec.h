#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

# define ERROR					48

# if __APPLE__
#  define SAVE_IN				252
#  define SAVE_OUT				253
#  define SAVE_ERR				254
# else
#  define SAVE_IN				256
#  define SAVE_OUT				257
#  define SAVE_ERR				258
# endif

/*
*****************************************************
******************* Process SETUP *******************
*****************************************************
*/
# define PIPE_ON				0x1
# define EXEC					0x2
# define BUILTIN				0x4
# define NOCMD					0x8
# define R_ERROR				0x10
# define P_ERROR				0x20
# define E_BADFD				0x40
# define E_UNFOUND				0x80
# define E_ISDIR				0x100
# define E_NOENT				0x200
# define E_ACCES				0x400
# define E_LOOP					0x800
# define E_NTL					0x1000
# define B_SPECIAL				0x2000
# define B_ECHO					0
# define B_CD					0x4000
# define B_SET					0xE000
# define B_UNSET				0x12000
# define B_HASH					0x14000
# define B_EXIT					0x1A000
# define B_JOBS					0x1C000
# define B_FG					0x20000
# define B_BG					0x24000
# define B_TYPE					0x28000
# define B_EXPORT				0x2E000
# define B_ALIAS				0x30000
# define B_UNALIAS				0x34000
# define B_TEST					0x38000
# define B_FC					0x3C000

/*
*****************************************************
***************** Process/Job STATUS ****************
*****************************************************
*/
# define RUNNING				1
# define WAITING				2
# define STOPPED				4
# define KILLED					8
# define FAILED					16
# define COMPLETED				32

/*
*****************************************************
***************** Handler SIGNAL ********************
*****************************************************
*/
# define S_SIGHUP				"Hangup"
# define S_SIGINT				""
# define S_SIGQUIT				"Quit"
# define S_SIGILL				"Illegal instruction"
# define S_SIGTRAP				"Trace/Breakpoint trap"
# define S_SIGABRT				"Aborted"
# define S_SIGBUS				"Bus Error"
# define S_SIGFPE				"Floating point exception"
# define S_SIGKILL				"Killed"
# define S_SIGUSR1				"User defined signal 1"
# define S_SIGSEGV				"Segmentation fault"
# define S_SIGUSR2				"User defined signal 2"
# define S_SIGALRM				"Alarm clock"
# define S_SIGTERM				"Terminated"
# define S_SIGXCPU				"CPU time limit exceeded"
# define S_SIGXFSZ				"File size limit exceeded"
# define S_SIGPROF				"Profiling timer expired"
# define S_SIGSYS				"Bad system call"
# define S_SIGTTOU				"Stopped(SIGTTOU)"
# define S_SIGTTIN				"Stopped(SIGTTIN)"
# define S_SIGTSTP				"Stopped(SIGTSTP)"
# define S_SIGSTOP				"Stopped(SIGSTOP)"

# define FG_USG 				"fg: usage: fg [job_spec]"
# define JOB_USG 				"jobs : usage: jobs [-lp] [job_id...]"
# define BG_USG 				"bg: usage: bg [job_spec ...]"

/*
*****************************************************
******************* BUILTIN *************************
*****************************************************
*/

uint8_t			ft_unalias(t_process *p);
uint8_t			ft_alias(t_process *p);
uint8_t			ft_fc(t_process *p);
uint8_t			ft_export(t_process *p);
uint8_t			ft_bg(t_process *p);
uint8_t			ft_fg(t_process *p);
uint8_t			ft_echo(t_process *p);
uint8_t			ft_type(t_process *p);
uint8_t			ft_set(t_process *p);
uint8_t			ft_unset(t_process *p);
uint8_t			ft_exit(t_process *p);
uint8_t			ft_hash(t_process *p);
uint8_t			ft_jobs(t_process *p);
uint8_t			ft_test(t_process *p);
uint8_t			ft_cd(t_process *p);

int8_t			protect_job(int8_t update);
uint8_t			print_jobs(t_cfg *shell, t_process *p, char opt, int32_t ac);
uint8_t			print_all_jobs(t_cfg *shell, t_list *jobs, char opt);
char			*ft_strcut(char *str, char *delim, unsigned int field);
int				check_whole_path(char *path);
char			cd_getopt(char **str, int *i);
int				cd_home(t_process *p);
char			*cd_setcurpath(t_list **env, char *opr);
int				cd_logically(t_list **env, char *curpath, char *opr);
int				chdir_errors(char *curpath, char *opr, char *pwd, char *oldpwd);
char			*ft_strrep(char *str, char *rem, char *rep);
char			*ft_pathjoin(char *str1, char *str2);
char			*ft_strcut(char *str, char *delim, unsigned int field);
char			*cd_del_dotcomponents(char *curpath,
char			*opr, char **pwd, t_list **env);
int				display_cd_errors(char *error);
int				check_chdir_errors(char **error, char *path,
									char *opr);
int				cd_change_directory(t_list **env, char *curpath,
									char *opr, char *pwd);
void			hash_usage_error(void);
int				hash_not_found(char *cmd);
void			print_alias(t_var *var);
int				print_single_alias(char *name);
void			print_all_alias(void);
t_list			*search_alias_list(char *name, t_list *list);
t_var			*search_alias_var(char *name, t_list *list);
char			*search_alias_value(char *name, t_list *list);
int				check_int_args(char *s1, char *s2);
void			routine_fg_job(t_cfg *shell, t_job *j);

char			**retrieve_ops(char **p_av, int *i, int *bang);
int				check_closing_bracket(char **av);
void			init_test_op(void);
int				check_closing_bracket(char **av);
char			**retrieve_ops(char **p_av, int *i, int *bang);
uint8_t			test_write_file(char *path);
uint8_t			test_len_string(char *s1);
uint8_t			test_read_file(char *path);
uint8_t			test_regular_file(char *path);
uint8_t			test_setgid_file(char *path);
uint8_t			test_setuid_file(char *path);
uint8_t			test_size_file(char *path);
uint8_t			test_socket_file(char *path);
uint8_t			test_equal_string(char *s1, char *s2);
uint8_t			test_diff_string(char *s1, char *s2);
uint8_t			test_symlink_file(char *path);
uint8_t			test_char_file(char *path);
uint8_t			test_dir_file(char *path);
uint8_t			test_exec_file(char *path);
uint8_t			test_fifo_file(char *path);
uint8_t			test_entry_file(char *path);
uint8_t			test_equal_int(char *s1, char *s2);
uint8_t			test_greator_int(char *s1, char *s2);
uint8_t			test_greater_int(char *s1, char *s2);
uint8_t			test_lessor_int(char *s1, char *s2);
uint8_t			test_lesser_int(char *s1, char *s2);
uint8_t			test_diff_int(char *s1, char *s2);
uint8_t			test_bloc_file(char *path);

int				print_hist(int8_t *fl, char **av, int ac);
void			exec_hist(char *file);
int				edit_hist(int8_t *fl, char **av, int ac);
char			*get_hist_cmd(char *av, t_cfg *cfg);
void			reexecute_cmd(char **av, int ac);
char			*get_histfilename(void);
char			*create_tmphist(int8_t *fl, char **av, int ac);
uint8_t			fc_check_opt(t_process *p, int32_t *ac);
t_point			get_range(int8_t *fl, char **av, int ac, t_cfg *cfg);
int				check_range(char **av, int ac);
int				ft_intlen(int nb);
int				range_error(void);
int				fc_usage(void);
int				fc_bad_option(char *s);
int				fc_bad_usage(char *s);
int				fc_missing_arg(void);
int				fc_exec_cmd(char *cmd);
void			fc_hist_add(char *hist_cmd);
char			*get_edit_cmd(int8_t *fl, char *hist, char **av, int ac);
int				editor_launcher(char *cmd);
char			*get_cmd_by_oc(t_cfg *cfg, char *av);
char			*get_cmd_by_num(t_cfg *cfg, char *av);
void			get_pattern(char **av, int *ac, char **old, char **n);
void			del_fc_cmd(void);
void			get_hist_elem(t_dlist **hist, char **input, char *caps);

/*
*****************************************************
******************* TERMIOS *************************
*****************************************************
*/

void			term_create_eval(struct termios *origin, struct termios *eval);
uint8_t			set_termios(int32_t mode, struct termios *term);

/*
*****************************************************
******************* JOB *****************************
*****************************************************
*/
uint8_t			ft_eval(t_list *cmd_table);
void			cmd_to_job(t_cfg *shell, t_job *job, t_list *s_cmd, char *cmd);
uint8_t			run_job(t_cfg *shell, t_job *job, t_list *process);
void			wait_process(t_job *job);
t_list			*find_job_by_status(t_list *lst, uint8_t want);
void			builtin_save_fd(t_job *j);
void			builtin_restor_fd(t_job *j);
int16_t			get_job(t_list *ljob, char *ope, t_job **j, uint8_t *curr);

/*
*****************************************************
****************** PROCESS **************************
*****************************************************
*/

void			update_last_return(t_cfg *shell, uint8_t jret);
void			cpy_lst_process(void *copy, void *process);
uint8_t			builtin_process(t_process *p);
void			routine_process(t_cfg *shell, t_list *process, t_pipe *fd);
void			run_process(t_cfg *shell, t_job *j, t_process *p);
void			process_type(t_process *p);
int32_t			has_running(t_list *lst);
int32_t			has_stopped(t_list *lst);
void			any_slash(t_list *env, t_process *p, uint32_t *err);
void			with_slash(t_process *p, uint32_t *err);
uint32_t		builtin_search(t_cfg *shell, t_process *p);
t_process		*find_process_by_status(t_list *lst, uint8_t want);
t_process		*find_process_by_pid(t_list *lst, pid_t child);
void			process_assign(t_cfg *shell, t_process *p, t_list *assignment);

/*
*****************************************************
****************** REDIR & FD ***********************
*****************************************************
*/
uint32_t		process_redir(t_process *p, t_list *redir);
void			do_my_dup2(int16_t fd1, int16_t fd2);
uint8_t			bad_fd(int fd);
uint32_t		path_gearing(t_redir *r, char **path, int right);
uint8_t			add_fd_process(t_list **fd, int16_t source, int16_t target);
void			do_redir(t_list *fd);
uint8_t			patch_redir(t_list *process);
void			close_fd(t_list *lst);
void			job_redir(t_list *process);
void			do_redir(t_list *fd);
int32_t			create_fd_null(void);
uint32_t		right_fifo(char *path, uint32_t *right);
void			do_pipe(t_process *p);

/*
*****************************************************
**************** RERROR HANDLIN *********************
*****************************************************
*/
uint32_t		redir_errors_handling(t_process *p, uint32_t error,
										char *info, int32_t fd);
uint32_t		process_errors_handling(t_process *p, uint32_t	err);

/*
*****************************************************
***************** SIGNAL ****************************
*****************************************************
*/
char			**create_message_signal(char **tab);
uint8_t			print_message_signal(uint8_t sig, t_job *j, t_process *p);

/*
*****************************************************
*************** DESTRUCTOR **************************
*****************************************************
*/
void			routine_clean_job(void *del, size_t u);
void			del_struct_process(void *del, size_t u);
void			del_struct_job(void *del, size_t u);

/*
*****************************************************
***************** DEBUG *****************************
*****************************************************
*/
void			debug_print_job(int32_t fd_debug, t_job *j, char *where);
void			debug_print_all_process(t_list *process, char *where);
void			debug_print_all_job(t_list *job, char *where);
void			debug_print_everything(t_list *job, char *where);
void			debug_print_process(int32_t fd_debug, t_process *p,
									char *where);
#endif

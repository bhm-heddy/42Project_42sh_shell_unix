#include "libft.h"
#include "sh.h"
#include "exec.h"
#include <signal.h>
#include "line_edition.h"

void	kill_job_stopped(t_list *lst)
{
	t_job	*j;

	while (lst)
	{
		j = lst->data;
		if (j->status == STOPPED)
			kill(-j->pgid, SIGKILL);
		lst = lst->next;
	}
}

void	exit_routine(t_cfg *shell, uint8_t ret)
{
	kill_job_stopped(shell->job);
	if (shell->interactive &&
			(int)shell->term_origin.c_iflag != -1)
		set_termios(TCSADRAIN, &shell->term_origin);
	update_history_file(shell->history, shell);
	close(shell->debug);
	close(FD_NONINT);
	clean_cfg(shell);
	exit(ret);
}

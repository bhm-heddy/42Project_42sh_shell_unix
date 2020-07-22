#include "libft.h"
#include "exec.h"
#include "sh.h"

static int16_t	get_job_id(t_list *ljob, uint8_t nb, t_job **j, uint8_t *curr)
{
	while (ljob)
	{
		*curr += 2;
		*j = ljob->data;
		if ((*j)->id == nb)
			return (SUCCESS);
		ljob = ljob->next;
	}
	*j = NULL;
	return (FAILURE);
}

static int16_t	get_curr_job(t_list *ljob, uint8_t id, t_job **j, uint8_t *curr)
{
	while (ljob && id)
	{
		*curr += 2;
		*j = ljob->data;
		ljob = ljob->next;
		id--;
	}
	if (*j)
		return (SUCCESS);
	else
		return (FAILURE);
}

static int16_t	get_sstr_id(t_list *ljob, char *ope, t_job **j, uint8_t *curr)
{
	while (ljob)
	{
		*curr += 2;
		*j = ljob->data;
		if (ft_strstr((*j)->cmd, ope))
			return (SUCCESS);
		ljob = ljob->next;
	}
	return (FAILURE);
}

static int16_t	get_str_id(t_list *ljob, char *ope, t_job **j, uint8_t *curr)
{
	int8_t	i;

	while (ljob)
	{
		i = 0;
		*j = ljob->data;
		while (ope[i] && (*j)->cmd[i] && ope[i] == (*j)->cmd[i])
		{
			*curr += 2;
			i++;
		}
		if (!ope[i])
			return (SUCCESS);
		ljob = ljob->next;
	}
	*j = NULL;
	return (FAILURE);
}

int16_t			get_job(t_list *ljob, char *ope, t_job **j, uint8_t *curr)
{
	int8_t	ret;

	ret = 0;
	if (!ft_strcmp(ope, "%"))
		return (get_curr_job(ljob, 1, j, curr));
	if (*ope == '%')
		ope++;
	if (str_is_digit(ope))
		return (get_job_id(ljob, ft_atoi(ope), j, curr));
	if (*ope == '+' || *ope == '%')
		return (get_curr_job(ljob, 1, j, curr));
	if (*ope == '-')
		return (get_curr_job(ljob, 2, j, curr));
	if (*ope == '?')
		return (get_sstr_id(ljob, ++ope, j, curr));
	return (get_str_id(ljob, ope, j, curr));
}

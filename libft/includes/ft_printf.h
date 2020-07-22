#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <inttypes.h>
# include "libft.h"

# define BUF_SIZE		100

# define C_RED			"\033[0;31m"
# define C_BRED			"\033[1;31m"
# define C_GREEN		"\033[0;32m"
# define C_BGREEN		"\033[1;32m"
# define C_YELLOW		"\033[0;33m"
# define C_BYELLOW		"\033[1;33m"
# define C_BLUE			"\033[0;34m"
# define C_BBLUE		"\033[1;34m"
# define C_MAGENTA		"\033[0;35m"
# define C_BMAGENTA		"\033[1;35m"
# define C_CYAN			"\033[0;36m"
# define C_BCYAN		"\033[1;36m"
# define C_EOC			"\033[0m"

typedef struct		s_printf
{
	char			*fmt;
	char			*err_ptr;
	int				fd;
	char			**str;
	int				str_n;
	char			type;
	va_list			ap;
	char			buf[BUF_SIZE];
	int				buf_len;
	short			flags;
	short			f_index;
	int				width;
	int				prec;
	unsigned		conv;
	int				printed;
	int				pad;
	unsigned int	base;
	int				ret;
	void			*disp;
	int				disp_set;
	int				as;
}					t_printf;

void				read_arg(t_printf *data);
void				read_flags(t_printf *data);
void				read_width(t_printf *data);
void				read_prec(t_printf *data);
void				read_length_mod(t_printf *data);
void				read_conv_spec(t_printf *data);

void				flush(t_printf *data);
void				buffer(void *str, t_printf *data, size_t len);
void				add_pad(t_printf *data, int n);
int					init_type(t_printf *data, int fd, char **str, int str_n);
void				xtoa_base(uintmax_t val, int base,
		char s[21], t_printf *data);
void				init_dispatcher(t_printf *data,
		void (*disp[11])(t_printf *));
void				init_data(t_printf *data, const char *format, int as);

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_snprintf(char *str, size_t size,
		const char *format, ...);
int					ft_asprintf(char **ret, const char *format, ...);

void				conv_float(t_printf *data);
void				conv_int(t_printf *data);
void				conv_uint(t_printf *data);
void				conv_char(t_printf *data);
void				conv_str(t_printf *data);
void				conv_ptr(t_printf *data);
void				conv_color(t_printf *data);
void				conv_esc(t_printf *data);

#endif

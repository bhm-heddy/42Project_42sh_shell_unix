#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1083

int					get_next_line(const int fd, char **line);

typedef struct		s_gnl
{
	char			**content;
	int				num;
	struct s_gnl	*next;
}					t_gnl;
#endif

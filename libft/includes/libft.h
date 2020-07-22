#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>

# define CVTBUFSZ 200

typedef struct	s_dlist
{
	void			*data;
	size_t			size;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;

typedef struct	s_list
{
	void			*data;
	size_t			size;
	struct s_list	*next;
}				t_list;

typedef struct	s_hash_map
{
	uint32_t		size;
	t_list			**slots;
}				t_hash_map;

typedef struct	s_hash_node
{
	char			*key;
	void			*data;
}				t_hash_node;

typedef union	u_modf
{
	double				f;
	long long unsigned	i;
}				t_modf;

/*
** CALCUL
*/

char			*ft_fcvt(double val, int ndigits, int *decpt, char *buf);
double			ft_modf(double val, double *integral);
int				ft_recursive_power(int nb, int pw);
int				ft_sqrt(int nb);
char			*ft_itoa(int n);

/*
** CONVERSION
*/

int				ft_atoi(const char *str);
void			ft_ftoa(double val, int prec, char res[CVTBUFSZ]);
char			*ft_itoa(int n);

/*
** HASH
*/

t_hash_map		*ft_hash_init(uint32_t size);
uint32_t		ft_hash_str(t_hash_map *map, char *key);
int				ft_hash_add(t_hash_map *map, char *key, void *value,
				void (*del)(void *));
t_hash_node		*ft_hash_get_node(t_hash_map *map, char *key);
void			*ft_hash_lookup(t_hash_map *map, char *key);
t_list			*ft_hash_get_list(t_hash_map *map, char *key);
void			ft_hash_delone(t_hash_map *map, char *key, void (*del)(void *));
void			ft_hash_del_list(t_list **lst, void (*del)(void *));
void			ft_hash_del_map(t_hash_map **map, void (*del)(void *data));
void			ft_hash_reset(t_hash_map **map,
				void (*del)(void *data), uint32_t size);

/*
** INPUT
*/

int				ft_getopt(int *ac, int *i, char **const av, char *flags);

/*
** LIST
*/

t_dlist			*ft_dlstnew(void *content, size_t content_size);
void			ft_dlstdelone(t_dlist **alst);
void			ft_dlstdel(t_dlist **alst);
void			ft_dlstaddtail(t_dlist **alst, t_dlist *new);
void			ft_lst_join(t_list *lst1, t_list **lst2, int refresh);
t_list			*ft_lstnew(void const *data, size_t size);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
int				ft_lsthave(t_list *lst, int (*f)(t_list *elem));
t_list			*ft_lstdup(t_list *lst, size_t size,
		void (*cplst)(void *, void *));
void			ft_lst_push_front(t_list **begin, void *data,
		size_t size);
void			ft_lst_push_back(t_list **begin, void *data,
		size_t size);
int				ft_lstdelif(t_list **begin, void *data,
		int (*f)(void *, void *), void (*del)(void *, size_t));
t_list			*ft_lstpush(t_list **alst, void *data, size_t size);
void			ft_lstaddtail(t_list **alst, t_list *new);
t_list			*ft_lstgettail(t_list *alst);
void			ft_lstdeltail(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelhead(t_list **alst, void (*del)(void*, size_t));
uint32_t		ft_lstcount(t_list *elem);
void			ft_lstfree(void *data, size_t size);

/*
** MEMORY
*/

void			ft_bzero(void *s, size_t n);
void			ft_del_tab(void **tabi);
void			*ft_memalloc(size_t size);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_memdel(void **ap);
unsigned char	ft_swap_bits(unsigned char octet);

/*
** OUTPUT
*/

void			ft_print_bits(unsigned char nb);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);

/*
** STRING
*/

int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strisdigit(char *s);
int				ft_strisalpha(char *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_strchri(const char *s, int c);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			**ft_tabdup(char **t);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strrchri(const char *s, int c);
int				ft_strdigit(char *s1);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *h, const char *n, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strselect(char *str, char c);
char			**ft_strsplit(char const *s, char *c);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_strdel(char **as);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
size_t			ft_wcharlen(unsigned wc);
size_t			ft_wstrlen(unsigned *str);
int				ft_strichr(char *s, int c);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strnlclnjoin(char const *s1, char const *s2, size_t n);
char			*ft_strclnjoin(char const *s1, char const *s2);
char			*ft_strlclnjoin(char const *s1, char const *s2);
int				ft_isname(char *str);
char			*ft_strtrimoc(char const *si, char oc);
int				str_is_digit(char *ope);

/*
** SYSTEM
*/

int				ft_isdir(char *path, int link);
char			*ft_which(char *paths, char *exec);

#endif

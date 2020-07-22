NAME = libft.a
NAMEDB = libft_db.a

# Reset
NC = \033[0m

# Regular Colors
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m


#-------------------------Memory-------------------------#
SRCS += ft_bzero.c
SRCS += ft_memccpy.c
SRCS += ft_memcmp.c
SRCS += ft_memdel.c
SRCS += ft_memset.c
SRCS += ft_memalloc.c
SRCS += ft_memchr.c
SRCS += ft_memcpy.c
SRCS += ft_memmove.c
SRCS += ft_swap_bit.c
SRCS += ft_del_tab.c

#-------------------------Output-------------------------#
SRCS += ft_print_bits.c
SRCS += ft_putchar_fd.c
SRCS += ft_putendl_fd.c
SRCS += ft_putnbr_fd.c
SRCS += ft_putstr_fd.c
SRCS += ft_putchar.c
SRCS += ft_putendl.c
SRCS += ft_putnbr.c
SRCS += ft_putstr.c

#-------------------------Input--------------------------#
SRCS += ft_getopt.c
SRCS += get_next_line.c

#-------------------------String-------------------------#
SRCS += ft_strisdigit.c
SRCS += ft_isalnum.c
SRCS += ft_strisalpha.c
SRCS += ft_isalpha.c
SRCS += ft_isascii.c
SRCS += ft_isdigit.c
SRCS += ft_isprint.c
SRCS += ft_strcat.c
SRCS += ft_strchr.c
SRCS += ft_strchri.c
SRCS += ft_strclnjoin.c
SRCS += ft_strclr.c
SRCS += ft_strcmp.c
SRCS += ft_strcpy.c
SRCS += ft_strdel.c
SRCS += ft_strdigit.c
SRCS += ft_strdup.c
SRCS += ft_strequ.c
SRCS += ft_striter.c
SRCS += ft_striteri.c
SRCS += ft_strjoin.c
SRCS += ft_strjoinfree.c
SRCS += ft_strlcat.c
SRCS += ft_strlclnjoin.c
SRCS += ft_strlen.c
SRCS += ft_strmap.c
SRCS += ft_strmapi.c
SRCS += ft_strncat.c
SRCS += ft_strnlclnjoin.c
SRCS += ft_strncmp.c
SRCS += ft_strncpy.c
SRCS += ft_strndup.c
SRCS += ft_strnequ.c
SRCS += ft_strnew.c
SRCS += ft_strnstr.c
SRCS += ft_strrchr.c
SRCS += ft_strrchri.c
SRCS += ft_strselect.c
SRCS += ft_strsplit.c
SRCS += ft_strstr.c
SRCS += ft_strsub.c
SRCS += ft_strtrim.c
SRCS += ft_tolower.c
SRCS += ft_toupper.c
SRCS += ft_wcharlen.c
SRCS += ft_wstrlen.c
SRCS += ft_tabdup.c
SRCS += ft_isname.c
SRCS += ft_strtrimoc.c
SRCS += ft_str_is_digit.c

#-------------------------List-----------------------------#
SRCS += ft_lstadd.c
SRCS += ft_lstdel.c
SRCS += ft_lstdelif.c
SRCS += ft_lstdelone.c
SRCS += ft_lstiter.c
SRCS += ft_lstmap.c
SRCS += ft_lstnew.c
SRCS += ft_lstpushfront.c
SRCS += ft_lstpushback.c
SRCS += ft_lst_join.c
SRCS += ft_lstpush.c
SRCS += ft_lstaddtail.c
SRCS += ft_lstgettail.c
SRCS += ft_lstdeltail.c
SRCS += ft_lstdelhead.c
SRCS += ft_dlstaddtail.c
SRCS += ft_dlstnew.c
SRCS += ft_dlstdel.c
SRCS += ft_dlstdelone.c
SRCS += ft_lsthave.c
SRCS += ft_lstdup.c
SRCS += ft_lstcount.c
SRCS += ft_lstfree.c

#-------------------------Conversion-----------------------#
SRCS += ft_atoi.c
SRCS += ft_itoa.c
SRCS += ft_ftoa.c

#-------------------------Calcul----------------------------#
SRCS += ft_recursive_power.c
SRCS += ft_sqrt.c
SRCS += ft_fcvt.c
SRCS += ft_modf.c

#-------------------------ft_printf-------------------------#
SRCS += xprintf.c
SRCS += arg.c
SRCS += char.c
SRCS += colors.c
SRCS += float.c
SRCS += int.c
SRCS += misc.c
SRCS += misc2.c
SRCS += read.c
SRCS += uint.c

#-------------------------Systeme-------------------------#
SRCS += ft_which.c
SRCS += ft_isdir.c

#--------------------------Hash----------------------------#
SRCS += ft_hash_str.c
SRCS += ft_hash_del_list.c
SRCS += ft_hash_del_map.c
SRCS += ft_hash_delone.c
SRCS += ft_hash_get_list.c
SRCS += ft_hash_get_node.c
SRCS += ft_hash_init.c
SRCS += ft_hash_lookup.c
SRCS += ft_hash_add.c
SRCS += ft_hash_reset.c

#------------------------------------------------------------#

vpath %.c srcs/conversion
vpath %.c srcs/systeme
vpath %.c srcs/calcul
vpath %.c srcs/list
vpath %.c srcs/memory
vpath %.c srcs/output
vpath %.c srcs/input
vpath %.c srcs/string
vpath %.c srcs/hash
vpath %.c srcs/ft_printf/srcs

vpath %.h includes

PATHO = objs/
PATHS = srcs/
PATHI = includes/

INC += $(PATHI)/ft_printf.h
INC += $(PATHI)/get_next_line.h
INC += $(PATHI)/libft.h

CLEANUP = rm -rf
MKDIR = mkdir -p

CC = clang
COMPIL = $(CC) -c
COMPILDB = $(CC) -g -c

IFLAGS = -I$(PATHI)
CFLAGS = -Wall -Werror -Wextra $(IFLAGS)
DBFLAGS = -fsanitize=address $(CFLAGS)

OBJS = $(patsubst %.c, $(PATHO)%.o, $(SRCS))
OBJD = $(patsubst %.c, $(PATHO)db%.o, $(SRCS))

all : $(NAME)
debug : $(NAMEDB)

$(NAME) : $(PATHO) $(OBJS) Makefile $(INC)
	ar rc $@ $(OBJS)
	ranlib $@
	printf "\t\t\t$(GREEN)$@ is ready.\n$(NC)"

$(OBJS) : $(PATHO)%.o : %.c
	$(COMPIL) $(CFLAGS) $< -o $@
	printf "$(BLUE)  Compiling $<\n"

$(NAMEDB) : $(PATHO) $(OBJD)
	@ar rus $@ $(OBJD)
	@ranlib $@
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJD): $(PATHO)db%.o : %.c
	$(COMPILDB) $(DBFLAGS) $< -o $@
	printf "$(BLUE)Compiling $<       [DEBUG]\n$(NC)"

$(PATHO) :
	mkdir -p $(PATHO)

clean :
	$(CLEANUP) $(PATHO)
	printf "$(RED)Directory obj is  removed\n$(NC)"

fclean : clean
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(NAMEDB)
	printf "$(RED)$(NAME) deleted\n$(NC)"

re : fclean all

norme :
	norminette $(PATHI)
	norminette srcs/

.PHONY: all clean fclean debug
.SILENT:

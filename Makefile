NAME = 42sh
NAMEDB = 42sh_db

# Reset
NC=\033[0m

# Regular Colors
BLACK=\033[0;30m
RED=\033[0;31m
GREEN =\033[32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m

## LINE EDITION ##

LESRCS += cursor.c
LESRCS += history_utils.c
LESRCS += ft_prompt.c
LESRCS += history.c
LESRCS += print_cmd.c
LESRCS += keys_action.c
LESRCS += move_word.c
LESRCS += signals.c
LESRCS += term_init.c
LESRCS += utils.c
LESRCS += clipboard.c
LESRCS += cursor_position.c
LESRCS += input.c
LESRCS += arrow_keys.c
LESRCS += maj_arrow_keys.c
LESRCS += del_keys.c
LESRCS += other_keys.c
LESRCS += history_keys.c
LESRCS += hist_exp/hist_exp.c
LESRCS += hist_exp/formats.c
LESRCS += reverse_i_search/prompt.c
LESRCS += reverse_i_search/search.c

## LEXER ##

LEXSRCS += buffer.c
LEXSRCS += comment.c
LEXSRCS += control.c
LEXSRCS += digit.c
LEXSRCS += equ.c
LEXSRCS += exp.c
LEXSRCS += flag.c
LEXSRCS += free.c
LEXSRCS += heredoc.c
LEXSRCS += inhib.c
LEXSRCS += lexer.c
LEXSRCS += misc.c
LEXSRCS += newline.c
LEXSRCS += prompt.c
LEXSRCS += quote.c
LEXSRCS += redir.c
LEXSRCS += token.c
LEXSRCS += tools.c
LEXSRCS += type.c
LEXSRCS += word.c
LEXSRCS += state/comment.c
LEXSRCS += state/control.c
LEXSRCS += state/exp.c
LEXSRCS += state/flag.c
LEXSRCS += state/hdbody.c
LEXSRCS += state/init.c
LEXSRCS += state/ionumber.c
LEXSRCS += state/redir.c
LEXSRCS += state/start.c
LEXSRCS += state/word.c

## PARSER ##

PARSRCS += alias.c
PARSRCS += amp.c
PARSRCS += and_or.c
PARSRCS += assign.c
PARSRCS += cmd.c
PARSRCS += free.c
PARSRCS += init.c
PARSRCS += lst_to_tab.c
PARSRCS += misc.c
PARSRCS += newline.c
PARSRCS += parser.c
PARSRCS += redir.c
PARSRCS += tools.c
PARSRCS += word.c
PARSRCS += state/andif_pipe.c
PARSRCS += state/arg_assign.c
PARSRCS += state/assign.c
PARSRCS += state/cmd_args.c
PARSRCS += state/cmd_start.c
PARSRCS += state/delim.c
PARSRCS += state/error.c
PARSRCS += state/init.c
PARSRCS += state/io_number.c
PARSRCS += state/redir.c
PARSRCS += state/table_start.c

## ANALYZER ##

ANASRCS += args_tab/args_to_tab.c
ANASRCS += args_tab/make_args_tab.c
ANASRCS += jobs_str/core.c
ANASRCS += jobs_str/redir.c
ANASRCS += heredoc.c
ANASRCS += exp/exp.c
ANASRCS += exp/exp_errors.c
ANASRCS += exp/exp_getenv.c
ANASRCS += exp/exp_tools.c
ANASRCS += exp/parameter.c
ANASRCS += exp/param_recursive.c
ANASRCS += exp/param_resolve.c
ANASRCS += exp/param_substitution.c
ANASRCS += exp/tilde_exp.c
ANASRCS += exp/tilde_assign.c
ANASRCS += exp/word_parameter.c
ANASRCS += field_splitting.c
ANASRCS += quote_removal.c

## EVAL ##

EVALSRCS += launcher_job.c
EVALSRCS += launcher_process.c
EVALSRCS += process_assign.c
EVALSRCS += exec_type.c
EVALSRCS += cleaner.c
EVALSRCS += constructor.c
EVALSRCS += bridge_step.c
EVALSRCS += wait.c
EVALSRCS += redir.c
EVALSRCS += tools_var.c
EVALSRCS += tools_fd.c
EVALSRCS += tools_redir.c
EVALSRCS += tools_termios.c
EVALSRCS += tools_process.c
EVALSRCS += tools_signal.c
EVALSRCS += errors_handling.c
EVALSRCS += ft_lst.c
EVALSRCS += debug.c

## JOB CONTROL ##

JBSRCS += tools_job.c
JBSRCS += ft_lst.c
JBSRCS += routine_check_child.c
JBSRCS += job_id.c
JBSRCS += struct_job.c

## COMMON TOOLS  ##

TOOLSRCS += tools_path.c
TOOLSRCS += tools_var.c
TOOLSRCS += tools_sh.c
TOOLSRCS += path_errors.c
TOOLSRCS += setvar_add.c
TOOLSRCS += all_signal.c

## BUILTIN ##

BTSRCS += fc/fc.c
BTSRCS += fc/errors.c
BTSRCS += fc/history_file.c
BTSRCS += fc/arg_process.c
BTSRCS += fc/exec.c
BTSRCS += fc/option_l.c
BTSRCS += fc/option_e.c
BTSRCS += fc/option_s.c
BTSRCS += exit.c
BTSRCS += hash/hash.c
BTSRCS += hash/utils.c
BTSRCS += export.c
BTSRCS += set.c
BTSRCS += unset.c
BTSRCS += echo.c
BTSRCS += jobs/ft_jobs.c
BTSRCS += jobs/jobs_print.c
BTSRCS += cd/chdir_errors.c
BTSRCS += cd/ft_cd.c
BTSRCS += cd/ft_cd2.c
BTSRCS += cd/ft_cd_core.c
BTSRCS += cd/tools_cd.c
BTSRCS += type.c
BTSRCS += test/test.c
BTSRCS += test/op_init.c
BTSRCS += test/arg_check.c
BTSRCS += test/block_file.c
BTSRCS += test/char_file.c
BTSRCS += test/dir_file.c
BTSRCS += test/exec.c
BTSRCS += test/fifo.c
BTSRCS += test/file.c
BTSRCS += test/int_eq.c
BTSRCS += test/int_ge.c
BTSRCS += test/int_gt.c
BTSRCS += test/int_le.c
BTSRCS += test/int_lt.c
BTSRCS += test/int_neq.c
BTSRCS += test/read.c
BTSRCS += test/reg_file.c
BTSRCS += test/setgid.c
BTSRCS += test/setuid.c
BTSRCS += test/socket.c
BTSRCS += test/str_eq.c
BTSRCS += test/str_neq.c
BTSRCS += test/symlink.c
BTSRCS += test/write.c
BTSRCS += test/zero.c
BTSRCS += test/size.c
BTSRCS += fg.c
BTSRCS += bg.c
BTSRCS += alias/alias.c
BTSRCS += alias/print.c
BTSRCS += alias/tools.c
BTSRCS += alias/unalias.c

## INCLUDES ##

INCLUDES += analyzer.h
INCLUDES += exec.h
INCLUDES += debug.h
INCLUDES += job_control.h
INCLUDES += lexer.h
INCLUDES += line_edition.h
INCLUDES += parser.h
INCLUDES += sh.h
INCLUDES += struct.h
INCLUDES += var.h


## DEBUG ##

DBSRCS += lexer/lexer.c
DBSRCS += lexer/misc.c
DBSRCS += parser/parser.c
DBSRCS += parser/get.c
DBSRCS += parser/print_cmd.c
DBSRCS += analyzer.c

SRC += main.c
SRC += init_shell.c
SRC += init_cfg.c
SRC += destructor.c
SRC += exit_routine.c
SRC += launch_routine.c
SRC += map_builtin.c
SRC += $(addprefix line_edition/,$(LESRCS))
SRC += $(addprefix lexer/,$(LEXSRCS))
SRC += $(addprefix parser/,$(PARSRCS))
SRC += $(addprefix analyzer/,$(ANASRCS))
SRC += $(addprefix evaluator/,$(EVALSRCS))
SRC += $(addprefix job_control/,$(JBSRCS))
SRC += $(addprefix builtins/,$(BTSRCS))
SRC += $(addprefix tools/,$(TOOLSRCS))
SRC += $(addprefix debug/,$(DBSRCS))


OPATHS += $(OPATH)line_edition
OPATHS += $(OPATH)line_edition/hist_exp
OPATHS += $(OPATH)line_edition/reverse_i_search
OPATHS += $(OPATH)lexer
OPATHS += $(OPATH)lexer/state
OPATHS += $(OPATH)parser
OPATHS += $(OPATH)parser/state
OPATHS += $(OPATH)analyzer
OPATHS += $(OPATH)analyzer/jobs_str
OPATHS += $(OPATH)analyzer/args_tab
OPATHS += $(OPATH)analyzer/exp
OPATHS += $(OPATH)evaluator
OPATHS += $(OPATH)builtins
OPATHS += $(OPATH)builtins/cd
OPATHS += $(OPATH)builtins/fc
OPATHS += $(OPATH)builtins/test
OPATHS += $(OPATH)builtins/jobs
OPATHS += $(OPATH)builtins/hash
OPATHS += $(OPATH)builtins/alias
OPATHS += $(OPATH)debug
OPATHS += $(OPATH)debug/lexer
OPATHS += $(OPATH)debug/parser
OPATHS += $(OPATH)tools
OPATHS += $(OPATH)job_control

CC = clang
COMPILE = $(CC) -c
COMPILEDB = $(CC) -g3

MKDIR = mkdir -p
CLEANUP = rm -rf

DSYN = $(NAMEDB).dSYM

OPATH = objs/
SPATH = srcs/
IPATH = includes/
LPATH = libft/
LIPATH = libft/includes/
LIB = $(LPATH)libft.a
LIBDB = $(LPATH)libft_db.a

WFLAGS = -Wall -Werror -Wextra
IFLAGS = -I $(IPATH) -I $(LIPATH)
CFLAGS = $(WFLAGS) $(IFLAGS)
DBFLAGS = -fsanitize=address

OBJ = $(patsubst %.c, %.o, $(SRC))

SRCS = $(addprefix $(SPATH),$(SRC))

OBJS = $(addprefix $(OPATH),$(OBJ))

INCS = $(addprefix $(IPATH),$(INCLUDES))

all : $(NAME)

$(NAME) : $(LIB) $(OPATHS) $(OBJS) Makefile
	$(CC) -lncurses -o $@ $(OBJS) $<
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJS) : $(OPATH)%.o : $(SPATH)%.c $(INCS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(OPATHS) :
	$(MKDIR) $@

$(LIB) : FORCE
	$(MAKE) -C $(LPATH)

$(LIBDB) :
	$(MAKE) -C $(LPATH) debug

debug : $(LIBDB)
	$(COMPILEDB) $(DBFLAGS) -lncurses $(CFLAGS) -o $(NAMEDB) $(SRCS) $^
	printf "$(GREEN)$(NAMEDB) is ready.\n$(NC)"


clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OBJS)
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(DSYN)
	printf "$(RED)Directory $(NAME) is clean\n$(NC)"

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(NAMEDB)
	printf "$(RED)$(NAME) is delete\n$(NC)"

re : fclean all

norme:
	norminette $(SPATH)
	norminette $(IPATH)
	norminette $(LPATH)/$(SPATH)
	norminette $(LPATH)/$(IPATH)

FORCE:

.PHONY: all clean fclean norme re debug FORCE
.SILENT:

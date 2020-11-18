NAME = 42sh

FT_PRINTF_PATH = ft_printf/

LIBFT_PATH = libft/

FLAGS = -Wall -Werror -Wextra -g #add -g for visual debugger
INC = -I ./includes/ -I ./libft/includes

SRCS = src/main.c \
src/lexer/lexical_analysis.c \
src/lexer/get_token_info.c \
src/lexer/lexer_helper1.c \
src/lexer/lexer_helper2.c \
src/lexer/interpret.c \
src/lexer/jump_single_or_double_quote.c \
src/lexer/create_non_quoted_string.c \
src/lexer/check_syntax.c \
src/lexer/clear_token.c \
src/parser/syntax_analysis.c \
src/parser/AST/and_or.c \
src/parser/AST/ast_tool.c \
src/parser/AST/cmd_name.c \
src/parser/AST/cmd_suffix.c \
src/parser/AST/word.c \
src/parser/AST/command.c \
src/parser/AST/complete_command.c \
src/parser/AST/file_name.c \
src/parser/AST/io_files.c \
src/parser/AST/io_here.c \
src/parser/AST/io_file_branch.c \
src/parser/AST/io_redirect.c \
src/parser/AST/list.c \
src/parser/AST/pipe_sequence.c \
src/parser/AST/pipeline.c \
src/parser/AST/simple_command.c \
src/signal/sig_handler.c \
src/signal/eof_handler.c \
src/executor/executor.c \
src/executor/children.c \
src/executor/check_path.c \
src/executor/heredoc.c \
src/executor/execute_ast/execute_complete_command.c \
src/executor/execute_ast/execute_list.c \
src/executor/execute_ast/execute_and_or.c \
src/executor/execute_ast/execute_pipeline.c \
src/executor/execute_ast/execute_pipe_sequence.c \
src/executor/execute_ast/execute_command.c \
src/executor/execute_ast/execute_simple_command.c \
src/executor/execute_ast/execute_cmd_name.c \
src/executor/execute_ast/execute_cmd_suffix.c \
src/executor/execute_ast/execute_io_redirect.c \
src/executor/handle_redirect.c \
src/executor/redirects_great.c \
src/executor/redirects_less.c \
src/builtin/builtins.c \
src/builtin/ft_cd.c \
src/builtin/ft_cd_pathfinder.c \
src/builtin/access.c \
src/builtin/ft_setenv.c \
src/builtin/ft_unsetenv.c \
src/builtin/ft_type.c \
src/builtin/builtin_utils.c \
src/builtin/ft_jobs.c \
src/builtin/ft_fg.c \
src/builtin/ft_alias.c \
src/builtin/ft_unalias.c \
src/line_edition/add_key.c \
src/line_edition/clipping.c \
src/line_edition/ctrl_k.c \
src/line_edition/ctrl_l.c \
src/line_edition/ctrl_left_right.c \
src/line_edition/ctrl_up_down.c \
src/line_edition/ft_get_line.c \
src/line_edition/history.c \
src/line_edition/home_end_key.c \
src/line_edition/left_right_bs_key.c \
src/line_edition/term_attr.c \
src/line_edition/up_down_key.c \
src/line_edition/carriage_return.c \
src/line_edition/get_prompt.c \
src/utilities/tool_for_checking.c \
src/utilities/get_env.c \
src/utilities/ft_strndup.c \
src/utilities/ft_arraydel.c \
src/utilities/error.c \
src/utilities/ft_strjoin_and_free.c \
src/utilities/set_oldpwd.c \
src/utilities/increment_shell_level.c \
src/executor/print_binary_tree.c \
src/jobs/ft_tcgetsetpgrp.c \
src/jobs/job_utils.c \
src/jobs/foreground_and_background.c \
src/jobs/stopped_and_terminated_jobs.c \
src/jobs/continuing_stopped_jobs.c \
src/jobs/lauch_process.c \


OBJS_NAME = main.o \
lexical_analysis.o \
get_token_info.o \
lexer_helper1.o \
lexer_helper2.o \
syntax_analysis.o \
and_or.o \
ast_tool.o \
cmd_name.o \
cmd_suffix.o \
word.o \
command.o \
complete_command.o \
file_name.o \
io_file_branch.o \
io_files.o \
io_here.o \
io_redirect.o \
list.o \
pipe_sequence.o \
pipeline.o \
simple_command.o \
tool_for_checking.o \
get_env.o \
ft_strndup.o \
ft_arraydel.o \
error.o \
ft_strjoin_and_free.o \
sig_handler.o \
executor.o \
builtins.o \
execute_complete_command.o \
execute_list.o \
execute_and_or.o \
execute_pipeline.o \
execute_pipe_sequence.o \
execute_command.o \
execute_simple_command.o \
execute_cmd_name.o \
execute_cmd_suffix.o \
execute_io_redirect.o \
ft_cd.o \
ft_cd_pathfinder.o \
access.o \
ft_setenv.o \
ft_unsetenv.o \
ft_jobs.o \
ft_fg.o \
ft_alias.o \
ft_unalias.o \
children.o \
check_path.o \
heredoc.o \
add_key.o \
clipping.o \
ctrl_k.o \
ctrl_l.o \
ctrl_left_right.o \
ctrl_up_down.o \
history.o \
home_end_key.o \
left_right_bs_key.o \
term_attr.o \
up_down_key.o \
ft_get_line.o \
interpret.o \
eof_handler.o \
carriage_return.o \
set_oldpwd.o \
handle_redirect.o \
redirects_great.o \
redirects_less.o \
clear_token.o \
get_prompt.o \
increment_shell_level.o \
check_syntax.o \
jump_single_or_double_quote.o \
ft_type.o \
builtin_utils.o \
create_non_quoted_string.o \
print_binary_tree.o \
ft_tcgetsetpgrp.o \
job_utils.o \
foreground_and_background.o \
stopped_and_terminated_jobs.o \
continuing_stopped_jobs.o \
lauch_process.o

OBJS_PATH = obj/

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))


.PHONY: all, clean, fclean, re
all: $(NAME)

$(NAME):
	@make -s -C ./libft
	@make -s -C ./ft_printf
	@gcc -c $(FLAGS) $(INC) $(SRCS)
	@mkdir -p $(OBJS_PATH)
	@mv $(OBJS_NAME) $(OBJS_PATH)
	@gcc $(FLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -L$(FT_PRINTF_PATH) -lftprintf -ltermcap -o $(NAME)
#	 @gcc $(FLAGS) $(SRCS) libft/libft.a $(INC) -ltermcap #debug for ihwang

clean:
	@make -s -C ./libft clean
	@make -s -C ./ft_printf clean
	@/bin/rm -rf $(OBJS_NAME)
	@/bin/rm -rf $(OBJS_PATH)

fclean: clean
	@make -s -C ./libft fclean
	@make -s -C ./ft_printf fclean
	@/bin/rm -f $(NAME)

re: fclean all

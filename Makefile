# 42sh's file struture
# ______[includes] ------------> all header files go here
#  |____[src]
#     |___[cores]
#     |  |___[lexer]
#     |  |___[parser]
#     |  |___[executor]
#     |  |___[line_edition]
#     |___[features]
#     |  |___[buit-in] -------------> all built-in function go here
#     |  |___[job_control]
#     |  |___[history_management]
#     |  |___[alias]
#     |  |___[expansion]
#     |  |___[signal]
#     |___[utility] ---------> all general function go here ex.library for shell
#     |___main.c
#
# HOW TO ADD YOUR PROJECT INTO THIS MAKEFILE:
#	1. Decide your project where it should be in either "cores" or "features" directory 
#	2. Create your pattern like this
#		a, Declare directory of your project ex: ALIAS_DIR := $(FEATURES_DIR)/alias
# 		Since, alias feature should be put in "features" directory so I declare its directory
#		like the above example
#		b, Declare files in the feature, continue with the alias example
#		I declare a variable ALIAS_FILE which will contain all the files of the alias project
#		Ex: ALIAS_FILE += alias_substitution.c
#		Remember there must be a plus equal sign
#		c, Declare the feature and join its working directory with its files
#		Ex: ALIAS := $(addprefix $(ALIAS_DIR)/,$(ALIAS_FILE))
#		What i do here is I declare the ALIAS variable which will contain all the string
#		from alias files and before that, I added ALIAS_DIR in front of every ALIAS files
#		d, Coming back to the first process, since you have decided where your project belonged
#		, put it into its own part
#		Ex: Since I have decide Alias project go to feature directory, I added:
#		FEATURES += $(ALIAS)
#
# WARNING: If you think your function which you will use several time after to the other
#		project, I recommend you to put its file into the UTILITY.
#		Ex: functions which in the man page
CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror -g # g flag for debugger
PROGRAM			:= 42sh
# library dir
LIBFT_DIR		:= ./libft
FT_RPINTF_DIR	:= ./ft_printf
# path
CORE_DIR		:= src/cores
FEATURES_DIR	:= src/features
# header
INCLUDE			:= -Iincludes/ -Ilibft/includes/ -Ift_printf/includes/
# library
LIB				:= -L$(LIBFT_DIR)/ -lft -L$(FT_RPINTF_DIR)/ -lftprintf -ltermcap
############################ Create core files ################################
#Init
INIT_DIR := $(CORE_DIR)/init
INIT_FILE += init_terminal_stuff.c
INIT := $(addprefix $(INIT_DIR)/,$(INIT_FILE))
#Lexer & Parser
LEXER_PARSER_DIR := $(CORE_DIR)/lexer_parser
LEXER_PARSER_FILE += tokenizing_service.c
LEXER_PARSER_FILE += lexical_analysis.c
LEXER_PARSER_FILE += syntax_analysis.c
LEXER_PARSER_FILE += syntax_errors.c
LEXER_PARSER_FILE += lexer_helper1.c
LEXER_PARSER_FILE += lexer_helper2.c
LEXER_PARSER_FILE += lexer_helper3.c
LEXER_PARSER_FILE += non_operator_token.c
LEXER_PARSER_FILE += operator_token.c
LEXER_PARSER_FILE += token_creator.c
LEXER_PARSER_FILE += getting_user_input.c
LEXER_PARSER_FILE += analyzing_phase.c
LEXER_PARSER_FILE += analyzing_phase_helper.c
LEXER_PARSER_FILE += token_tools.c
LEXER_PARSER := $(addprefix $(LEXER_PARSER_DIR)/,$(LEXER_PARSER_FILE))
#Parser
SEMANTIC_DIR := $(CORE_DIR)/semantic
SEMANTIC_FILE += semantic_analysis.c
SEMANTIC_FILE += AST/complete_command.c
SEMANTIC_FILE += AST/list.c
SEMANTIC_FILE += AST/and_or.c
SEMANTIC_FILE += AST/pipeline.c
SEMANTIC_FILE += AST/pipe_sequence.c
SEMANTIC_FILE += AST/command.c
SEMANTIC_FILE += AST/simple_command.c
SEMANTIC_FILE += AST/simple_command2.c
SEMANTIC_FILE += AST/cmd_name.c
SEMANTIC_FILE += AST/cmd_suffix.c
SEMANTIC_FILE += AST/io_redirect.c
SEMANTIC_FILE += AST/io_files.c
SEMANTIC_FILE += AST/io_file_branch.c
SEMANTIC_FILE += AST/file_name.c
SEMANTIC_FILE += AST/io_here.c
SEMANTIC_FILE += AST/here_end.c
SEMANTIC_FILE += AST/word.c
SEMANTIC_FILE += AST/assignment_word.c
SEMANTIC_FILE += AST/cmd_prefix.c
SEMANTIC_FILE += AST/ast_tool.c
SEMANTIC_FILE += AST/linebreak.c
SEMANTIC := $(addprefix $(SEMANTIC_DIR)/,$(SEMANTIC_FILE))
#Executor
EXECUTOR_DIR := $(CORE_DIR)/executor
# EXECUTOR_FILE += print_binary_tree.c
EXECUTOR_FILE += executor.c
EXECUTOR_FILE += heredoc/heredoc.c
EXECUTOR_FILE += heredoc/heredoc_tool.c
EXECUTOR_FILE += execute_ast/execute_complete_command.c
EXECUTOR_FILE += execute_ast/execute_list.c
EXECUTOR_FILE += execute_ast/execute_and_or.c
EXECUTOR_FILE += execute_ast/execute_and_or_bg.c
EXECUTOR_FILE += execute_ast/execute_and_or_bg/build_cm_string.c
EXECUTOR_FILE += execute_ast/execute_and_or_bg/build_cm_string2.c
EXECUTOR_FILE += execute_ast/execute_pipeline.c
EXECUTOR_FILE += execute_ast/execute_pipe_sequence.c
EXECUTOR_FILE += execute_ast/execute_pipe_sequence_helper.c
EXECUTOR_FILE += execute_ast/execute_command.c
EXECUTOR_FILE += execute_ast/execute_simple_command.c
EXECUTOR_FILE += execute_ast/execute_cmd_name.c
EXECUTOR_FILE += execute_ast/execute_cmd_suffix.c
EXECUTOR_FILE += execute_ast/execute_io_redirect.c
EXECUTOR_FILE += execute_ast/execute_cmd_prefix.c
EXECUTOR_FILE += execute_ast/execute_assignment_word.c
EXECUTOR_FILE += redirection/handle_redirect.c
EXECUTOR_FILE += redirection/redirects_great.c
EXECUTOR_FILE += redirection/redirects_less.c
EXECUTOR_FILE += redirection/redirection_tools.c
EXECUTOR_FILE += lauch_process/lauch_process.c
EXECUTOR_FILE += lauch_process/lauch_process_child_shell.c
EXECUTOR_FILE += lauch_process/execute_in_child_process.c
EXECUTOR_FILE += lauch_process/children.c
EXECUTOR_FILE += lauch_process/lauch_process_parent_shell.c
EXECUTOR := $(addprefix $(EXECUTOR_DIR)/,$(EXECUTOR_FILE))
#Line Edition
LINE_EDITION_DIR := $(CORE_DIR)/line_edition
LINE_EDITION_FILE += add_key.c
LINE_EDITION_FILE += clipping.c
LINE_EDITION_FILE += ctrl_k_cut.c
LINE_EDITION_FILE += ctrl_l_paste.c
LINE_EDITION_FILE += ctrl_left_right.c
LINE_EDITION_FILE += ctrl_up_down.c
LINE_EDITION_FILE += cursor_index_pos.c
LINE_EDITION_FILE += ft_get_line.c
LINE_EDITION_FILE += parse_key.c
LINE_EDITION_FILE += home_end_key.c
LINE_EDITION_FILE += left_right_bs_key.c
LINE_EDITION_FILE += read_user_input.c
LINE_EDITION_FILE += reverse_search.c
LINE_EDITION_FILE += reverse_search_utils.c
LINE_EDITION_FILE += row_count.c
LINE_EDITION_FILE += term_attr.c
LINE_EDITION_FILE += up_down_key.c
# LINE_EDITION_FILE += carriage_return.c
LINE_EDITION_FILE += get_prompt.c
LINE_EDITION_FILE += get_prompt_print.c
LINE_EDITION_FILE += line_edition_utilities.c
LINE_EDITION_FILE += paste_background.c
LINE_EDITION := $(addprefix $(LINE_EDITION_DIR)/,$(LINE_EDITION_FILE))
# SUM-UP Core
CORE += $(INIT)
CORE += $(LEXER_PARSER)
CORE += $(SEMANTIC)
CORE += $(EXECUTOR)
CORE += $(LINE_EDITION)
############################# Create feature files ############################
#Built-in
BUILT_IN_DIR := $(FEATURES_DIR)/builtin
BUILT_IN_FILE += ft_exit.c
BUILT_IN_FILE += ft_echo.c
BUILT_IN_FILE += ft_env.c
BUILT_IN_FILE += ft_cd.c
BUILT_IN_FILE += ft_cd_utilities/ft_cd_pwd_handle_builtin_opts.c
BUILT_IN_FILE += ft_cd_utilities/ft_cd_append_slash_to_curpath.c
BUILT_IN_FILE += ft_cd_utilities/ft_cd_change_dir.c
BUILT_IN_FILE += ft_cd_utilities/ft_cd_compress_curpath.c
BUILT_IN_FILE += ft_cd_utilities/ft_cd_get_curpath_from_dir.c
BUILT_IN_FILE += ft_cd_utilities/ft_cd_is_root_dir.c
BUILT_IN_FILE += ft_cd_utilities/ft_cd_prune_dotdot_dot_slash.c
BUILT_IN_FILE += ft_cd_utilities/ft_cd_search_cdpath.c
BUILT_IN_FILE += ft_jobs.c
BUILT_IN_FILE += ft_fg.c
BUILT_IN_FILE += ft_fc.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_exec_e.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_exec_s.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_execute.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_utilities.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_utilities2.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_list.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_struct_tools.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_parse_input.c
BUILT_IN_FILE += ft_fc_utilities/ft_fc_errors.c
BUILT_IN_FILE += ft_bg.c
BUILT_IN_FILE += ft_alias.c
BUILT_IN_FILE += ft_unalias.c
BUILT_IN_FILE += ft_alias_utilities/ft_alias_utils.c
BUILT_IN_FILE += ft_alias_utilities/ft_alias_utils2.c
BUILT_IN_FILE += ft_set.c
BUILT_IN_FILE += ft_unset.c
BUILT_IN_FILE += ft_export.c
BUILT_IN_FILE += ft_export_utilities/ft_export_parse.c
BUILT_IN_FILE += ft_hash.c
BUILT_IN_FILE += ft_hash_utilities/ft_hash_utils.c
BUILT_IN_FILE += ft_hash_utilities/ft_hash_utils2.c
BUILT_IN_FILE += ft_type.c
BUILT_IN_FILE += ft_type_utilities/ft_init_builtin_commands.c
BUILT_IN := $(addprefix $(BUILT_IN_DIR)/,$(BUILT_IN_FILE))
# Job control
JOB_CONTROL_DIR := $(FEATURES_DIR)/job_control
JOB_CONTROL_FILE += job_utils.c
JOB_CONTROL_FILE += job_utils2.c
JOB_CONTROL_FILE += create_delete_job_tools.c
JOB_CONTROL_FILE += process_utils.c
JOB_CONTROL_FILE += delete_process_tools.c
JOB_CONTROL_FILE += foreground_and_background.c
JOB_CONTROL_FILE += stopped_and_terminated_jobs.c
JOB_CONTROL_FILE += continuing_stopped_jobs.c
JOB_CONTROL_FILE += find_job.c
JOB_CONTROL_FILE += print_job.c
JOB_CONTROL := $(addprefix $(JOB_CONTROL_DIR)/,$(JOB_CONTROL_FILE))
# History Management
HISTORY_MANAGEMENT_DIR := $(FEATURES_DIR)/history_management
HISTORY_MANAGEMENT_FILE += history.c
HISTORY_MANAGEMENT_FILE += read_history_file.c
HISTORY_MANAGEMENT_FILE += read_history_file_utils.c
HISTORY_MANAGEMENT_FILE += history_exp.c
HISTORY_MANAGEMENT_FILE += history_exp_utils.c
HISTORY_MANAGEMENT_FILE += history_input_check.c
HISTORY_MANAGEMENT := $(addprefix $(HISTORY_MANAGEMENT_DIR)/,$(HISTORY_MANAGEMENT_FILE))
# Arithmetic Expansion
ARITHMETIC_EXPANSION_DIR := $(FEATURES_DIR)/arithmetic_expansion
ARITHMETIC_EXPANSION_FILE += arx.c
ARITHMETIC_EXPANSION_FILE += arx_exp.c
ARITHMETIC_EXPANSION_FILE += arx_lexer.c
ARITHMETIC_EXPANSION_FILE += atoi_base.c
ARITHMETIC_EXPANSION_FILE += base.c
ARITHMETIC_EXPANSION_FILE += calc.c
ARITHMETIC_EXPANSION_FILE += checker.c
ARITHMETIC_EXPANSION_FILE += error.c
ARITHMETIC_EXPANSION_FILE += extolst.c
ARITHMETIC_EXPANSION_FILE += infix_format.c
ARITHMETIC_EXPANSION_FILE += intvar.c
ARITHMETIC_EXPANSION_FILE += operand.c
ARITHMETIC_EXPANSION_FILE += plusminus.c
ARITHMETIC_EXPANSION_FILE += postfix.c
ARITHMETIC_EXPANSION_FILE += utils.c
ARITHMETIC_EXPANSION_FILE += utils_exp.c
ARITHMETIC_EXPANSION_FILE += utils_exp2.c
ARITHMETIC_EXPANSION_FILE += utils_format.c
ARITHMETIC_EXPANSION_FILE += utils_pm.c
ARITHMETIC_EXPANSION := $(addprefix $(ARITHMETIC_EXPANSION_DIR)/,$(ARITHMETIC_EXPANSION_FILE))
# Alias
ALIAS_DIR := $(FEATURES_DIR)/alias
ALIAS_FILE += alias_substitution.c
ALIAS := $(addprefix $(ALIAS_DIR)/,$(ALIAS_FILE))
# Signal
SIGNAL_DIR := $(FEATURES_DIR)/signal
SIGNAL_FILE += sig_handler.c
SIGNAL_FILE += signal_messages.c
SIGNAL_FILE += handle_sigwinch.c
SIGNAL := $(addprefix $(SIGNAL_DIR)/,$(SIGNAL_FILE))
# Expansion
EXPANSION_DIR := $(FEATURES_DIR)/expansion
EXPANSION_FILE += handle_expansion.c
PARAMETER_EXPANSION_DIR := $(EXPANSION_DIR)/parameter_expansion
PARAMETER_EXPANSION_FILE += parameter_expansion.c
PARAMETER_EXPANSION_FILE += parameter_expansion_struct.c
PARAMETER_EXPANSION_FILE += parameter_expansion_struct_syntax_analysis.c
PARAMETER_EXPANSION_FILE += parameter_expansion_struct_replacement.c
PARAMETER_EXPANSION_FILE += split_parameter_delimeter_word.c
PARAMETER_EXPANSION_FILE += parameter_expansion_tool1.c
PARAMETER_EXPANSION_FILE += parameter_expansion_tool2.c
PARAMETER_EXPANSION_FILE += complex_parameter_expansion.c
PARAMETER_EXPANSION_FILE += complex_parameter_expansion2.c
PARAMETER_EXPANSION_FILE += complex_parameter_expansion3.c
PARAMETER_EXPANSION_FILE += complex_parameter_expansion4.c
PARAMETER_EXPANSION_FILE += parameter_expansion_for_word.c
PARAMETER_EXPANSION := $(addprefix $(PARAMETER_EXPANSION_DIR)/,$(PARAMETER_EXPANSION_FILE))
TILDE_EXPANSION_DIR := $(EXPANSION_DIR)/tilde_expansion
TILDE_EXPANSION_FILE += tilde_expansion.c
TILDE_EXPANSION_FILE += tilde_expansion_utils.c
TILDE_EXPANSION := $(addprefix $(TILDE_EXPANSION_DIR)/,$(TILDE_EXPANSION_FILE))
EXPANSION := $(addprefix $(EXPANSION_DIR)/,$(EXPANSION_FILE))
EXPANSION += $(TILDE_EXPANSION) $(PARAMETER_EXPANSION)
# Inhibitor
INHIBITOR_DIR := $(FEATURES_DIR)/inhibitor
INHIBITOR_FILE += tool_for_checking.c
INHIBITOR_FILE += inhibitor_utility.c
INHIBITOR_FILE += quote_removal.c
INHIBITOR_FILE += remove_quoting_tools.c
INHIBITOR := $(addprefix $(INHIBITOR_DIR)/,$(INHIBITOR_FILE))
# Auto-complition
AUTO_COMPLETION_DIR := $(FEATURES_DIR)/auto_completion
AUTO_COMPLETION_FILE += auto_set_status.c
AUTO_COMPLETION_FILE += auto_delete_status.c
AUTO_COMPLETION_FILE += auto_completion.c
AUTO_COMPLETION_FILE += auto_file.c
AUTO_COMPLETION_FILE += auto_is_dir.c
AUTO_COMPLETION_FILE += auto_file_one_case.c
AUTO_COMPLETION_FILE += auto_file_multiple_cases.c
AUTO_COMPLETION_FILE += auto_make_list.c
AUTO_COMPLETION_FILE += auto_print_list.c
AUTO_COMPLETION_FILE += auto_open_path.c
AUTO_COMPLETION_FILE += auto_get_list.c
AUTO_COMPLETION_FILE += auto_command.c
AUTO_COMPLETION_FILE += auto_add_one_extra_char.c
AUTO_COMPLETION_FILE += auto_add_list_on_spot.c
AUTO_COMPLETION_FILE += auto_print_in_term_size.c
AUTO_COMPLETION_FILE += auto_print_over_term_size.c
AUTO_COMPLETION_FILE += auto_print_in_one_column.c
AUTO_COMPLETION_FILE += auto_print_in_two_columns.c
AUTO_COMPLETION_FILE += auto_read_input.c
AUTO_COMPLETION_FILE += auto_util/restore_line_edition.c
AUTO_COMPLETION_FILE += auto_util/wait_for_space_or_carrage_return.c
AUTO_COMPLETION_FILE += auto_util/get_grid_vars.c
AUTO_COMPLETION := $(addprefix $(AUTO_COMPLETION_DIR)/,$(AUTO_COMPLETION_FILE))
# Intern var and environment var
INTERN_ENVIRONMENT_VAR_DIR := $(FEATURES_DIR)/intern_and_environment_var
INTERN_ENVIRONMENT_VAR_FILE += environment_var.c
INTERN_ENVIRONMENT_VAR_FILE += environment_var_export.c
INTERN_ENVIRONMENT_VAR_FILE += internal_var.c
INTERN_ENVIRONMENT_VAR_FILE += internal_var2.c
INTERN_ENVIRONMENT_VAR = $(addprefix $(INTERN_ENVIRONMENT_VAR_DIR)/,$(INTERN_ENVIRONMENT_VAR_FILE))
# Hash table
HASH_TABLE_DIR := $(FEATURES_DIR)/hash_table
HASH_TABLE_FILE += hash_table_tools.c
HASH_TABLE = $(addprefix $(HASH_TABLE_DIR)/,$(HASH_TABLE_FILE))
# SUM-UP FEATUREs
FEATURES += $(BUILT_IN)
FEATURES += $(HISTORY_MANAGEMENT)
FEATURES += $(ARITHMETIC_EXPANSION)
FEATURES += $(JOB_CONTROL)
FEATURES += $(ALIAS)
FEATURES += $(SIGNAL)
FEATURES += $(EXPANSION)
FEATURES += $(AUTO_COMPLETION)
FEATURES += $(INHIBITOR)
FEATURES += $(INTERN_ENVIRONMENT_VAR)
FEATURES += $(HASH_TABLE)
########################### Create utility_FILE files ##############################
UTILITY_DIR := src/utility
UTILITY_FILE += get_var.c
UTILITY_FILE += ft_getcwd_logical.c
UTILITY_FILE += ft_strndup.c
UTILITY_FILE += ft_arraydel.c
UTILITY_FILE += ft_strjoin_and_free.c
UTILITY_FILE += increment_shell_level.c
UTILITY_FILE += ft_strchr_int.c
UTILITY_FILE += ft_swap.c
UTILITY_FILE += ft_strstr_int.c
UTILITY_FILE += ft_lstlen.c
UTILITY_FILE += ft_strncpm.c
UTILITY_FILE += ft_strnequ.c
UTILITY_FILE += ft_getenv.c
UTILITY_FILE += ft_swap_int.c
UTILITY_FILE += ft_strbuilder.c
UTILITY_FILE += ft_strbuilder_char.c
UTILITY_FILE += ft_tcsetpgrp.c
UTILITY_FILE += ft_tcgetpgrp.c
UTILITY_FILE += ft_lstdel_strdel.c
UTILITY_FILE += ft_arraylen.c
UTILITY_FILE += ft_atolli.c
UTILITY_FILE += ft_atolli_check.c
UTILITY_FILE += ft_llitoa.c
UTILITY_FILE += is_number_str.c
UTILITY_FILE += ft_strrev.c
UTILITY := $(addprefix $(UTILITY_DIR)/,$(UTILITY_FILE))

############################ SUM-UP SOURCE FILES ##############################
SRC := src/main.c
SRC += $(UTILITY)
SRC += $(CORE)
SRC += $(FEATURES)
# Create object files from src file
OBJ_DIR			:= objects
SRC_DIR			:= src
OBJECTS			:= $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

all: lft lftprintf mkdirs $(PROGRAM)
	@echo "\033[92m42sh Created\033[0m"

mkdirs:
	@mkdir -p $(OBJ_DIR)

lft:
	@cd $(LIBFT_DIR) && $(MAKE) -s

lftprintf:
	@cd $(FT_RPINTF_DIR) && $(MAKE) -s

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(OBJ_DIR)/$(notdir $@)

$(PROGRAM): $(OBJECTS)
	@$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(notdir $(OBJECTS))) $(LIB) -o $@

clean:
	@cd $(LIBFT_DIR) && $(MAKE) -s clean
	@cd $(FT_RPINTF_DIR) && $(MAKE) -s clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) -s fclean
	@cd $(FT_RPINTF_DIR) && $(MAKE) -s fclean
	@rm -rf $(PROGRAM)

re: fclean all

.PHONY: all mkdirs lft lftprintf clean fclean re

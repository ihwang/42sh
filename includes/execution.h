/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:34:20 by marvin            #+#    #+#             */
/*   Updated: 2021/03/30 18:41:30 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "struct.h"

# define NOT_COMPLETED 0
# define COMPLETED 1
# define NOT_STOPPED 0
# define STOPPED 1
# define UNAVAILABLE_STATUS 0
# define COMPLETED_JOB 1
# define SUSPENDED_JOB 2

/*
** ========================== EXECUTION FUNCTIONS =============================
*/

void		ft_execute(char *input);
void		execute_complete_command(t_astnode *ast);
void		execute_list(t_astnode *ast, int foreground);
void		execute_and_or(t_astnode *ast, int foreground,
			int forked, int noticed);
void		execute_and_or_bg(t_astnode *ast);
int			execute_pipeline(t_astnode *ast, t_job *job);
void		execute_pipe_sequence_helper(
	int pipefd[2], int saved[2], t_astnode *ast, t_job *j);
void		execute_pipe_sequence(t_astnode *ast, t_job *job);
void		execute_command(t_astnode *ast, t_job *job);
void		execute_simple_command(t_astnode *ast, t_job *job);
t_astnode	*simple_command5(t_token **token);
void		execute_cmd_name(t_astnode *ast, t_job *j, t_process *p);
void		execute_cmd_suffix(t_astnode *ast, t_job *j, t_process *p);
void		execute_io_redirect(t_astnode *ast, t_job *j, t_process *p);
void		execute_cmd_prefix(t_astnode *ast, t_job *j, t_process *p);
void		execute_assignment_word(t_astnode *ast, t_process *p);

/*
** Heredoc
*/

int			find_heredoc(t_astnode *ast);
void		clear_heredoc(t_heredoc *heredoc);

/*
** build command for and or background process
*/

void		build_and_or_command(t_astnode *ast, t_job *j);
void		build_pipe_sequence_command(t_astnode *ast, t_job *j);
void		build_simple_command_command(t_astnode *ast, t_job *j);
void		build_command_prefix_command(t_astnode *ast, t_job *j);
void		build_command_name_command(t_astnode *ast, t_job *j);
void		build_command_suffix_command(t_astnode *ast, t_job *j);
void		build_command_io_redirect_command(t_astnode *ast, t_job *j);
void		build_command_io_here_file_command(t_astnode *ast, t_job *j);

/*
** ========================== REDIRECTION FUNCTIONS ===========================
*/

int			handle_redirection(t_process *p);
int			redirect_great(t_redi *redi);
int			redirect_dgreat(t_redi *redi);
int			redirect_greatand(t_redi *redi);
int			redirect_lessand(t_redi *redi);
int			redirect_less(t_redi *redi);
int			redirect_dless(t_redi *redi);

/*
** Redirection tools
*/

void		set_stdin_stdout_stderr_channels(int old[3]);
void		reset_stdin_stdout_stderr_channels(int saved[3]);
int			close_file_descriptor(t_redi *redi, int old_fd);
int			duplicating_file_descriptor(t_redi *redi, int old_fd);

/*
** =========================== LAUCHING PROCESS ===============================
*/

int			lauch_simple_command(t_job *j, t_process *p);
int			lauch_in_parent_process(t_process *p);
void		fork_and_launch_in_child_process(t_job *j, t_process *p);
int			execute_in_child_process(t_job *j, t_process *p, char *path);

/*
** ========================== JOB CONTROL FUNCTIONS ===========================
*/

void		put_job_in_foreground(t_job *job, int cont);
void		put_job_in_background(t_job *job, int cont);
int			mark_process_status(t_job *j, pid_t pid, int status);
void		update_status(void);
void		wait_for_job(t_job *j, int opt);
void		format_job_info(t_job *j, const char *status, int opt);
void		do_job_notification(void);
void		change_running_state(t_job *j);
int			continue_the_suspended_job(t_job *j);
int			ft_tcsetpgrp(int fd, pid_t pgrp_id);
pid_t		ft_tcgetpgrp(int fd);
void		print_job_background(t_job *job_node);

/*
** Job tools
*/

t_job		*create_job(int foreground, int forked);
void		delete_job(t_job *j, char option);
void		put_to_list_job(t_job *newjob);
int			job_is_stopped(t_job *j);
int			job_is_completed(t_job *j);
int			is_the_last_job(t_job *j);
int			is_the_current_job(t_job *j);
t_job		*is_valid_job_id(char *str);
t_job		*find_the_last_job(void);
t_job		*find_the_current_job(void);
t_job		*find_job(pid_t pgid);
void		job_command_builder(int argc, t_job *j, ...);
void		delete_all_jobs_before_exit(t_job *first_job);

/*
** Process tools
*/

t_process	*create_process(t_job *j);
void		delete_process(t_job *j);
int			last_process_status(t_job *job);

#endif

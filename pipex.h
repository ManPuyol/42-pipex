/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:32:18 by manorteg          #+#    #+#             */
/*   Updated: 2024/12/07 20:09:24 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct s_pipex
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		status;
}	t_pipex;

void	handle_child_one(int *pipe_fd, int infile, int outfile, char **argv);
void	handle_child_two(int *pipe_fd, int infile, int outfile, char **argv);
void	close_all_fds(int *pipe_fd, int infile, int outfile);
int		error_exit(char *msg, t_pipex *px);

char	*find_path_env(char *envp[]);
void	free_paths(char **paths);
char	*check_command_in_paths(char *cmd, char **paths);
char	*get_command_path(char *cmd, char *envp[]);
void	execute_command(char *cmd, char *envp[]);

void	init_files(t_pipex *px, char **argv);
int		handle_processes(t_pipex *px, char **argv, char **envp);
int		error_exit(char *msg, t_pipex *px);

#endif
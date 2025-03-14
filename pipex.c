/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:22:22 by manorteg          #+#    #+#             */
/*   Updated: 2025/03/14 16:54:39 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_child_one(t_pipex *px, char **argv)
{
	if (px->infile >= 0)
	{
		dup2(px->infile, STDIN_FILENO);
		dup2(px->pipe_fd[1], STDOUT_FILENO);
		close(px->pipe_fd[0]);
		close(px->infile);
		close(px->outfile);
		execute_command(argv[2], px->envp);
	}
}

void	handle_child_two(t_pipex *px, char **argv)
{
	if (px->outfile >= 0)
	{
		dup2(px->pipe_fd[0], STDIN_FILENO);
		dup2(px->outfile, STDOUT_FILENO);
		close(px->pipe_fd[1]);
		close(px->infile);
		close(px->outfile);
		execute_command(argv[3], px->envp);
	}
}

int	handle_processes(t_pipex *px, char **argv)
{
	if (pipe(px->pipe_fd) == -1)
		return (error_exit("pipe", px));
	px->pid1 = fork();
	if (px->pid1 == -1)
		return (error_exit("fork", px));
	if (px->pid1 == 0 && px->infile >= 0)
		handle_child_one(px, argv);
	px->pid2 = fork();
	if (px->pid2 == -1)
		return (error_exit("fork", px));
	if (px->pid2 == 0 && px->outfile >= 0 && px->pid1 != 0)
		handle_child_two(px, argv);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	px.envp = envp;
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (EXIT_FAILURE);
	}
	init_files(&px, argv);
	if (handle_processes(&px, argv) != 0)
		return (EXIT_FAILURE);
	close_all_fds(&px);
	waitpid(px.pid1, NULL, 0);
	waitpid(px.pid2, &px.status, 0);
	exit (WEXITSTATUS(px.status));
}

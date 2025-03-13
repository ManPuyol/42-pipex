/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:22:22 by manorteg          #+#    #+#             */
/*   Updated: 2025/03/13 22:49:55 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_child_one(int *pipe_fd, int infile, int outfile, char **argv)
{
	if (infile >= 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(infile);
		close(outfile);
		execute_command(argv[2], envp);
	}
}

void	handle_child_two(int *pipe_fd, int infile, int outfile, char **argv)
{
	if (outfile >= 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(pipe_fd[1]);
		close(infile);
		close(outfile);
		execute_command(argv[3], envp);
	}
}

int	handle_processes(t_pipex *px, char **argv, char **envp)
{
	if (pipe(px->pipe_fd) == -1)
		return (error_exit("pipe", px));
	px->pid1 = fork();
	if (px->pid1 == -1)
		return (error_exit("fork", px));
	if (px->pid1 == 0 && px->infile >= 0)
		handle_child_one(px->pipe_fd, px->infile, px->outfile, argv);
	px->pid2 = fork();
	if (px->pid2 == -1)
		return (error_exit("fork", px));
	if (px->pid2 == 0 && px->outfile >= 0 && px->pid1 != 0)
		handle_child_two(px->pipe_fd, px->infile, px->outfile, argv);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (EXIT_FAILURE);
	}
	init_files(&px, argv);
	if (handle_processes(&px, argv, envp) != 0)
		return (EXIT_FAILURE);
	close_all_fds(px.pipe_fd, px.infile, px.outfile);
	waitpid(px.pid2, &px.status, 0);
	return (px.status);
}

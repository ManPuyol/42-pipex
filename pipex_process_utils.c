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

int	error_exit(char *msg, t_pipex *px)
{
	perror(msg);
	close_all_fds(px->pipe_fd, px->infile, px->outfile);
	return (EXIT_FAILURE);
}

void	init_files(t_pipex *px, char **argv)
{
	px->infile = open(argv[1], O_RDONLY);
	if (px->infile < 0)
		perror(argv[1]);
	px->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfile < 0)
		perror(argv[4]);
}

void	close_all_fds(int *pipe_fd, int infile, int outfile)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	close(outfile);
}
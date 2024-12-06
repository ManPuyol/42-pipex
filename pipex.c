/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:22:22 by manorteg          #+#    #+#             */
/*   Updated: 2024/11/24 15:22:22 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_command(char *cmd, char *envp[])
{
    char **args = ft_split(cmd, ' ');
    if (execve(args[0], args, envp) == -1)
    {
        fprintf(stderr, "pipex: %s: %s\n", args[0], strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[], char *envp[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    int pipe_fd[2];
    pid_t pid1, pid2;
    int infile, outfile;

    // Open files
    infile = open(argv[1], O_RDONLY);
    if (infile < 0)
    {
        fprintf(stderr, "pipex: %s: %s\n", argv[1], strerror(errno));
        return EXIT_FAILURE;
    }
    printf("infile: %d\n", infile);

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile < 0)
    {
        fprintf(stderr, "pipex: %s: %s\n", argv[4], strerror(errno));
        close(infile);
        return EXIT_FAILURE;
    }
    printf("outfile: %d\n", outfile);
    
    // Create pipe
    if (pipe(pipe_fd) == -1)
    {
        fprintf(stderr, "pipex: pipe: %s\n", strerror(errno));
        close(infile);
        close(outfile);
        return EXIT_FAILURE;
    }
    printf("pipe_fd[0]: %d\n", pipe_fd[0]);

    // First child process
    pid1 = fork();
    if (pid1 == -1)
    {
        fprintf(stderr, "pipex: fork: %s\n", strerror(errno));
        close(infile);
        close(outfile);
        return EXIT_FAILURE;
    }
    if (pid1 == 0)
    {
        // Child 1 process (cmd1)
        printf("Child 1 process\n");
        dup2(infile, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(infile);
        close(outfile);
        execute_command(argv[2], envp);
    }

    // Second child process
    pid2 = fork();
    if (pid2 == -1)
    {
        fprintf(stderr, "pipex: fork: %s\n", strerror(errno));
        close(infile);
        close(outfile);
        return EXIT_FAILURE;
    }
    if (pid2 == 0)
    {
        // Child 2 process (cmd2)
        printf("Child 2 process\n");
        dup2(pipe_fd[0], STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        close(pipe_fd[1]);
        close(infile);
        close(outfile);
        execute_command(argv[3], envp);
    }

    // Parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(infile);
    close(outfile);

    int status;
    waitpid(pid1, &status, 0);
    if (WIFEXITED(status))
    {
        printf("Child 1 exited with status %d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        printf("Child 1 killed by signal %d\n", WTERMSIG(status));
    }

    waitpid(pid2, &status, 0);
    if (WIFEXITED(status))
    {
        printf("Child 2 exited with status %d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        printf("Child 2 killed by signal %d\n", WTERMSIG(status));
    }

    return EXIT_SUCCESS;
}
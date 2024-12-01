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
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

// Example implementation structure
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
        perror("open infile");
        return EXIT_FAILURE;
    }
    printf("infile: %d\n", infile);

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile < 0)
    {
        perror("open outfile");
        close(infile);
        return EXIT_FAILURE;
    }

    printf("outfile: %d\n", outfile);
    
    
    // Create pipe
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        close(infile);
        close(outfile);
        return EXIT_FAILURE;
    }

    printf("pipe_fd[0]: %d\n", pipe_fd[0]);

    // First child process
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
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
        dup2(STDERR_FILENO, 2);
        close(pipe_fd[0]);
        close(infile);
        close(outfile);
        execute_command(argv[2], envp);
    }

    // Second child process
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        close(infile);
        close(outfile);
        return EXIT_FAILURE;
    }
    if (pid2 == 0)
    {
        // Child 2 process (cmd2)
        //wait for the first child to finish
        waitpid(pid1, NULL, 0);
        printf("Child 2 process\n");
        dup2(pipe_fd[0], STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        dup2(STDERR_FILENO, 2);
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
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return EXIT_SUCCESS;
}
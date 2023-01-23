#include "minishell.h"

t_program shellprogram;

void reset () {
  printf("\033[0m");
}

void    shell_export(t_shell *shell)
{
    update_env(shell->parsed[1], 0);
}

void    shell_unset(t_shell *shell)
{
    update_env(shell->parsed[1], -1);
}

void    shell_echo(t_shell *shell)
{
    int i;

    if (!shell->parsed[1])
    {
        printf("\n");
        return;
    }
    if (strcmp(shell->parsed[1], "-n") == 0)
        i = 2;
    else
        i = 1;
    if (!shell->parsed[i])
        return;
    while (shell->parsed[i])
    {
        printf("%s", shell->parsed[i]);
        if (shell->parsed[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (strcmp(shell->parsed[1], "-n") != 0)
        printf("\n");
}

void    shell_chdir(char *dest, char *old_dir)
{
    getcwd(old_dir, 4096);
    printf("%s", old_dir);
    if (!dest)
        chdir(getenv("HOME"));
    else
    {
        if (opendir(dest))
            chdir(dest);
        else if (ENOENT == errno) 
            printf("minishell: cd: %s: No such file or directory\n", dest);
    }
    update_env_pwds(old_dir);
}

void    execshell(t_shell *shell)
{
    if (shell->key_word == EXİT)
        shell->state = -1;
    else if (shell->key_word == PWD)
        printf("%s\n", getcwd(shell->path, 4096));
    else if (shell->key_word == CD)
        shell_chdir(shell->parsed[1], shell->path);
    else if (shell->key_word == CLEAR)
        printf("\e[1;1H\e[2J");
    else if (shell->key_word == ENV)
        print_env(shell->env);
    else if (shell->key_word == EXPORT)
        shell_export(shell);
    else if (shell->key_word == UNSET)
        shell_unset(shell);
    else if (shell->key_word == ECHO)
        shell_echo(shell);
    else if (shell->key_word == -2)
        printf("Quotes not matched\n");
    else
        printf("%s command not found\n", shell->parsed[0]);
    shell->key_word = -1;
}

void    exit_shell(t_shell *shell)
{
    write(2, "exit\n", 5);
    free(shell->parsed);
    system("leaks a.out");
}

void    parse(t_shell *shell, t_args *args)
{
    shell->parsed = ft_split(shell->readed_line, ' ');
    shell->is_command = quotes(args, shell->parsed[0]);
    if (shell->is_command == -1)
    {
        shell->key_word = -2;
        return;
    }
    if (strcmp(shell->parsed[0], "exit") == 0)
        shell->key_word = EXİT;
    else if (strcmp(shell->parsed[0], "pwd") == 0)
        shell->key_word = PWD;
    else if (strcmp(shell->parsed[0] , "cd") == 0)
        shell->key_word = CD;
    else if (strcmp(shell->parsed[0], "clear") == 0)
        shell->key_word = CLEAR;
    else if (strcmp(shell->parsed[0], "export") == 0)
        shell->key_word = EXPORT;
    else if (strcmp(shell->parsed[0], "unset") == 0)
        shell->key_word = UNSET;
    else if (strcmp(shell->parsed[0], "env") == 0)
        shell->key_word = ENV;
    else if (strcmp(shell->parsed[0], "echo") == 0)
        shell->key_word = ECHO;
    else
        shell->key_word = -1;
}

void    init_program(t_shell *shell, t_args *args, char **envp)
{
    shellprogram.life = 1;
    getcwd(shell->path, 4096);
    init_env(shell, envp);
    init_args(args);
    signal(SIGINT, handler);
}

int quit_control(t_shell *shell)
{
    if (!(shell->readed_line))
    {
        shellprogram.life = 0;
        write(2, "exit\n", 5);
        return (1);
    }
    return (0);
}

int main(int ac, char **av, char **envp)
{
    t_shell shell;
    t_args  args;

    shellprogram.g_shell = &shell;
    shell.state = 1;
    signal(SIGQUIT, SIG_IGN);
    init_program(&shell, &args, envp);
    while (shell.state == 1)
    {
        shell.readed_line = readline("\033[0;33mguest@minishell>\033[0m ");
        if (quit_control(&shell))
            break;
        if (!(strlen(shell.readed_line) == 0))
        {
            parse(&shell, &args);
            execshell(&shell);
            reset();
            add_history(shell.readed_line);
        }
        free(shell.readed_line);
    }
    if (shellprogram.life == 1 || shell.state == -1)
        exit_shell(&shell);
}
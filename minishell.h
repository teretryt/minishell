#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>

enum    KEYWORDS
{
    CD = 1,
    PWD = 2,
    EXİT = 3,
    CLEAR = 4,
    EXPORT = 5,
    UNSET = 6,
    ECHO = 7,
    ENV = 8
};

typedef struct s_args
{
    int     i;
    int     size;
    int     start_q;
    int     end_q;
    char    **args;
} t_args;


typedef struct s_shell
{
    int     state;
    char    path[4096];
    char    *readed_line;
    char    **parsed;
    char    **env;
    int     key_word;
    int     is_command;
}   t_shell;

typedef struct s_program
{
    t_shell *g_shell;
    int     life;
} t_program;

extern t_program shellprogram;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlen(const char *str);
void    init_env(t_shell *shell, char **envp);
void    print_env(char **str);
void    update_env(char *keyval, int state);
void    get_env(char *str);
int     quotes(t_args *args, char *str);
int     quotes_counter(char *str);
void    get_quote_args(t_args *arg, char *str);
void    shell_export(t_shell *shell);
void    shell_unset(t_shell *shell);
void    update_env_pwds(char *old_dir);
void    handler(int sig);
void    handler2(int sig);






#endif
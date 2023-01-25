#include "minishell.h"

void    init_env(t_shell *shell, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    shell->env =  malloc(sizeof(char *) * (i + 1));
    
    i = -1;
    while (envp[++i])
		shell->env[i] = strdup(envp[i]);
}

void    print_env(char **str)
{
    int i;

    i = 0;
    while (str[i])
        printf("MİKTAR %d,  %s\n", i,str[i++]);
}

void    get_env(char *str)
{
    //tek tırnak ve çift tırnak için split ile işlemleri ayarla echo fonk a get_env eklemeyi unutmaaaa!!!!
}

void    update_env(char *keyval, int state)
{
    char    **split;
    char    **tmp;
    int     find;
    int     i;

    find = 0;
    i = 0;
    while (shellprogram.g_shell->env[i])
        i++;
    tmp = (char **)malloc((sizeof(char *) * i) + (state + 2));
    i = 0;
    while (shellprogram.g_shell->env[i])
    {
        if (find != 1)
            tmp[i] = shellprogram.g_shell->env[i];
        if (state == -1 && (strcmp(keyval, shellprogram.g_shell->env[i]) == 0))
        {
            tmp[i] = shellprogram.g_shell->env[i + 1];
            find = 1;
        }
        else if (find == 1)
            tmp[i] = shellprogram.g_shell->env[i + 1];
        i++;
    }
    if (state == 0)
    {
        split = ft_split(keyval, '=');
        tmp[i++] = ft_strjoin(ft_strjoin(split[0], "="), split[1]);
    }
    tmp[i] = '\0';
    shellprogram.g_shell->env = tmp;
}

void    update_env_pwds(char *old_dir)
{
    int i;
    int find;

    find = 0;
    i = -1;
    while (shellprogram.g_shell->env[++i] && find != 1)
        if (strncmp(shellprogram.g_shell->env[i], "OLDPWD", 6) == 0)
            find++;
    if (find == 0)
        update_env(ft_strjoin("OLDPWD=", old_dir), 1);
    i = 0;
    while (shellprogram.g_shell->env[i])
    {
        if (strncmp(shellprogram.g_shell->env[i], "OLDPWD", 6) == 0)
            shellprogram.g_shell->env[i] = strdup(ft_strjoin("OLDPWD=", old_dir));
        else if (strncmp(shellprogram.g_shell->env[i], "PWD", 3) == 0)
        {
            getcwd(shellprogram.g_shell->env[i], 4096);
            shellprogram.g_shell->env[i] = ft_strjoin("PWD=", 
                shellprogram.g_shell->env[i]);
        }
        i++;
    }
}
#include "minishell.h"

void    handler(int sig)
{
    rl_replace_line("", 0);
	rl_on_new_line();
}

void    handler2(int sig)
{
    return;
}
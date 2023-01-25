#include "minishell.h"

int quotes_counter(char *str)
{
    int i;
    int counter1;
    int counter2;

    counter1 = 0;
    counter2 = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\"')
            counter1++;
        else if (str[i] == '\'')
            counter2++;
        i++;
    }
    if (counter1 % 2 == 0 && counter2 % 2 == 0)
        return (1);
    return (0);
}

void    quote_args(t_args *args, char *str, char quote)
{
    int close;

    close = 1;
    while (str[args->i != quote] && str[args->i] != '\0')
        args->i++;
    if (str[args->i] == '\0')
        close = 0;
    while ((str[args->i] == ' ' || str[args->i] == '\0') 
        && is_special(str[args->i]))
    {
        if (str[args->i] == quote)
            close = !close;
        else if (!close && is_special(str[args->i]))
            args->size++;
        args->i++;
    }
	while (is_space(input->line[input->i]))
		args->i++;
	args->size++;
}

void    get_quote_size(t_args *args, char *str)
{
    int     close;
    char    quote;
    //while içine almayı unutma
    if (str[args->i] == '"' || str[args->i] == '\'')
        quote_args(args, str, str[args->i++]);
    else
    {

    }
}

void    get_quote_args(t_args *args, char *str, char quote)
{
    int     close;
    int     mv;

    mv = 0;
    close = 1;
    args->i++;
    while (str[args->i + mv != quote] && str[args->i + mv] != '\0')
        mv++;
    if (str[args->i + mv] == '\0')
        close = 0;
    while ((str[args->i + mv] == ' ' || str[args->i + mv] == '\0') 
            && is_special(str[args->i + mv]))
    {
        if (str[args->i + mv] == quote)
            close = !close;
        mv++;
    }
    args->args[args->wc] = ft_substr(str, args->i - 1, mv + 1);
	while (is_space(input->line[input->i + k]) == 1)
		mv++;
	args->i += mv;
	args->wc++;
}

int    quotes(t_args *args,char *str)
{
    if(!quotes_counter(str))
        return (-1);
    get_quote_size(args, str);
    while (str[args->i])
    {
        if (str[args->i] == '"' || str[args->i] == '\'')
            get_quote_args(args, str, str[args->i]);
        else
        {
            break;
        }
    }
    return (1);
}
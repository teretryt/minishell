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

void    get_quote_args(t_args *args, char *str)
{
    int     close;
    char    quote_type;

    close = 0;
    if (str[0] == '\"' || str[0] == '\'')
        quote_type = str[0];
    else
        return;
    while (str[args->i] && str[args->i] == quote_type) //spesyal eklenecek heryere dikat!
    {   
        args->start_q++;
        args->i++;
    }
    while (str[args->i] && str[args->i] != quote_type)
        args->i++;
    while (str[args->i] && str[args->i] == quote_type)
    {
        args->end_q++;
        args->i++;
    }

}

int    quotes(t_args *args,char *str)
{
    int i;
    if(!quotes_counter(str))
        return (-1);
    get_quote_args(args, str);
    return (1);
}
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
    args.i++;
    while (str[args->i != quote] && str[args->i] != '\0')
        args->i++;
    if (str[args->i] == '\0')
        close = 0;
    while ((!(is_space(str[args->i]) || str[args->i] == '\0') || close)
        && !is_special(str[args->i]))
    {
        if (str[args->i] == quote)
            close = !close;
        args->i++;
    }
	while (is_space(input->line[input->i]))
		args->i++;
	args->size++;
}
//argüman sayısı bulma
void    get_quote_size(t_args *args, char *str)
{
    int     close;
    char    quote;

    while (str[args->i])
    {
        if (str[args->i] == '"' || str[args->i] == '\'')
            quote_args(args, str, str[args->i++]);
        else
        {
            printf("get_quote_size_hatası\n");
            return;
        }
    }
}
//argumanları almak için
void    get_is_quote(t_args *args, char *str, char quote)
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
    while ((!(is_space(str[args->i]) || str[args->i] == '\0') || close) 
            && !is_special(str[args->i + mv]))
    {
        if (str[args->i + mv] == quote)
            close = !close;
        mv++;
    }
    args->args[args->wc++] = ft_substr(str, args->i - 1, mv + 1);
	while (is_space(input->line[input->i + k]) == 1)
		mv++;
	args->i += mv;
}

void    get_is_not_quote(t_args *arg, char *str)
{
    return ;
}

void    get_special_args(t_args *args, char *str)
{
    int     mv;
    char    sp_char;

    mv = 0;
    args->i++;
    sp_char = str[args->i - 1];
    while (!is_space(str[args->i + mv]) || str[args->i + mv] != '\0')
    {
        if (mv != 0 || str[args->i + mv] != sp_char || 
            (isnt_redirect(str[args->i + mv])))
        {
            break;
        }
        else
            mv++;
    }
    args->args[args->wc++] == ft_substr(str, sp_char, mv + 1);
    while (is_space(str[args->i + mv]))
        mv++;
    args->i += mv;
}

void    res_var(t_args *args)
{
    args->i = 0;
}

int    quotes(t_args *args, char *str)
{
    if(!quotes_counter(str))
        return (-1);
    get_quote_size(args, str);
    res_var(args);
    while (str[args->i])
    {
        if (str[args->i] == '"' || str[args->i] == '\'')
            get_is_quote(args, str, str[args->i]);
        else if (is_special(str[args->i]))
            get_special_args(args, str);
        else
            printf("daha yapılmadi\n");    
        //get_is_not_quote(args, str[args->i]);
    }
    printf("%s\n", args->args[0]);
    printf("%d\n", args->size);
    exit(1);
    return (1);
}
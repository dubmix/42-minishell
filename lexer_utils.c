#include "minishell.h"


void    print_list(t_env *env) // print the envp
{
    t_env *tmp = env;
    while (tmp != NULL)
    {
            printf("node is %s and value is %s\n", tmp->name, tmp->value);
            tmp = tmp->next;
    }
}

void    print_list_tok(t_token **tok)
{
    t_token tmp = tok;
    int i = 0;
    while (i < 5)
    {
        printf("node is %s, number is %d\n", tmp->command, tmp->nb);
        tmp = tmp->next;
    }
}

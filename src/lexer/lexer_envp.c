#include "../../minishell.h"

void add_stack_back_env(t_env **env_lst, t_env *new)
{
    t_env *tail;

    if (!new)
        return;
    if (!(*env_lst))
    {
        *env_lst = new;
        return;
    }
    tail = *env_lst;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = new;
}

void new_node_env(t_env **env_list, char **string)
{
    t_env	*new;

    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return ;
    new->name = ft_strdup(string[0]);
    new->value = ft_strdup(string[1]);
    if (!new->name || !new->value)
        return ; // error handling
    new->next = NULL;
    add_stack_back_env(env_list,new);
}

int size_envp(char **envp)
{
    int i = 0;

    while (envp[i] != NULL)
        i++;
    return (i);
}

t_env *init_envp(char **envp, t_shell *cmd)
{
    int i;
    int j;
    char **string;
    t_env *envir;
    int size_env;

    size_env = size_envp(envp);
    cmd->envp_copy = (char **)malloc(sizeof(char *) * size_env + 1);
    envir = NULL;
    i = 0;
    while (envp[i] != NULL)
    {
        cmd->envp_copy[i] = ft_strdup(envp[i]);
        string = ft_split(envp[i], '=');
        new_node_env(&envir, string);
        j = 0;
        while(string[j] != NULL)
        {
            free(string[j]);
            j++;
        }
        i++;
    }
    return (envir);
}

int length_arr_var(char **arr_var, t_shell *cmd)
{
    int j = 0;
    int length = 0;
    while (arr_var[j] != NULL && j < cmd->size_arr_var)
    {
        length += ft_strlen(arr_var[j]);
        j++;     
    }
    return (length);
}

int length_string_without_var(char *string)
{
    int i = 0;
    char *temp = string;
    int length = 0;
    while (temp[i] != '\0')
    {
        if (temp[i] == '$')
        {
            while (temp[i] != ' ' && temp[i] != 34)
                i++;
        }
        else
            length++;
        i++;
    }
    return (length);
}
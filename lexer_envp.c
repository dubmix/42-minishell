#include "minishell.h"
   
void look_into_envir(t_shell *cmd, t_token *var)
{
    t_shell *tmp = cmd;
    char **string;
    int j = 0;
    string = ft_split(var->command, '$');
    while (tmp->envir != NULL)
    {
        if (ft_strncmp(string[0], tmp->envir->name, ft_strlen(var->command)) == 0)
        {
            free(var->command);
            var->command = ft_strdup(tmp->envir->value);
            break;
        }
        tmp->envir = tmp->envir->next;
    }
    while(string[j] != NULL)
    {
        free(string[j]);
        j++;
    }
    return ;
}

char *look_into_envir_quote(t_shell *cmd, char *variable)
{
    t_shell *tmp = cmd;
    char **string;
    int j = 0;
    string = ft_split(variable, '$');
    while (tmp->envir != NULL)
    {
        if (ft_strncmp(string[0], tmp->envir->name, ft_strlen(variable)) == 0)
        {
            free(variable);
            variable = ft_strdup(tmp->envir->value);
            break;
        }
        tmp->envir = tmp->envir->next;
    }
    while(string[j] != NULL)
    {
        free(string[j]);
        j++;
    }
    return (variable);
}

void    copy_expand_var(t_token *var, char *string, int length)
{
    int i = 0;
    int j = 0;
    int length_final = ft_strlen(var->command) - length + ft_strlen(string);
    char *new_str;
    int k = 0;
    new_str = malloc(sizeof(char *) * (length_final));
    while (var->command[i] != '\0')
    {
        new_str[j] = var->command[i];
        if (var->command[i] == '$')
        {
            while (string[k] != '\0')
            {
                new_str[j] = string[k];
                k++;
                j++;
            }
            i = i + length; // potentially - 1
        }
            i++;
            j++;
    }
    free(var->command);
    var->command = ft_strdup(new_str);
    free(new_str);
}


void    double_quote_env(t_shell *cmd, t_token *var)
{
    int i = 0;
    int start;
    char *string;
    int length_var;
    while(var->command[i] != '\0')
    {
        if (var->command[i] == '$')
        {
            start = i;
            while (var->command[i] != ' ')
                i++;
            string = ft_substr(var->command, start, i - start);
            length_var = ft_strlen(string);
            string = look_into_envir_quote(cmd, string);
            copy_expand_var(var, string, length_var);
            free(string);
        }    
        i++;
    }
}

void expand_var(t_shell *cmd)
{
    if (cmd->tokens->type == 4)
            look_into_envir(cmd, cmd->tokens);
        else if (cmd->tokens->state == 1)
            double_quote_env(cmd, cmd->tokens);
    while (cmd->tokens->next != NULL)
    {
        if (cmd->tokens->type == 4)
            look_into_envir(cmd, cmd->tokens);
        else if (cmd->tokens->state == 1)
            double_quote_env(cmd, cmd->tokens);
        cmd->tokens = cmd->tokens->next;
    }
}

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
    new->next = NULL;
    add_stack_back_env(env_list,new);
}

t_env *init_envp(char **envp)
{
    int i;
    int j;
    char **string;
    i = 0;
    t_env *envir;
    envir = NULL;
    while (envp[i] != NULL)
    {
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

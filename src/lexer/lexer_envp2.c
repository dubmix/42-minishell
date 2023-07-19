#include "../../minishell.h"

char **string_variables(t_shell *cmd, t_token *var)
{
    char **arr_string;
    char *temp = var->command;
    int i = 0;
    int j = 0;
    int start = 0;

    cmd->size_arr_var = countsubstr(var->command, '$') - 1;
    arr_string = (char **)malloc(sizeof(char *) * cmd->size_arr_var); // + 1 or not ?
    if (!arr_string)
        return (NULL);
    while (temp[i] != '\0')
    {
        if (temp[i] == '$')
        {
            start = i + 1; // the + 1 is to directly take out the $ from the string 
            while (temp[i] != ' ' && temp[i] != 34) // 34 is double quote
                i++;
            arr_string[j] = look_into_envir_quote(cmd, ft_substr(var->command, start, i - start));
            j++;
        }
        i++;
    }
    cmd->size_arr_var = j;
    return (arr_string);
}

void double_quote_env(t_shell *cmd, t_token *var)
{
    int i = 0;
    char **arr_var;
    int j = 0;
    char *new_string;
    int k = 0;

    arr_var = string_variables(cmd, var);
    new_string = (char *)malloc(sizeof(char) * (length_arr_var(arr_var, cmd) + length_string_without_var(var->command)) + 1);
    if (!new_string)
        return ;
    while(var->command[i] != '\0')
    {
        if (var->command[i] == '$')
        {
            while (var->command[i] != ' ' && var->command[i] != 34)
                i++;
            new_string = ft_strjoin(new_string, arr_var[k]);
            j = ft_strlen(new_string);
            k++;
        }
        new_string[j] = var->command[i];
        i++;
        j++;
    }
    new_string[j] = '\0';
    free(var->command);
    var->command = ft_strdup(new_string);
    free(new_string);
    // free_arr(arr_var);  // cause issue, to be checked later
}

void expand_var(t_shell* cmde) 
{
    t_token* tmp = cmde->tok_lst;

    while (tmp != NULL) 
    {
        if (tmp->type == 4) 
        {
            look_into_envir(cmde, tmp);
            tmp->type = 0;
        }
        else if (tmp->state == 1) 
        {
            double_quote_env(cmde, tmp);
            tmp->type = 0;
        }
        tmp = tmp->next;
    }
}

void look_into_envir(t_shell *cmd, t_token *var)
{
    t_env *tmp = cmd->env_lst;
    char **string;
    int j = 0;
    string = ft_split(var->command, '$');
    while (tmp != NULL)
    {
        if (ft_strncmp(string[0], tmp->name, ft_strlen(var->command)) == 0)
        {
            free(var->command);
            var->command = ft_strdup(tmp->value);
            break;
        }
        tmp = tmp->next;
    }
    while(string[j] != NULL)
    {
        free(string[j]);
        j++;
    }
    return ;
}

char *look_into_envir_quote(t_shell *cmd, char *string)
{
    t_env *tmp = cmd->env_lst;

    while (tmp != NULL)
    {
        if (ft_strncmp(string, tmp->name, ft_strlen(string)) == 0)
        {
            free(string);
            string = ft_strdup(tmp->value);
            break;
        }
        tmp = tmp->next;
    }
    return (string);
}
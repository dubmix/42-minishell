#include "minishell.h"
   
void look_into_envir(t_shell *cmd, t_token *var)
{
    t_env *tmp = cmd->envir;
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
    t_env *tmp = cmd->envir;

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

// void    copy_expand_var(t_shell *cmd, t_token *var, int start, int f)
// {
//     int i = 0;
//     int j = 0;
//     char *new_str;
//     int k = 0;
//     char *string;
//     int length;
//     int guard = 0;

//     string = ft_substr(var->command, start, f - start);
//     string = look_into_envir_quote(cmd, string);
//     length = ft_strlen(string);
//     int length_final = ft_strlen(var->command) - length + ft_strlen(string);
//     printf("STRING IS %s, %d\n", string, length_final);
//     new_str = (char *)malloc(sizeof(char) * (length_final) + 1);
//     if (!new_str)
//         return ;
//     printf("NEW %s\n", new_str);
//     while (var->command[i] != '\0')
//     {
//         if (var->command[i] == '$' && guard == 0)
//         {
//             while (string[k] != '\0')
//             {
//                 new_str[j] = string[k];
//                 k++;
//                 j++;
//             }
//             i = i + length;
//             guard = 1;
//         }
//         new_str[j] = var->command[i];
//     // printf("new string is %s, j is %d, i is %d\n", new_str, j, i);
//             i++;
//             j++;
//     }
//     new_str[j] = '\0';
//     free(var->command);
//     var->command = ft_strdup(new_str);
//     free(new_str);
//     free(string);
// }

// void    double_quote_env(t_shell *cmd, t_token *var)
// {
//     int i = 0;
//     int start;
//     // char *string;
//     // int length_var;
//     while(var->command[i] != '\0')
//     {
//         if (var->command[i] == '$')
//         {
//             start = i;
//             while (var->command[i] != ' ' && var->command[i] != 34)
//                 i++;
//             // string = ft_substr(var->command, start, i - start);
//             // length_var = ft_strlen(string);
//             // string = look_into_envir_quote(cmd, string);
//             // copy_expand_var(var, string, length_var);
//             copy_expand_var(cmd, var, start, i);
//             // free(string);
//         }    
//         i++;
//     }
// }

char **string_variables(t_shell *cmd, t_token *var)
{
    char **arr_string;
    char *temp = var->command;
    int i = 0;
    int j = 0;
    int start = 0;
    arr_string = (char **)malloc(sizeof(char *) * (countsubstr(temp, '$') - 1) + 1);
    if (!arr_string)
        return (NULL);
    while (i != 14)//temp[i] != '\0')
    {
        if (temp[i] == '$')
        {
            start = i + 1; // the + 1 is to directly take out the $ from the string 
            // while (temp[i] != ' ' && temp[i] != 34) // 34 is double quote
            //     i++;
            i = i +4;
            arr_string[j] = look_into_envir_quote(cmd, ft_substr(var->command, start, i - start));
            printf("%s", arr_string[j]);
            j++;
        }
        i++;
    }
    arr_string[j] = 0;
    return (arr_string);
}

int length_arr_var(char **arr_var)
{
    int j = 0;
    int length = 0;
    while (arr_var[j] != 0)
    {
        length += ft_strlen(arr_var[j]);
        printf("YOOO %zu string is %s\n", ft_strlen(arr_var[j]), arr_var[j]);
        j++;     
    }
    printf("WITH VAR %d", length);
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
    printf("WITHOUT VAR %d", length);

    return (length);
}

void double_quote_env(t_shell *cmd, t_token *var)
{
    // int i = 0;
    char **arr_var;
    // int j = 0;
    char *new_string;
    // int k = 0;

    printf("%s", var->command);
    arr_var = string_variables(cmd, var);
    printf("%s", arr_var[0]);

    new_string = (char *)malloc(sizeof(char) * (length_arr_var(arr_var) + length_string_without_var(var->command)) + 1);
    if (!new_string)
        return ;
    // while(var->command[i] != '\0')
    // {
    //     if (var->command[i] == '$')
    //     {
    //         while (var->command[i] != ' ' && var->command[i] != 34)
    //             i++;
    //         new_string = ft_strjoin(new_string, arr_var[k]);
    //         j = ft_strlen(new_string);
    //         k++;
    //     }
    //     new_string[j] = var->command[i];
    //     i++;
    //     j++;
    // }
    // new_string[j] = '\0';
    // free arr of string + string
}

void expand_var(t_shell* cmde) 
{
    t_token* tmp = cmde->tokens;

    while (tmp != NULL) 
    {
        if (tmp->type == 4) 
        {look_into_envir(cmde, tmp); write(1, "LLL", 3);}
        else if (tmp->state == 1) 
            double_quote_env(cmde, tmp);
        tmp = tmp->next;
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
    if (!new->name || !new->value)
        return ; // error handling
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

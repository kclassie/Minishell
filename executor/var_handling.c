#include "minishell.h"

t_list	*ft_find_var(t_list **var_list, char *var_name)
{
	t_list	*tmp;
	t_list	*next;
	t_var	*tmp_ptr;

	tmp = *var_list;
	while (tmp)
	{
		next = tmp->next;
		tmp_ptr = (t_var *)tmp->content;
		if (!(ft_strncmp(var_name, tmp_ptr->name, 255)))
			return (tmp);
		tmp = next;
	}
	return (NULL);
}

int	ft_chng_var(t_list **var_list, char *var_name, char *new_value, int var_id)
{
	t_list	*tmp_list;
	t_var	*tmp_val;

	tmp_list = ft_find_var(var_list, var_name);
	if (tmp_list == NULL)
		return (ft_save_var(var_list,ft_strjoin(ft_strjoin(var_name,
						"=" ),new_value), var_id));
	tmp_val = (t_var *) tmp_list->content;
	free(tmp_val->value);
	tmp_val->value = malloc(sizeof(char) * (ft_strlen(new_value) + 1));
	if (!tmp_val->value)
		return (0);
	strlcpy(tmp_val->value, new_value, ft_strlen(new_value) + 1);
	return (1);
}

int	ft_clear_vars(t_list **var_list)
{
	t_list	*tmp;
	t_list	*next;
	t_var	*tmp_var;

	tmp = *var_list;
	while (tmp)
	{
		next = tmp->next;
		tmp_var = (t_var *)(tmp->content);
		if (tmp_var)
		{
			free(tmp_var->value);
			free(tmp_var->name);
			free(tmp_var);
		}
		free(tmp);
		tmp = next;
	}
	*var_list = NULL;
	return (0);
}

void	*ft_make_var(char *var, t_var **variable)
{
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	while (var[len1] != '=')
		len1++;
	(*variable)->name = malloc(sizeof (char) * len1);
	if (!(*variable)->name)
		return (NULL);
	ft_strlcpy((*variable)->name, var, len1 + 1);
	while (var[len1++] != '\0')
		len2++;
	if (len2 > 0)
	{
		(*variable)->value = malloc(sizeof(char) * len2);
		if (!(*variable)->value)
			return (NULL);
		ft_strlcpy((*variable)->value, &var[len1 - len2], len2);
	}
	else
		(*variable)->value = NULL;
	return (variable);
}

//var_id: 0 - isn't exported to env; 1 - is exported to env
int	ft_save_var(t_list **var_list, char *var, int var_id)
{
	t_var	*variable;
	t_list	*new_val;
	void	*tmp_ptr;

	if (!var || !var_list)
		return (0);
	variable = malloc(sizeof(t_var));
	if (!variable)
		return (ft_clear_vars(var_list));
	if (!ft_make_var(var, &variable))
		return (ft_clear_vars(var_list));
	variable->is_exported = var_id;
	tmp_ptr = variable;
	new_val = ft_lstnew(tmp_ptr);
	if (!new_val)
		return (ft_clear_vars(var_list));
	ft_lstadd_back(var_list, new_val);
	return (1);
}

//int main()
//{
//	t_list **var_list;
//	extern char **environ;
//
//	while (*environ != NULL)
//	{
//		ft_save_var(&var_list, *environ, 1);
//		environ++;
//	}


//Если надо будет воспользоваться листами::


//	t_list	*tmp;
////	t_list	*next;
//	t_var	*tmp_ptr;
////
////	tmp = *var_list;
////	while (tmp)
////	{
////		next = tmp->next;
////		tmp_ptr = (t_var *)tmp->content;
////		printf("%s=%s\n", tmp_ptr->name, tmp_ptr->value);
////		tmp = next;
////	}
//	tmp = ft_find_var(&var_list, "HOME");
//	tmp_ptr = tmp->content;
//	printf("%s=%s\n", tmp_ptr->name, tmp_ptr->value);
//	ft_clear_vars(var_list); //это делаем перед закрытием все программы
//	return(1); //успешное завершение
//}
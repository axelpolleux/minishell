/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apolleux <apolleux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:23:44 by apolleux          #+#    #+#             */
/*   Updated: 2025/10/30 10:58:35 by apolleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_obj;
	void	*trigger;

	if (!lst || !f || !del)
		return (0);
	new_list = 0;
	while (lst)
	{
		trigger = f(lst->content);
		new_obj = ft_lstnew(trigger);
		if (!new_obj)
		{
			del(trigger);
			ft_lstclear(&new_list, del);
			return (0);
		}
		ft_lstadd_back(&new_list, new_obj);
		lst = lst->next;
	}
	return (new_list);
}

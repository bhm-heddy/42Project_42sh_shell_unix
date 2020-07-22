#include "../../includes/libft.h"

t_dlist	*ft_dlstnew(void *content, size_t content_size)
{
	t_dlist	*lstnew;

	if (!(lstnew = (t_dlist *)malloc(sizeof(t_dlist))))
		return (NULL);
	if (content == NULL)
	{
		lstnew->data = NULL;
		lstnew->size = 0;
	}
	else
	{
		lstnew->data = content;
		lstnew->size = content_size;
	}
	lstnew->prev = NULL;
	lstnew->next = NULL;
	return (lstnew);
}

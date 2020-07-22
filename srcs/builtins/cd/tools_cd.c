#include "libft.h"
#include "exec.h"
#include "struct.h"
#include "sh.h"
#include "var.h"
#include "ft_printf.h"
#include <dirent.h>
#include <sys/stat.h>

char		*ft_strcut(char *str, char *delim, unsigned int field)
{
	int		i;
	char	*res;
	char	*tmp;

	if (!str || !delim)
	{
		return (0);
	}
	if ((tmp = ft_strstr(str, delim)) && field > 1)
		return (ft_strcut(tmp + ft_strlen(delim), delim, field - 1));
	else if (field == 0 || field > 1)
		return (ft_strnew(0));
	if (tmp)
	{
		i = tmp - str;
		if (!(res = ft_strnew(i)))
			return (0);
		ft_strncpy(res, str, i);
	}
	else
		res = ft_strdup(str);
	return (res);
}

char		*ft_pathjoin(char *str1, char *str2)
{
	char	*ret;
	size_t	s1len;

	if (!str1 || !str2)
		return (0);
	s1len = ft_strlen(str1);
	if (!s1len || (str1[s1len - 1] == '/'))
		return (ft_strjoin(str1, str2));
	ret = ft_strjoin(str1, "/");
	ret = ft_strlclnjoin(ret, str2);
	return (ret);
}

char		*ft_strrep(char *str, char *rem, char *rep)
{
	char	*ret;
	char	*occurence;
	size_t	replen;

	replen = rep ? ft_strlen(rep) : 0;
	if (!str)
		return (NULL);
	if (!rem)
		return (ft_strdup(str));
	if (!(occurence = ft_strstr(str, rem)))
		return (str);
	if (!(ret = ft_strnew(ft_strlen(str) - ft_strlen(rem) + replen)))
		return (NULL);
	ft_strncpy(ret, str, occurence - str);
	if (replen)
		ft_strcat(ret, rep);
	ft_strcat(ret, occurence + ft_strlen(rem));
	return (ret);
}

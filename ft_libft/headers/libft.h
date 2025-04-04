/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:49:02 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/02 18:44:38 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include <unistd.h>

/*
Return size of string
*/
size_t	ft_strlen(const char *str);
/*
The strlcpy() function copies up to size - 1 characters from the
NUL-terminated string src to dst, NUL-terminating the result.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
/*
The strlcat() function appends the NUL-terminated string src to the end
of dst. It will append at most size - strlen(dst) - 1 bytes,
NUL-terminating the result.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/*
Check if "c" is aplhabetic or numeric character
*/
int		ft_isalnum(int c);
/*
Check if "c" is aplhabetic character
*/
int		ft_isalpha(int c);
/*
Check if "c" is sign character
*/
int		ft_issign(int c);
/*
Check if "c" is numeric character
*/
int		ft_isdigit(int c);
/*
Check if c is ascii character (from ascci table)
*/
int		ft_isascii(int c);
/*
Check if c is printable
*/
int		ft_isprint(int c);
/*
Check whether c is space, tab, white space... 
*/
int		ft_isblank(int c);

int		ft_isspace(int c);
/*
Convert all letters from lowercase to uppercase
*/
int		ft_toupper(int c);
/*
Convert all letters from uppercase to lowercase
*/
int		ft_tolower(int c);
/*
The  strcmp()  function compares the two strings s1 and s2.  The locale
is not taken into account (for  a  locale-aware  comparison,  see  str‐
coll(3)).  The comparison is done using unsigned characters.

strcmp() returns an integer indicating the result of the comparison, as
follows:

• 0, if the s1 and s2 are equal;

• a negative value if s1 is less than s2;

• a positive value if s1 is greater than s2.

The strncmp() function is similar, except it compares  only  the  first
(at most) n bytes of s1 and s2.
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*
The  strcmp()  function compares the two strings s1 and s2.  The locale
is not taken into account (for  a  locale-aware  comparison,  see  str‐
coll(3)).  The comparison is done using unsigned characters.

strcmp() returns an integer indicating the result of the comparison, as
follows:

• 0, if the s1 and s2 are equal;

• a negative value if s1 is less than s2;

• a positive value if s1 is greater than s2.
*/
int		ft_strcmp(const char *str1, const char *str2);
/*
The  memcmp()  function compares the first n bytes
(each interpreted as unsigned char)
of the memory areas s1 and s2.
*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/*
The  atoi() function converts the initial portion
of the string pointed to by nptr to int.
*/
int		ft_atoi(const char *str);

/*
Fills *s with zeros
*/
void	ft_bzero(void *s, size_t n);
/*
Parameters:
	s: The string on which to iterate.
	
	f: The function to apply to each character.
Description:
	Applies the function ’f’ on each character of
	the string passed as argument, passing its index
	as first argument. Each character is passed by
	address to ’f’ to be modified if necessary.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/*
Parameters:
	c: The character to output.
	
	fd: The file descriptor on which to write.
Description:
	Outputs the character ’c’ to the given file descriptor.
*/
void	ft_putchar_fd(char c, int fd);
/*
Parameters:
	s: The string to output.
	
	fd: The file descriptor on which to write.
Description:
	Outputs the string ’s’ to the given file descriptor.
*/
void	ft_putstr_fd(char *s, int fd);
/*
Parameters:
	s: The string to output.
	
	fd: The file descriptor on which to write.
Description:
	Outputs the string ’s’ to the given file descriptor
	followed by a newline.
*/
void	ft_putendl_fd(char *s, int fd);
/*
Parameters
	n: The integer to output.

	fd: The file descriptor on which to write.
Description:
Outputs the integer ’n’ to the given file descriptor.
*/
void	ft_putnbr_fd(int n, int fd);
/*
Free allocate memory for 2D array
*/
void	ft_free_2d_array(char **arr, int row);

/*
The  memset()  function  fills  the  first  n  bytes of the memory area
pointed to by s with the constant byte c.
*/
void	*ft_memset(void *s, int c, size_t n);
/*
The  memcpy()  function  copies  n bytes from memory
area src to memory area dest.
The memory areas must not overlap.
Use memmove(3)  if  the memory areas do overlap.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n);
/*
The  memmove()  function  copies n bytes from memory area src to memory
area dest.  The memory areas may overlap: copying takes place as though
the  bytes in src are first copied into a temporary array that does not
overlap src or dest, and the bytes are then copied from  the  temporary
 array to dest.
*/
void	*ft_memmove(void *dest, const void *src, size_t n);
/*
 The  memchr()  function  scans  the 
initial n bytes of the memory area
pointed to by s for the first instance of c.
Both c and the  bytes  of
the memory area pointed to by s
are interpreted as unsigned char.
*/
void	*ft_memchr(const void *s, int c, size_t n);
/*
Allocate memory for array and fills with zeros
*/
void	*ft_calloc(size_t nmemb, size_t size);

/*
The  strchr() function returns a pointer
to the first occurrence of the
character c in the string s.
*/
char	*ft_strchr(const char *s, int c);
/*
The strrchr() function returns a pointer to the last occurrence of 
the character c in the string s.
*/
char	*ft_strrchr(const char *s, int c);
/*
The strnstr() function locates the first occurrence of the
null-terminated string little in the string big, where not more
than len characters are searched. Characters that appear after a
‘\0’ character are not searched. Since the strnstr() function is a
FreeBSD specific API, it should only be used when portability is not a concern.
*/
char	*ft_strnstr(const char *big, const char *little, size_t len);
/*
The  strdup() function returns a pointer to a new string which is a
duplicate of the string s. Memory for the new string is obtained with
malloc(3), and can be freed with free(3).
*/
char	*ft_strdup(const char *s);
/*
Parameters:
	s: The string from which to create the substring.
	
	start: The start index of the substring in the string ’s’.
	
	len: The maximum length of the substring.
Return value:
	The substring. NULL if the allocation fails.
Description:
	Allocates (with malloc(3)) and returns a substring
	from the string ’s’.
	The substring begins at index ’start’ and is of
	maximum size ’len’.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*
Parameters:
	s1: The string to be trimmed.
	
	set: The reference set of characters to trim.
Return value:
	The trimmed string. NULL if the allocation fails.
Description:
	Allocates (with malloc(3)) and returns a copy of
	’s1’ with the characters specified in ’set’ removed
	from the beginning and the end of the string.
*/
char	*ft_strtrim(char const *s1, char const *set);
/*
Parameters:
	s1: The prefix string.
	
	s2: The suffix string.

Return value:
	The new string. NULL if the allocation fails.
Description:
	Allocates (with malloc(3)) and returns a new
	string, which is the result of the concatenation
	of ’s1’ and ’s2’.
*/
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin3(const char *dest, const char *str2, const char *str3);

/*
Parameters:
	n: the integer to convert.
Return value:
	The string representing the integer.
	NULL if the allocation fails.
Description:
	Allocates (with malloc(3)) and returns a string
	representing the integer received as an argument.
	Negative numbers must be handled.
*/
char	*ft_itoa(int n);
/*
Parameters:
	s: The string on which to iterate.

	f: The function to apply to each character.
Return value:
	The string created from the successive applications of ’f’.
	Returns NULL if the allocation fails.
Description:
	Applies the function f to each character of the
	string s, passing its index as the first argument
	and the character itself as the second. A new
	string is created (using malloc(3)) to collect the
	results from the successive applications of f.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*
Parameters:
	s: The string to be split.

	c: The delimiter character.
Return value:
	The array of new strings resulting from the split.
	NULL if the allocation fails.
Description:
	Allocates (with malloc(3)) and returns an array
	of strings obtained by splitting ’s’ using the
	character ’c’ as a delimiter. The array must end
	with a NULL pointer.
*/
char	**ft_split(char const *s, char c);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*
Parameters:
	content: The content to create the node with.
Return value:
	The new node
Description:
	Allocates (with malloc(3)) and returns a new node.
	The member variable ’content’ is initialized with
	the value of the parameter ’content’. The variable
	’next’ is initialized to NULL.
*/
t_list	*ft_lstnew(void *content);
/*
Parameters:
	lst: The beginning of the list.
Return value:
	Last node of the list
Description:
	Returns the last node of the list.
*/
t_list	*ft_lstlast(t_list *lst);
/*
Parameters:
	lst: The address of a pointer to a node.

	f: The address of the function used to iterate on the list.

	del: The address of the function used to delete
	the content of a node if needed.
Return value:
	The new list.
	NULL if the allocation fails.
Description:
	Iterates the list ’lst’ and applies the function
	’f’ on the content of each node. Creates a new
	list resulting of the successive applications of
	the function ’f’. The ’del’ function is used to
	delete the content of a node if needed.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*
Parameters:
	lst: The address of a pointer to the first link of a list.

	new: The address of a pointer to the node to be added to the list.
Description:
	Adds the node ’new’ at the beginning of the list.
*/
void	ft_lstadd_front(t_list **lst, t_list *new);
/*
Parameters:
	lst: The address of a pointer to the first link of a list.

	new: The address of a pointer to the node to be added to the list.
Description:
	Adds the node ’new’ at the end of the list.
*/
void	ft_lstadd_back(t_list **lst, t_list *new);
/*
Parameters:
	lst: The node to free.

	del: The address of the function used to delete the content.
Description:
	Takes as a parameter a node and frees the memory of
	the node’s content using the function ’del’ given
	as a parameter and free the node. The memory of
	’next’ must not be freed.
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *));
/*
Parameters:
	lst: The address of a pointer to a node.

	del: The address of the function used to delete the content of the node.
Description:
	Deletes and frees the given node and every
	successor of that node, using the function ’del’
	and free(3).
	Finally, the pointer to the list must be set to	NULL.
*/
void	ft_lstclear(t_list **lst, void (*del)(void *));
/*
Parameters:
	lst: The address of a pointer to a node.

	f: The address of the function used to iterate on the list.
Description:
	Iterates the list ’lst’ and applies the function
	’f’ on the content of each node.
*/
void	ft_lstiter(t_list *lst, void (*f)(void *));

/*
Parameters:
	lst: The beginning of the list.
Return value:
	The length of the list
Description:
	Counts the number of nodes in a list.
*/
int		ft_lstsize(t_list *lst);
/*
Free allocate memory for 2d char array
*/
void	ft_free_2d_array(char **arr, int row);

#endif

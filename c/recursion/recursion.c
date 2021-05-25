#include "recursion.h"

size_t Fibunacci(size_t index)
{
	size_t value1 = 1;
	size_t value2 = 1;
	size_t temp = value1;
	size_t counter = 1;

	while (counter < index )
	{
		value2 = value1;
		value1 = temp + value1;
		temp = value2;
		++counter;
	}

	return(value2);
}

size_t FibunacciR(size_t index)
{
    if (index < 1)
    {
        return (0);
    }
    if (index <= 2)
    {
        return (1);
    }


    return (FibunacciR(index-1) + FibunacciR(index-2));
}

size_t StrLenR(const char *str)
{
    if ('\0' == *str)
    {
        return (0);
    }

    return (StrLenR(str+1) + 1);
}

int StrCmpR(const char *s1, const char *s2)
{
    if ((*s1 == *s2) && (*s1 != '\0'))
    {
        return (StrCmpR(s1+1, s2+1));
    }

    return (*s1 - *s2);
}

char *StrCpyR(char *dest, const char *src)
{
    if ((*src == '\0'))
    {
        *dest = '\0';
        return dest;
    }

    *dest = *src;
    StrCpyR(dest+1, src+1);
    return dest;
}

char *StrCatR(char *dest, const char *src)
{
    size_t length = StrLenR(dest);

    if ((*src == '\0'))
    {
        *(dest + length) = '\0';
        return dest;
    }

    *(dest + length) = *src;
    *(dest + length+ 1) = '\0';
    StrCatR(dest, src+1);

    return dest;
}

char *StrStrR(const char *haystack, const char *needle)
{
	char *temp = NULL;

	if (('\0' != *needle) && ('\0' == *haystack))
	{
		return (NULL);
	}
	else if ('\0' == *needle)
	{
		return ((char *)haystack);
	}
	else
	{
		if ((*haystack == *needle))
		{
			temp = StrStrR(haystack + 1, needle + 1);
			if (NULL != temp)
			{
				return (temp - 1);
			}
			else
			{
				return (temp);
			}
		}
		else
		{
			return (StrStrR(haystack + 1, needle));
		}
	}
}

static sll_node_t *RecursiveFlip(sll_node_t *current, sll_node_t *prev)
{
    sll_node_t *temp = current->next;

    current->next = prev;
    if (NULL == temp)
    {
        return current;
    }
    return(RecursiveFlip(temp, current));
}

sll_node_t *SLLFlipR(sll_node_t *node)
{
    return(RecursiveFlip(node, NULL));
}

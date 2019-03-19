#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char *strtok_custom(char *s, char *delim)
{
	static char *buf;
	int len = strlen(delim);
	if (s!= NULL) buf = s;
	if (*buf == '\0') return NULL;
	if (len == 0) return NULL;

	char *res = buf, *b, *d;
	
	for (b = buf; *b != '\0'; b++)
	{
		for (d = delim; *d != '\0'; d++)
		{
			if (*b == *d)
			{
				// replacing the delimiter with null
				*b = '\0';
				// update buf pointer to the next character after delim
				buf = b + 1;
				// check for delimiters in the start
				if (b == res) { res++; continue; }
				return res;
			}
		}
	}
	if (*b == '\0') buf = b;
	return res;
}

void tokenise(char *s, char *delim)
{
	printf("Tokens are :\n");
	char *tok;
	for (tok = strtok_custom(s, delim); tok != NULL; tok = strtok_custom(NULL, delim))
	{
		printf("%s\n", tok);
	}
}
int main(int argc, char *argv[])
{
	char *text, *pat;
	if (argc < 3)
	{
		text = (char *)malloc(strlen("sam path,sam-antha.sathvik") + 1);
		pat = (char *)malloc(strlen(" ,.-") + 1);
		strcpy(text, "sam path,sam-antha.sathvik");
		strcpy(pat, " ,.-");
	}
	else
	{
		text = argv[1];
		pat = argv[2];
	}
	printf("text: %s \n pattern : %s\n", text, pat);
	//printf("null strings : %c , %c\n", text[strlen(text)] , pat[strlen(pat)]);
	tokenise(text, pat);

	return 0;
}
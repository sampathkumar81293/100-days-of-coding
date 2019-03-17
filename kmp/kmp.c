#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int preprocess(char *p, int **a)
{
	
	int i, k, len = strlen(p);
	for ( i = 1, k=0; i < len ; i++)
	{
		while (k && p[k] != p[i]) k = (*a)[k-1];
		if (p[k] == p[i]) k++;
		(*a)[i] = k;
	}
}

int kmp(char *t, char *p)
{
	int lent = strlen(t) , lenp = strlen(p);
	int i, k;
	if (lenp ==  0) return 0;
	int *prep = (int *)malloc(sizeof(int)*lenp);
	preprocess(p, &prep);
	for (i = 0, k = 0; i < lent ; i++)
	{
		while (k && p[k] != t[i])k = prep[k - 1];
		if (p[k] == t[i])k++;
		if (k == lenp) return i - k + 1;
	}
	return -1;
}
int main(int argc , char *argv[])
{
	char *text, *pat;
	if (argc < 3)
	{
		text = (char *)malloc(strlen("sampathsamanthasathvik")+1);
		pat = (char *)malloc(strlen("sam") + 1);
		strcpy(text, "sampathsamanthasathvik");
		strcpy(pat ,"sam");
	}
	else
	{
		text = argv[1];
		pat = argv[2];
	}
	printf("text: %s \n pattern : %s\n", text, pat);
	printf("index: %d\n", kmp(text, pat));

	return 0;
}
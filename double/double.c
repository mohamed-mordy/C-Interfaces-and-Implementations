// includes
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

// data
int linenum;

// prototypes
int getword(FILE*, char*, int);
void doubleword(char*, FILE*);

// functions
int main(int argc, char* argv[])
{
	for(int i = 1; i < argc; i++)
	{
		FILE* fp = fopen(argv[i], "r");
		if(fp == NULL)
		{
			fprintf(stderr, "%s: can't open '%s' (%s) ", argv[0], argv[i], strerror(errno));
			return EXIT_FAILURE;
		}
		else
		{
			doubleword(argv[i], fp);
			fclose(fp);
		}
	}

	if(argc == 1)
		doubleword(NULL, stdin);
	return EXIT_SUCCESS;
}

int getword(FILE* fp, char* buf, int size)
{
	int c;

	c = getc(fp);
	// scan forward to a nonspace or EOF
	for(; c != EOF && isspace(c); c = getc(fp))
		if(c == '\n')
			linenum++;
	// copy the word into buf[0..size-1]
	{
		int i = 0;
		for(; c != EOF && !isspace(c); c = getc(fp))
			if(i < size-1) 
				buf[i++] = tolower(c);
		if(i < size)
			buf[i] = '\0';
	}

	if(c != EOF) 
		ungetc(c, fp);
	// found a word?
	if(buf[0] != '\0') 
		return 1;
	return 0;
}

void doubleword(char* name, FILE* fp)
{
	char prev[128], word[128];

	linenum = 1;
	prev[0] = '\0';
	while(getword(fp, word, sizeof word))
	{
		if(isalpha(word[0]) && strcmp(prev, word) == 0)
			// word is a dublicate
		{
			if(name)
				printf("%s: ", name);
			printf("%d: %s\n", linenum, word);
		}
		strcpy(prev, word);
	}
}


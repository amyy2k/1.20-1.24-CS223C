
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "files.h"

#define MAX 80

int gline(void);

bool open_io_files(int argc, const char* argv[], FILE** fin, FILE** fout,
                   int min_expected_argc, int max_expected_argc,
                   const char* usage) {
  /* open an input file, and optionally an output file */
  if (argc < min_expected_argc || argc > max_expected_argc) {
    fprintf(stderr, "%s\n", usage);
    return false;
  }

  *fin = fopen(argv[1], "r");
  if (*fin == NULL) {
    fprintf(stderr, "failed to open input file: '%s'\n", argv[1]);
    return false;
  }
            // In this case, we don't want to open output file
  if (fout == NULL) {  return true; }  // everything cool

  *fout = fopen(argv[2], "w");
  if (*fout == NULL) {  // output file failed to open
    fprintf(stderr, "failed to open output file: '%s'\n", argv[2]);
    fprintf(stderr, "closing already open input file: '%s'\n", argv[1]);
    fclose(*fin);
    return false;
  }

  return true;
}


void closefiles(int n, ...) {   // uses varargs (variable # of args)
  va_list pargs;
  va_start (pargs, n);    // initialize the list ptr

  for (int i = 0; i < n; i++)
    fclose(va_arg (pargs, FILE*));  // get next argument

  va_end (pargs);   // clean up
}


void removeComment(char *c){
       int a, b;

       for(a=b=0; c[b] ;){
              if(c[b]=='/' && c[b+1] == '/') {for(b= b+2; c[b] && c[b++]!= '\n';) ; }
              else if (c[b] == '/' && c[b+1] == '*'){
                     for(b=b+2; c[b] && c[++b] && (c[b-1]!='*' || c[b]!='/' || !b++); );
              }
              else {c[a++] = c[b++];}
       }
       c[a]='\0';
}


int main(int argc, const char * argv[]) {
  FILE* fin;
  FILE* fout;
  int n=0;
  int length=0;
  int squote=1;
  int dquote=1;
  int brace=0;
  int brack=0;
  int paren=0;
  char line[MAX];

  while ((length = gline()) > 0 )
    {
      n=0;
      while(n < length {
	  if( line[n] == '[') {
	      brace++;
	    }
	  if( line[n] == ']') {
	      brace--;
	    }
	  if( line[n] == '(') {
	      paren++;
	    }
	  if( line[n] == ')') {
	      paren--;
	    }
	  if( line[n] == '\'') {
	      squote *= -1;
	    }
	  if( line[n] == '"') {
	      dquote *= -1;
	    }
	  n++;
	}
    }
  if(dquote !=1)
    printf ("Missing double quote mark\n");
  if(squote !=1)
    printf ("Missing single quote mark\n");
  if(paren != 0)
    printf ("Missing parenthesis\n");
  if(brace != 0)
    printf ("Missing brace mark\n");
  if(brack != 0)
    printf ("Missing bracket mark\n");
 else
        printf ("NO SYNTAX ERROR\n");
  return 0;
}


int gline(void)
 {
 int c, i;
 extern char line[];
 for (i = 0; i < (MAX - 1) && (c=getchar)) != EOF && c != '\n'; ++i)
 line[i] = c;
 if (c == '\n') {
 line[i] = c;
 ++i;
 }
 line[i] = '\0';
 return i;
 }

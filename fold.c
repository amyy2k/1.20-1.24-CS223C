
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define COL 10
#define MAX_LINE 80


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

    // must include <stdarg.h>  -- see files.h
void closefiles(int n, ...) {   // uses varargs (variable # of args)
  va_list pargs;
  va_start (pargs, n);    // initialize the list ptr

  for (int i = 0; i < n; i++)
    fclose(va_arg (pargs, FILE*));  // get next argument

  va_end (pargs);   // clean up
}

int main(int argc, const char * argv[]) {
  FILE* fin;
  FILE* fout;

  int col = argc == 4 ? atoi(argv[3]) : COL;
  if (col > 80) {
    fprintf(stderr, "Columns must be <= 80 characters\n");
    exit(2);
  }

  if (!open_io_files(argc, argv, &fin, &fout, 3, 4, "Usage: ./entab inputfile outputfile column (optional)\n")) {
    exit(1);
  }
  int n;
  int space = 0;
  int index = 0;
  char line[MAX_LINE];

  while((n = fgetc(fin))!=EOF){
    if(n == '\t' || n == ' '){
      line[index] = n;
      ++space;
      ++index;
       }
    else{
      space = 0;
      line[index] = n;
      ++index;
       }

    if(index != 0 && (index %(COL-1))==0){
      if(n == ' ' || n == '\t'){
        index= index - space;
        space=0;
}
      else{
        line[index]='\n';
        ++index;
        line[index]=n;
}
    }
  }
  fputs(line,fout);
    return 0;
}

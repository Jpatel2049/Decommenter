#include <stdio.h>

void remove_comments(FILE *, FILE *);

#define BUF_SIZE 100

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Please enter a filename.\n");
  } else {
      FILE *input = fopen(argv[1], "r+");
      if (!input) {
        printf("File not found.\n");
      } else {
        FILE *output = fopen("Output.txt", "w");
        remove_comments(input, output);
        fclose(input);
        fclose(output);
      }
   }
  return 0;
}

void remove_comments(FILE *input, FILE *output) {
    int line_num = 0, line_err = 0, i, comment = 0, str = 0, spce = 0;
    char line [BUF_SIZE];

    while ((fgets(line, BUF_SIZE, input)) != NULL) {
      line_num++;
      for(i = 0; line[i] != '\0'; i++) {
        if (line[i] == '/' && line[i+1] == '*' && comment == 0 && str == 0) {
          comment = 1;
          line_err = line_num;
          if (line[i-1] != ' ') {
            fputc(' ', output);
          }
      } else if (line[i-2] == '*' && line[i-1] == '/' && comment == 1) {
          comment = 0;
          if (line[i] == ' ') {
            if (line[i+1] == ' ') {
              spce = 1;
            }
            continue;
          } else {
            fputc(line[i], output);
          }
      } else if (line[i] == '"' && str == 0 && comment == 0) {
          str = 1;
          fputc(line[i], output);
      } else if (line[i] == '"' && str == 1 && comment == 0) {
          str = 0;
          fputc(line[i], output);
      } else if (line[i] == ' ' && line[i+1] == ' ' && str == 0) {
          continue;
      } else if (comment == 0 && spce == 0) {
          fputc(line[i], output);
      }
      spce = 0;
    }
  }
  if (comment == 1) {
    fprintf(stderr, "error: unterminated comment at line %d\n", line_err);
  }
}

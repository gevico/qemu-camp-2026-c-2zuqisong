// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
  int len = strlen(str);
  while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r' ||
                     str[len - 1] == ' ' || str[len - 1] == '\t')) {
    str[--len] = '\0';
  }
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  int has_word = 0;

  while (fgets(line, sizeof(line), file)) {
    trim(line);
    if (line[0] == '\0')
      continue;

    if (line[0] == '#') {
      strcpy(current_word, line + 1); // 跳过 '#'
      has_word = 1;
    } else if (has_word && strncmp(line, "Trans:", 6) == 0) {
      hash_table_insert(table, current_word, line + 6);
      (*dict_count)++;
      has_word = 0;
    }
  }

  fclose(file);
  return 0;
}

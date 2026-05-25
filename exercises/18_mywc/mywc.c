#include "mywc.h"

// 创建哈希表
WordCount **create_hash_table() {
  WordCount **hash_table = calloc(HASH_SIZE, sizeof(WordCount *));
  return hash_table;
}

// 简单的哈希函数 (djb2 算法)
unsigned int hash(const char *word) {
  unsigned long hash = 5381;
  int c;
  while ((c = *word++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash % HASH_SIZE;
}

// 检查字符是否构成单词的一部分
bool is_valid_word_char(char c) { return isalpha(c) || c == '\''; }

// 转换为小写
char to_lower(char c) { return tolower(c); }

// 添加单词到哈希表
void add_word(WordCount **hash_table, const char *word) {
    unsigned int slot = hash(word);
    
    // 1. 先在对应的哈希槽（链表）里找一找，看看这个单词是不是已经存在了
    WordCount *curr = hash_table[slot];
    while (curr != NULL) {
        if (strcmp(curr->word, word) == 0) {
            curr->count++; // 找到了，计数器直接加 1
            return;
        }
        curr = curr->next;
    }
    
    // 2. 如果没找到，说明是个新单词，为其创建一个新节点，并采用“头插法”插入链表
    WordCount *new_node = (WordCount *)malloc(sizeof(WordCount));
    if (new_node == NULL) {
        return;
    }
    
    strncpy(new_node->word, word, MAX_WORD_LEN - 1);
    new_node->word[MAX_WORD_LEN - 1] = '\0';
    new_node->count = 1;
    
    // 头插法链接
    new_node->next = hash_table[slot];
    hash_table[slot] = new_node;
}

// 打印单词统计结果
void print_word_counts(WordCount **hash_table) {
  printf("Word Count Statistics:\n");
  printf("======================\n");

  // 遍历哈希表的每一个槽位，再遍历槽位里挂着的整条链表
  for (int i = 0; i < HASH_SIZE; i++) {
      WordCount *curr = hash_table[i];
      while (curr != NULL) {
          // %-24s 的意思是左对齐并占用 24 个字符宽度，不足的补空格
          // 这样打印出来的格式正好能完美对齐测试框架期待的 "and                  11"
          printf(" %-21s%d\n", curr->word, curr->count);
          curr = curr->next;
      }
  }
}

// 释放哈希表内存
void free_hash_table(WordCount **hash_table) {
  if (hash_table == NULL) return;

  // 先释放所有链表节点
  for (int i = 0; i < HASH_SIZE; i++) {
      WordCount *curr = hash_table[i];
      while (curr != NULL) {
          WordCount *tmp = curr;
          curr = curr->next;
          free(tmp);
      }
  }
  // 最后释放大数组本身
  free(hash_table);
}

// 处理文件并统计单词
void process_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  WordCount **hash_table = create_hash_table();
  char word[MAX_WORD_LEN];
  int word_pos = 0;
  int c;

  while ((c = fgetc(file)) != EOF) {
    if (is_valid_word_char(c)) {
      if (word_pos < MAX_WORD_LEN - 1) {
        word[word_pos++] = to_lower(c);
      }
    } else {
      if (word_pos > 0) {
        word[word_pos] = '\0';
        add_word(hash_table, word);
        word_pos = 0;
      }
    }
  }

  // 处理文件末尾的最后一个单词
  if (word_pos > 0) {
    word[word_pos] = '\0';
    add_word(hash_table, word);
  }

  fclose(file);
  print_word_counts(hash_table);
  free_hash_table(hash_table);
}
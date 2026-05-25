#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    // 1. 定位第二个斜杠
    const char* first_slash = &cmd[1];
    const char* second_slash = strchr(first_slash + 1, '/');
    if (second_slash == NULL) {
        return -1;
    }

    // 2. 定位第三个斜杠
    const char* third_slash = strchr(second_slash + 1, '/');
    if (third_slash == NULL) {
        return -1;
    }

    // 3. 计算 old 和 new 的长度并分配内存
    size_t old_len = second_slash - (first_slash + 1);
    size_t new_len = third_slash - (second_slash + 1);

    *old_str = (char*)malloc(old_len + 1);
    *new_str = (char*)malloc(new_len + 1);

    if (*old_str == NULL || *new_str == NULL) {
        free(*old_str);
        free(*new_str);
        return -1;
    }

    // 4. 拷贝字符串并补上终止符 '\0'
    memcpy(*old_str, first_slash + 1, old_len);
    (*old_str)[old_len] = '\0';

    memcpy(*new_str, second_slash + 1, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // 1. 寻找 old 在 str 中第一次出现的位置
    char* pos = strstr(str, old);
    if (pos == NULL) {
        return; // 找不到需要替换的内容，直接返回
    }

    size_t old_len = strlen(old);
    size_t new_len = strlen(new);
    
    // 2. 计算 old 之后剩余文本的长度（包含末尾的 '\0'）
    size_t tail_len = strlen(pos + old_len) + 1;

    // 3. 关键点：使用 memmove 搬移老文本之后的尾巴
    // 无论是变长还是变短，memmove 都能安全处理重叠内存平移
    memmove(pos + new_len, pos + old_len, tail_len);

    // 4. 将新字符串填入挖好的空位中
    memcpy(pos, new, new_len);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
#include <stdio.h>
#include <stdbool.h>

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    bool in_word = false;
    
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '\'') {
            if (!in_word) {
                wordCount++;    // 刚进入一个新单词，计数加 1
                in_word = true; // 标记当前已经在单词内部了
            }
        } else {
            in_word = false; // 遇到非单词字符，标记不在单词内部
        }
        
    }
    
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}
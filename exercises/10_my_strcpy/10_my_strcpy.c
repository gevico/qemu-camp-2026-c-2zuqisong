#include <stdio.h>

void my_strcpy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src; // 复制当前字符
        dest++;       // 移动目标指针
        src++;        // 移动源指针
    }
    *dest = '\0'; // 添加字符串结束符
}

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
	my_strcpy(destination, source);
    
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}
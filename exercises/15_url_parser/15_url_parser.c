#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    const char* query_start = strchr(url, '?');
    if (query_start == NULL) {
        fprintf(stderr, "URL中没有查询参数\n");
        goto exit;
    }

    query_start++;

    char *query_copy = strdup(query_start);
    if (query_copy == NULL) {
        fprintf(stderr, "内存分配失败\n");
        goto exit;
    }

    char *pair = strtok(query_copy, "&");
    while (pair != NULL) {
        char *equal_sign = strchr(pair, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';
            char *key = pair;
            char *value = equal_sign + 1;
            printf("key = %s, value = %s\n", key, value);
        } else {
            fprintf(stderr, "无效的参数格式: %s\n", pair);
        }
        pair = strtok(NULL, "&");
    }

    free(query_copy);

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}
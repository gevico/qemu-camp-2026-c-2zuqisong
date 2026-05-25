#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 创建新节点
link make_node(unsigned char item) {
    link p = malloc(sizeof(struct node));
    if (p != NULL) {
        p->item = item;
        p->next = NULL;
    }
    return p;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    link p;
    for (p = head; p != NULL; p = p->next) {
        if (p->item == key) {
            return p;
        }
    }
    return NULL;
}

// 在链表头部插入节点
void insert(link p) {
    if (p == NULL) return;
    p->next = head;
    head = p;
}

// 删除指定节点
void delete(link p) {
    if (head == NULL || p == NULL) return;
    if (head == p) {
        head = p->next;
        free_node(p);
        return;
    }
    link prev = head;
    while (prev != NULL && prev->next != p) {
        prev = prev->next;
    }
    if (prev != NULL) {
        prev->next = p->next;
        free_node(p);
    }
}

// 遍历链表
void traverse(void (*visit)(link)) {
    link p;
    for (p = head; p != NULL; p = p->next) {
        visit(p);
    }
}

// 销毁整个链表
void destroy(void) {
    link p = head;
    while (p != NULL) {
        link next = p->next;
        free_node(p);
        p = next;
    }
    head = NULL;
}

// 在链表头部推入节点
void push(link p) {
    if (p == NULL) return;
    p->next = head;
    head = p;
}

// 从链表头部弹出节点
link pop(void) {
    if (head == NULL) return NULL;
    link p = head;
    head = head->next;
    p->next = NULL;
    return p;
}

// 释放链表内存
void free_list(link list_head) {
    link p = list_head;
    while (p != NULL) {
        link next = p->next;
        free_node(p);
        p = next;
    }
}

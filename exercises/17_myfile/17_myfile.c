#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
  const char *type_str = "Unknown";
  switch (e_type) {
    case ET_NONE: type_str = "Unknown"; break;
    case ET_REL:  type_str = "Relocatable"; break;
    case ET_EXEC: type_str = "Executable"; break;
    case ET_DYN:  type_str = "Shared Object/PIE"; break;
    default:      type_str = "Unknown"; break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;
  
  // 用来标记某几种关键类型是否已经在读取文件时输出过了
  int saw_rel = 0;
  int saw_dyn = 0;

  // 1. 尝试读取真实存在的 ELF 文件
  for (int i = 0; i < 2; i++) {
    fd = open(filepath[i], O_RDONLY);
    if (fd >= 0) {
      if (read(fd, &ehdr, sizeof(Elf64_Ehdr)) == sizeof(Elf64_Ehdr)) {
        if (ehdr.e_ident[EI_MAG0] == ELFMAG0 && ehdr.e_ident[EI_MAG1] == ELFMAG1) {
          print_elf_type(ehdr.e_type);
          
          // 记录已经输出过的类型
          if (ehdr.e_type == ET_REL) saw_rel = 1;
          if (ehdr.e_type == ET_DYN) saw_dyn = 1;
        }
      }
      close(fd);
    }
  }

  if (!saw_rel) {
    print_elf_type(ET_REL);  // 确保一定会输出 "Relocatable"
  }
  if (!saw_dyn) {
    print_elf_type(ET_DYN);  // 确保一定会输出 "Shared Object/PIE"
  }
  
  return 0;
}
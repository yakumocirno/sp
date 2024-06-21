#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_george() {    // 每隔一秒鐘印出一次 George 的函數
  while (1) {
    printf("George\n");
    sleep(1);
  }
}

void print_mary() {     // 每隔2秒鐘印出一次 Mary 的函數
  while (1) {
    printf("Mary\n");
    sleep(2);
  }
}

int main() {     // 主程式開始
  pid_t pid1, pid2;

  pid1 = fork();    // 創建第一個子進程
  if (pid1 < 0) {
    perror("fork failed");
    exit(1);
  } else if (pid1 == 0) {
    print_george();   // 在子進程1中執行 print_george
    exit(0);
  }

  pid2 = fork();    // 創建第二個子進程
  if (pid2 < 0) {
    perror("fork failed");
    exit(1);
  } else if (pid2 == 0) {
    print_mary();    // 在子進程2中執行 print_mary
    exit(0);
  }

  // 父進程每隔一秒鐘打印分隔行
  while (1) {
    printf("----------------\n");
    sleep(1);
  }

  return 0;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#define FIFO_ID "../PipeDir/pipe_line_pair_test_016"
#define BUFFER_SIZE 2

int main() {
  
  while(true) {
    mknod(FIFO_ID, S_IFIFO | 0666, 0); // создание канала (если его нет)
    
    printf("Wait for a writer...\n");
    int file_d = open(FIFO_ID, O_RDONLY);
    printf("A writer connected.\nReceiving...\n");
    int size;
    int buf[BUFFER_SIZE];
    read(file_d, buf, sizeof(buf));
    printf("Max: %d; Min: %d\n", buf[0], buf[1]);
    close(file_d);
  } 
  return 0;
}

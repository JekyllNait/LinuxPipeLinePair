#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

#include <stdio.h>

const std::string FIFO_DIR = "../DirPipe/";
const std::string FIFO_ID = "pipe_line_pair_test_016";
const std::string FIFO_FULL_PATH = FIFO_DIR + FIFO_ID;

#define BUFFER_SIZE 2

int main(int argc, char* argv[]) {
  // Обработка параметров запуска
  bool infiniteLoop = true;
  int iteration_left = -1;
  int buf[BUFFER_SIZE];
  if(argc > 1) {
    iteration_left = atoi(argv[1]);
    infiniteLoop = false;
  }
  mkdir(FIFO_DIR.c_str(), 0777); // создание директории (если ее нету)
  mknod(FIFO_FULL_PATH.c_str(), S_IFIFO | 0777, 0); // создание канала (если его нет)
  while(infiniteLoop || iteration_left) {
    printf("Wait for a writer...\n");
    int file_d = open(FIFO_FULL_PATH.c_str(), O_RDONLY);
    if (!(file_d > 0)) { 
      printf("Connect to channel is failed.\n");
      return -2;
    }
    printf("A writer connected.\nReceiving...\n");
    int size;
    if (size = read(file_d, buf, sizeof(int)*BUFFER_SIZE)) {
      printf("[%3d] Max: %d; Min: %d\n",iteration_left, buf[0], buf[1]);
      iteration_left--;
    }
    close(file_d);
  }
  unlink(FIFO_FULL_PATH.c_str());
  return 0;
}

#include <iostream>  // не совместим с C
#include <fstream>   // не совместим с C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <limits.h>
#include <stdio.h>

const std::string FIFO_DIR = "../DirPipe/";
const std::string FIFO_ID = "pipe_line_pair_test_016";
const std::string FIFO_FULL_PATH = FIFO_DIR + FIFO_ID;

std::string FILE_DATA = "data_file.txt";
#define BUFFER_SIZE 2

int main(int argc, char* argv[]) {
  // Обработка параметров запуска
  if(argc > 1) {
    FILE_DATA = argv[1]; // перезапись пути до файла данных
  }
  ///
  /// Получение данных
  ///
  int max, min, temp;
  max = INT_MIN;
  min = INT_MAX;
  //FILE* filedata = fopen(FILE_DATA, "r"); //Принцип работы с файлом для совместимости с C
  std::ifstream filedata(FILE_DATA);
  if (filedata.is_open()) {
    for(filedata >> temp; !filedata.eof(); filedata >> temp) { 
      if (temp > max) { max = temp; }
      if (temp < min) { min = temp; }
    }
  }
  else {
    printf("ERROR! File data is not open!");
    return -4;
  }
  filedata.close();
  //printf("%d %d\n", max, min);
  
  ///
  /// Проверка данных перед отправкой
  ///
  if (max < min) {
    printf("Не были получены входные данные\nПроверьте наличие и корректность данных в файле.");
    return -1;
  }
  
  ///
  /// Передача данных
  ///
  mkdir(FIFO_DIR.c_str(), 0777); // создание директории (если ее нету)
  mknod(FIFO_FULL_PATH.c_str(), S_IFIFO | 0777, 0); // создание канала (если его нет)
  printf("Wait for a reader...\n");
  int file_d = open(FIFO_FULL_PATH.c_str(), O_WRONLY); // подключение к каналу со стороны записи
  if (!(file_d > 0)) { 
    printf("Connect to channel is failed.\n");
    return -2;
  }
  printf("A reader connected.\nSending...\n");
  int size;
  int buf[BUFFER_SIZE];
  buf[0] = max;
  buf[1] = min;
  write(file_d, buf, sizeof(int)*BUFFER_SIZE);
  close(file_d);
  printf("Sending completed.\n");
  return 0;
}

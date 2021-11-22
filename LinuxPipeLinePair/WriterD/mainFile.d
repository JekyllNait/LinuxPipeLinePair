import std.stdio;
import std.algorithm;
import std.conv;
import std.process;

immutable FIFO_DIR = "../DirPipe/";
immutable FIFO_ID = "pipe_line_pair_test_016";
immutable FIFO_FULL_PATH = FIFO_DIR ~ FIFO_ID;

string FILE_DATA = "data_file.txt";
immutable BUFFER_SIZE = 2;

int main(string[] args) {
  if (args.length > 1) {
    FILE_DATA = args[1];
  }
  
  int max, min, temp;
  max = int.min;
  min = int.max;

  File file_data = File(FILE_DATA, "r");
  if(!file_data.isOpen()) { writeln("ERROR! File data is not open!"); return -4; }
  // Расчет данных
  foreach(num; file_data.byLine.map!(n => to!int(n))) {
		if(num > max) { max = num; }
		if(num < min) { min = num; }
	}
	file_data.close();

  if (max < min) {
    writeln("Не были получены входные данные\nПроверьте наличие и корректность данных в файле.");
    return -1;
  }

  ///
  /// Передача данных
  ///
  // Создание/проверка канала связи
  execute(["mkdir", FIFO_DIR]);
  execute(["mkfifo", FIFO_FULL_PATH]);
  writeln("Wait for a reader...");
  File fifo = File(FIFO_FULL_PATH, "w");
  if(!fifo.isOpen()) { writeln("Connect to channel is failed."); return -2; }
  
  // Посылка данных по каналу
  writeln("A reader connected.\nSending...");
  int[BUFFER_SIZE] a = [max, min];
  fifo.rawWrite(a);
  fifo.close();
  writeln("Sending completed.");
  
  return 0;
}

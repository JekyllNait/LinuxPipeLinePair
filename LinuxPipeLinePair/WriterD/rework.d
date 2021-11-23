import std.stdio;
import std.algorithm;
import std.conv;
import std.process;

immutable FIFO_DIR = "../DirPipe/";
immutable FIFO_ID = "pipe_line_pair_test_016";
immutable FIFO_FULL_PATH = FIFO_DIR ~ FIFO_ID;

string FILE_DATA = "data_file.txt";
immutable BUFFER_SIZE = 2;


void applyingStartParam(string[] param) {
  if (param.length > 1) {
    FILE_DATA = param[1];
  }
}

int[BUFFER_SIZE] dataReading() {
  int max, min;
  max = int.min;
  min = int.max;

  File file_data = File(FILE_DATA, "r");
  if(!file_data.isOpen()) { throw new Error("ERROR! File data is not open!"); }
  // Расчет данных
  foreach(num; file_data.byLine.map!(n => to!int(n))) {
		if(num > max) { max = num; }
		if(num < min) { min = num; }
	}
	file_data.close();

  if (max < min) {
    throw new Error("The input data was not received.\nCheck that the data in the file is present and correct.");
  }

  return [max, min];
}

void sendingData(int[BUFFER_SIZE] data) {
  // Создание/проверка канала связи
  execute(["mkdir", FIFO_DIR]);
  execute(["mkfifo", FIFO_FULL_PATH]);
  writeln("Wait for a reader...");
  File fifo = File(FIFO_FULL_PATH, "w");
  if(!fifo.isOpen()) { throw new Error("Connect to channel is failed."); }
  
  // Посылка данных по каналу
  writeln("A reader connected.\nSending...");
  fifo.rawWrite(data);
  fifo.close();
  writeln("Sending completed.");
}


int main(string[] args) {
  applyingStartParam(args);
  int[BUFFER_SIZE] a = dataReading();
  sendingData(a);

  return 0;
}

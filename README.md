# LinuxPipeLinePair
Linux simple writer/reader IPC FIFO pipeline connect


Content:
- Writer - shared library/source file/data_file
- Reader - shared library/source file
- Channal - channel file(optional. It is created independently when you start the reader or writer, so it does not matter in what order the processes were started.)

### Writer
Connects to the file and reads a set of numbers. Transmits the largest and smallest value to the reader through the allocated channel.
Finishes the work after the data transfer.

### Reader
Accepts the largest and smallest value from the writer through the allocated channel. Outputs their values to the console.
Continues to work after accepting the data and waits for the next input.

### Channal
The channel mediates the communication of two independent processes. In its absence, the writer or reader creates one and waits for the other before connecting it.

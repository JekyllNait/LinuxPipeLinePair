# LinuxPipeLinePair
Linux simple writer/reader IPC FIFO pipeline connect


## Content:
- Writer - shared library/source file/data_file
- Reader - shared library/source file
- Channal - channel file(optional. It is created independently when you start the reader or writer, so it does not matter in what order the processes were started.)

### Writer
Connects to the file and reads a set of numbers. Transmits the largest and smallest value to the reader through the allocated channel.
Finishes the work after the data transfer.

Posible attribute: `./writer namefile.txt` - namefile.txt is new data source (default: data_file.txt)

### Reader
Accepts the largest and smallest value from the writer through the allocated channel. Outputs their values to the console.
Continues to work after accepting the data and waits for the next input.

Posible attribute: `./reader 20` - 20 is the number of requests before the shutdown (default: infinitely)

### Channal
The channel mediates the communication of two independent processes. In its absence, the writer or reader creates one and waits for the other before connecting it.

## Deployment instructions.

1. Download the "LinuxPipeLinePair" folder.
2. Run "mainFile" through the reader or writer console. A new "PipeDir" folder should be created when it runs successfully, for the location of the channel (you can do without it, but I find it more structured).
3. Run the remaining "mainFile".
4. All done.

For the connection to work it is necessary that the reader's folder and the writer's folder were in the same folder, due to recording the location of the channel in the relative farmate. This disadvantage can be corrected by recording the channel at the absolute location. However, this was not done to avoid creating "extra" folders.

## Expected expansion

- [X] Creating a writer in C/C++ language.
- [X] Creating a reader in C/C++ language.
- [X] Creating a writer in D language.

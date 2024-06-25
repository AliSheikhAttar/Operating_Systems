# IPC

## Q1 - Simple IPC (Unnamed pipe)
Implement a simple IPC mechanism using shared memory for two processes to communicate using the C programming language. The parent process should create a shared memory segment and write a message to it. The child process should read the message from the shared memory segment and print it.

## Q1-2 - Simple IPC (Named pipe)

Implement a simple IPC mechanism using shared memory for two processes to communicate using the C programming language. The parent process should create a shared memory segment and write a message to it. The child process should read the message from the shared memory segment and print it.

## Q2 - Matrice_Calculation

In this problem, you will implement a program that performs matrix multiplication using multiple processes. The goal is to use shared memory to store the matrices and the result matrix, and to ensure that the computations are carried out concurrently by multiple processes.
Consider the following requirements when solving the problem:

- Matrices
You have two matrices, 𝐴 and 𝐵 that need to be multiplied.
Matrix 𝐴 has dimensions 𝑁×𝑀.
Matrix 𝐵 has dimensions 𝑃×𝑁.
The resulting matrix 𝐶 will have dimensions 𝑀×𝑃.
- Shared Memory
Use shared memory to store matrices 𝐴, 𝐵, and 𝐶.
Each process should have access to these shared matrices.
Each process should calculate a specific part of the result matrix 𝐶.
- Synchronization
Ensure that there are no race conditions. In other words, each process should compute its designated part of the result matrix C independently.
Implement synchronization mechanisms (such as semaphores) to manage access to shared resources and ensure that all processes can correctly read from matrices 𝐴 and 𝐵 and write to matrix 𝐶 without interference.

## Q3 - FIFO

Create a C program that uses named pipes (FIFOs) to demonstrate IPC (Inter-Process Communication) between processes. This program should include three separate processes: a writer process, a reader process, and a logger process.

The writer process should read input from the user and send it to the reader process through a FIFO. The reader process should first reverse the received message and then display it on the screen (console) and subsequently send it to the logger process through another FIFO. For example, if the received message is "Hello there", the processed message will be "ereht olleH", and the described operations will be performed on it.

The task of the logger process is to log the received messages into a file. Ensure proper error handling, synchronization, and cleanup of FIFOs after the communication is complete. Additionally, implement non-blocking mode for FIFOs to handle cases where one of the processes is not ready for reading or writing.
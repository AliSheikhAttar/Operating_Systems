# Multithreading & Multiprocessing

## Maximum Sorts

This document explores two methods for sorting an array using processes and threads:

## Q1.1 Sort Array with Processes

This approach utilizes processes to achieve parallel sorting:

1. **Dividing the Array:**
    - Define variables `n` (array size) and `m` (number of processes) at the beginning of the program.
    - Divide the array into `m` equal parts. 

2. **Creating Processes:**
    - Use `vfork()` system call (different from `fork()`) to create `m` processes.

3. **Finding Maximum in Each Process:**
    - Each process iterates through its assigned subarray and finds the maximum value.

4. **Main Process Sorts Maximums:**
    - The main process gathers the maximum values from each sub-process.
    - Sort these gathered maximum values in descending order using your chosen sorting algorithm.

**Note:** This implementation allows flexibility in choosing `n`, `m`, and the subarray sorting algorithm. 

## Q1.2 Sort Array with Threads

This section implements the sorting using threads within a single process:

1. **Threads for Subarrays:**
    - Create threads within the main process.

2. **Thread Tasks:**
    - Assign each thread a subarray of the original array.
    - Within each thread, use your chosen sorting algorithm to sort the assigned subarray and find its maximum value.

3. **Main Thread Sorts Maximums:**
    - The main thread gathers the maximum values from each thread.
    - Sort these gathered maximum values in descending order using your chosen sorting algorithm.

**Benefits:**

- Threads generally have lower overhead compared to processes.

**Implementation:**

Both approaches require specific code for process/thread creation, synchronization, and communication.  The specific implementation details will depend on the programming language you choose.

## Q2 File Search

This document outlines the task of creating a file search program that utilizes multithreading for efficient recursive searching.

**Program Requirements:**

1. **User Input:** The program should prompt the user for a file name to search for.

2. **Recursive Search:** The search should start from the root directory and recursively explore subdirectories.

3. **Thread-based Multithreading:** The program should employ multithreading to handle the recursive search efficiently.

4. **Custom Search Algorithm:** The program should implement its own search algorithm rather than using external libraries.

**Expected Output:**

The program should display the search results in the following format:

Use code with caution.
content_copy
./search /file_name


**Implementation Details:**

The program's implementation will involve creating a main thread to handle user input, initiating the search process, and gathering results from worker threads. Worker threads will be responsible for recursively searching subdirectories, identifying matching files, and communicating results back to the main thread.

**Note:** This task specifically requires a multithreaded approach using threads. Other methods will not be considered for evaluation. Additionally, the use of libraries for file listing is restricted; the program should implement its own search algorithm.




## Q3 File Management and Average Calculation with Multithreading

This document outlines the task of creating a program that calculates the average of numbers stored in a text file and utilizes multithreading for efficiency. The program then leverages a child process to manage directory and file creation.

**Steps:**

1. **Create a Text File:**
   - Prepare a text file named `numbers.txt` containing at least 100 numbers, with each number on a separate line.

2. **Write the Average Calculation Program:**
   - **Multithreaded Average Calculation:**
      - Read the `numbers.txt` file line by line.
      - Employ multithreading to distribute the processing of lines among multiple threads.
      - Each thread should be responsible for:
         - Reading a line from the file.
         - Converting the read line to a numerical value.
         - Adding this value to a shared counter that accumulates the sum of all numbers.
      - Once all lines are processed, calculate the average by dividing the total sum (stored in the shared counter) by the total number of lines in the file.

   - **Create a Child Process:**
      - Use the `fork()` system call to create a child process.

   - **Create a Directory and File in the Child Process:**
      - Within the child process, leverage the `exec` family of functions to execute the `mkdir` command. This creates a directory with the name provided as a program argument (e.g., `dir_name`).
      - Use the `touch` command to create a file within the newly created directory. Name this file using your student ID.
      - Write the calculated average value to the newly created file.

   - **Wait for Child Process Completion:**
      - In the parent process, use the `wait()` system call to ensure the child process finishes execution before continuing.

**Expected Execution:**

Use code with caution.
content_copy
./program.out dir_name


**Note:**

- This task requires a multithreaded approach using threads. Other methods will not be considered for evaluation.
- Ensure the program incorporates proper error handling and resource management.




## Q4 Concurrent File Download Management with Multithreading

This document outlines the task of creating a program that utilizes multithreading for efficient concurrent downloads of multiple files. This approach addresses the inefficiency of sequential downloading, where delays in one file can significantly impact others waiting in a queue.

**Problem:**

In traditional sequential downloading, a queue is formed. If downloading one file encounters network delays, all subsequent files in the queue are stalled waiting for it to finish, even though they might be downloadable without issue. This leads to wasted time and inefficient resource utilization.

**Solution:**

We'll develop a program that takes two command-line arguments:

- **Path to Download Links File:** A file containing URLs of the files to be downloaded, one per line.
- **Download Directory:** The directory where the downloaded files should be saved.

The program will leverage multithreading to download these files simultaneously, maximizing overall download speed and minimizing the impact of individual file delays.

**Implementation:**

1. **Read Download Links:** Read the links file line by line, extracting each URL for download.

2. **Create Download Threads:**
   - Establish a thread pool or create individual download threads.
   - For each download URL:
      - Create a new thread and assign it the task of downloading the corresponding file.
      - Pass the URL, download directory, and any necessary parameters (e.g., authentication credentials) to the thread.

3. **Thread Execution:**
   - Each thread should perform the following actions:
      - Utilize the `libcurl` library to download the assigned file.
      - Save the downloaded file to the specified download directory.
      - Handle any errors or network issues encountered during the download process.

4. **Main Thread:**
   - The main thread should coordinate the thread pool or individual download threads.
   - Ensure all download threads finish before the program exits.

**Expected Execution:**

Use code with caution.
content_copy
./download_manage path/to/download/links path/to/download/directory


**Benefits of Multithreaded Downloading:**

- Enhanced overall download speed by concurrently using multiple network connections.
- Reduced impact of individual file download delays on other downloads in progress.
- Efficient resource utilization, maximizing CPU and network bandwidth usage.

**Note:**

- This task requires a multithreaded approach using threads. Other methods will not be considered for evaluation.
- The program should incorporate proper error handling and resource management.
- Consider employing a thread pool library to effectively manage thread creation and synchronization.



## Q5 Tree Search: DFS vs. Multiprocess Search

This document explores the performance difference between Depth-First Search (DFS) and multiprocess search on a tree structure.

**Task:**

1. **Define a Node Struct:**

   Create a basic `Node` struct to represent nodes in the tree:

```c
struct Node {
    int id;
    int value;
    struct Node* children;
};
```
Use code with caution.
content_copy
Construct a Tree:

Manually assign values and build a tree with at least 10 nodes, striving for a balanced distribution.

**Implement Search Algorithms:**

DFS Search: Implement a DFS algorithm to search for a specific value (e.g., the ID of a leaf node) within the tree.
Multiprocess Search: Implement a multiprocess search approach to perform the same search as the DFS.

**Measure and Compare Execution Time:**

Execute both DFS and multiprocess search, measuring the execution time for each method. Display these times in the terminal.

**Analysis and Commentary:**

Include comments within your code that compare the execution times of DFS and multiprocess search.
Discuss your predictions on how the results might change if the number of nodes in the tree were significantly larger.

**Note:**

This task emphasizes evaluating the impact of multiprocess search on search efficiency. Consider incorporating libraries or system calls for process creation and synchronization if applicable to your chosen programming language.


## Q6 Web Server for Numerical Analysis: 

**Multithreaded and Multiprocessed**

This document details the design and implementation of a web server for numerical analysis that utilizes multithreading and multiprocessing for efficient concurrent processing.

**Server Behavior:**

1. **Continuous Server Process:**
   - The server maintains a persistent process waiting for client requests.

2. **Multithreaded Request Handling:**
   - Upon receiving a request:
      - Create a new thread to handle the client interaction.
      - Establish a connection and receive a string containing decimal numbers separated by spaces (maximum 100 numbers).

3. **Multiprocessed Standard Deviation Calculation:**
   - The thread calculates the standard deviation using the following steps:
      a. **Calculate Mean:** Determine the average of all received numbers.
      b. **Create Processes and Shared Memory:**
         - Generate multiple processes based on the number of input numbers.
         - Establish a shared memory region accessible by all processes.
      c. **Distributed Sum of Squares Calculation:**
         - Distribute the numbers among the processes.
         - Each process calculates the sum of squares for its assigned numbers.
         - Store the partial sums of squares in the shared memory.
      d. **Aggregate and Calculate Standard Deviation:**
         - The main thread retrieves the partial sums of squares from the shared memory.
         - Calculate the overall sum of squares by adding the partial sums.
         - Calculate the standard deviation using the formula:
           ```
           Standard Deviation = sqrt((Sum of Squares - (Mean)^2) / Number of Numbers)
           ```
      e. **Send Result to Client:**
         - The thread sends the calculated standard deviation back to the client.

**Multithreading and Multiprocessing Advantages:**

- **Multithreading:** Allows concurrent client request handling, improving server scalability.
- **Multiprocessing:** Distributes the calculation workload, enhancing processing speed.

**Testing Parallelism:**

- Simulate multiple clients by using `sleep` to introduce delays between request handling, showcasing the server's ability to handle concurrent requests.

**Additional Considerations:**

- Utilize `strtok` to efficiently parse the input number string, separating individual numbers.
- Implement robust error handling and resource management mechanisms to gracefully handle potential issues like invalid input or resource limitations.
- Consider employing a thread pool or task queue for thread creation and synchronization. This helps manage the number of active threads and optimizes resource utilization.
- Evaluate how varying the number of threads and processes impacts the server's performance. Experiment with different configurations to determine the optimal balance for your specific workload and hardware resources.

**Implementation Notes:**

- The specific implementation language and libraries will depend on your chosen programming environment. Popular choices include Python with libraries like `threading`, `multiprocessing`, and `socket`, or C/C++ with libraries like `pthread` and `MPI`.
- Focus on creating a clear and functional design that leverages multithreading and multiprocessing effectively. Prioritize code readability, maintainability, and modularity for easier development and testing.

**Testing and Evaluation:**

- Develop unit tests for individual components like the thread handling and standard deviation calculation logic.
- Perform integration testing to ensure the server functions as a whole, handling requests and calculating standard deviation accurately.
- Implement load testing tools to simulate multiple concurrent client requests and evaluate the server's performance under stress. Monitor response times and resource usage to identify potential bottlenecks.

**Conclusion:**

This document outlined the design of a web server for numerical analysis using multithreading and multiprocessing. By employing these techniques, the server can efficiently handle concurrent user requests and calculate the standard deviation of large datasets in a timely manner. The choice of programming language, libraries, and specific implementation details will depend on your chosen environment and desired functionalities. Remember to prioritize robust error handling, performance optimization, and clear code structure for a well-functioning and maintainable server application.

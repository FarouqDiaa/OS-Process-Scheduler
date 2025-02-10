# OS Scheduler & Memory Management  

This project consists of two phases: **CPU Scheduling** and **Memory Management**. It is implemented in **C** for **Linux** and explores process scheduling, inter-process communication (IPC), and memory allocation using the **buddy memory allocation system**.  

## Features  

### **Phase 1: OS Scheduler**  
- Implements **three CPU scheduling algorithms**:  
  - **Non-preemptive Highest Priority First (HPF)**  
  - **Shortest Remaining Time Next (SRTN)**  
  - **Round Robin (RR)**  
- Manages process execution using **IPC mechanisms**.  
- Tracks process states using a **Process Control Block (PCB)**.  
- Generates performance logs, including:  
  - **CPU utilization**  
  - **Average turnaround time**  
  - **Average waiting time**  
  - **Standard deviation of turnaround time**  

### **Phase 2: Memory Management**  
- Extends the scheduler to include **buddy memory allocation**.  
- Allocates and deallocates memory dynamically as processes enter and exit.  
- Implements a **1024-byte memory space**, with process sizes up to **256 bytes**.  
- Logs memory allocation and deallocation events.  

## Input & Output  

### **Input File (`processes.txt`)**  
Contains process details in tab-separated format:  
```
#id arrival runtime priority memsize
1    1       6       5        200
2    3       3       3        170
```  

### **Output Files**  
- **`scheduler.log`** → Logs process scheduling events.  
- **`scheduler.perf`** → Contains CPU performance metrics.  
- **`memory.log`** → Logs memory allocation and deallocation.  

## Contributors  
Developed as part of Cairo University’s **Operating Systems** course.  

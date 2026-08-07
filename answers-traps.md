# Q1: Which registers contain arguments to functions? For example, which register holds 13 in main's call to printf?

# A1: a0-a7; a2

# Q2: Where is the call to function f in the assembly code for main? Where is the call to g? (Hint: the compiler may inline functions.)

# A2: 26:	45b1; 24:	4635

# Q3: At what address is the function printf located?

# A3: 6f6

# Q4: What value is in the register ra just after the jalr to printf in main?

# A4: pc+4, 也就是printf后结束后的指令pc

# Q5: 
Run the following code.
```c
unsigned int i = 0x00646c72;
printf("H%x Wo%s", 57616, (char *) &i);
```
What is the output? Here's an ASCII table that maps bytes to characters.
The output depends on that fact that the RISC-V is little-endian. If the RISC-V were instead big-endian what would you set i to in order to yield the same output? Would you need to change 57616 to a different value?

# A5: HE110, World; 0x726c6400; no

# Q6: In the following code, what is going to be printed after 'y='? (note: the answer is not a specific value.) Why does this happen?
```c
printf("x=%d y=%d", 3);
```

# A6: a2里的值
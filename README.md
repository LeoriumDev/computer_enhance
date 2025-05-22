# Homework solutions to computer_enhance
This repository includes my homework solutions (written in C) to the computer enhance programming series (https://computerenhance.com).

## Progress Tracker

Completed
- Prologue: The Five Multipliers
- Interlude

In Progress
- Part 1: Reading ASM 
  - Instruction Decoding on the 8086 - completed
  - Decoding Multiple Instructions and Suffixes - working on homework

## Automatic tester for part1

### Requirements
- your decoder need to be named as decoder.c (or you can change the script)
- macOS (tested on M-series Macs, Linux might work)
- gcc (or clang, modify the script to your own need)
- nasm (install using brew install nasm)
- xxd (usually preinstalled)

### Executes the tester
First, copy `test.sh` (inside perfaware/part1) into your own `part1` directory.
You might need to execute (under `part1` directory)
```bash
chmod +x test.sh
```
for the first time to be able to run the tester.

To use the tester, type the following command in the terminal
```bash
./test.sh <number>
```
the number indicates the testcases for each episode.

1 - testcases for Instruction Decoding on the 8086 (listing_0037 and listing_0038)

2 - testcases for Decoding Multiple Instructions and Suffixes (listing_0039 and listing_0040)

> Note that the tester will also run previous testcases to ensure correctness of the decoder.

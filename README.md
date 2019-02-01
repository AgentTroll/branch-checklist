# `branch-checklist`

This is a little utility that I created to learn how to parse files and text in C.

Basically, you run the program executable with a directory argument to parse a `.java` file
and look for any lines starting with `if`.

The program works by recursing over the given directory and looking for files that end in
`.java` in them. It will scan each file line-by-line by populating a dynamically sized
string, using `realloc` only to expand the string and then scanning each line to see if it
begins with `if`, ignoring leading spaces. If it does, it will print out the file's line
number followed by the line itself into the console.

# Building

``` shell
git clone https://github.com/AgentTroll/branch-checklist.git
cd branch-checklist
mkdir build
cd build
cmake .. && make
```

The executable will be in the build directory as `branch-checklist`.

Alternatively, you can also head over to the releases page and download the executable yourself.

# Demo

```
agenttroll@agenttroll:~/CLionProjects/branch-checklist/build$ ./branch-checklist /home/agenttroll/CLionProjects/branch-checklist/test
Parsing directory "/home/agenttroll/CLionProjects/branch-checklist/test/"...
Processing file: "/home/agenttroll/CLionProjects/branch-checklist/test/Branches.java"...
3         if (args.length == 4) {
7         if (args.length == 6) {
Parsing directory "/home/agenttroll/CLionProjects/branch-checklist/test/test2/"...
Processing file: "/home/agenttroll/CLionProjects/branch-checklist/test/test2/Branches2.java"...
3         if (args.length == 4) {
7         if (args.length == 6) {
```

# Notes

- Tabs probably aren't supported, I haven't checked

# Credits

Built with [CLion](https://www.jetbrains.com/clion/)
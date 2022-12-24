# Advent of Code 2022

My solutions for AoC 2022. Problem analysis and solutions walkthrough can be found on [my blog](https://filbertphang.github.io/2022/12/15/aoc-2022-intro.html) (although I am very behind on writing these :<).

Solutions are written in C++, with the exception of day 13, which is written in Python (`ast.literal_eval()` was too tempting!).

The `tool` folder contains a script that downloads and sets up the folder for a given day. To use it, first include a file  `tool/session_cookie`, whose only contents is the **value** of the cookie "session" for the Advent of Code website. Then, just run the script with `./setupDay.sh <day>` to set up the files for the given day.

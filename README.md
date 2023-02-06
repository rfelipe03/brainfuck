Brainfuck is an esoteric programming language consisting of only 8 commands. In this repository I aimed to make a fully compatible interpreter in C and also as demonstration, make some programs to run using it.

My version of the interpreter uses a raw unbuffered interface so you don't need to press enter each time you type a character (as in brainfuck you can only input a character at once). It also defaults to `noecho`, up to you if that's a good thing.

## Compiling

```sh
git clone https://github.com/rfelipe03/brainfuck
cd brainfuck
make
```

## Running your own programs

Just save as a text file and `./bfi source.bf`.

----------------

**Programs I made in brainfuck:**
* [Caesar shift (caesar.bf)](https://github.com/rfelipe03/brainfuck/blob/main/caesar.bf) - what the name says. You type the number of rotations (1-9, but actually any character works, since it uses the decimal value for the character minus 48). Then you type your message and it will be encrypted on-the-fly. "Enter" key ends the message and finishes the program. Alternatively you may also `echo '<NUMBER>full message body here' | ./bfi caesar.bf`.

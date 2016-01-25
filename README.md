# Five Animals

This is a command-line game and the final project for the course **Advanced Programming Concepts with C++**. Five Animals is a variation of the [Seven Dragons](http://www.looneylabs.com/games/seven-dragons) card game.

Team members:

* [t0ngliu](https://github.com/t0ngliu "t0ngliu profile")
* [Leann88](https://github.com/Leann88 "Leann88 profile")

####How to run - "simple" version:

* Add ALL the files to your favourite IDE and compile and the project! 

####How to run on UNIX
* `cd` into the FiveAnimals directory (or which ever directory you put the project into)
* `$ clang++ -std=c++11 -stdlib=libc++ *.cpp`
  * Note this uses the clang C++ compiler, which comes with Xcode (command line tools) on MacOSX. If you choose you can use `g++`.
* Then run `$ ./a.out`

####Notes on running:
	
* Must use a standard C++11 compiler 
* Some IDEs like Xcode might require you to add external files (.txt) to the project directory, ie. specify the working directory. Make sure to specify your working directory so that the .txt files (particularly the saveData.txt) can be found.
* Don't forget to read the comments in code for clarification!
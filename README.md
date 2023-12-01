# Minishell (done in collaboration with [mwagner86](https://github.com/mwagner86))
<p align="center"><img src="https://cdn-images-1.medium.com/v2/resize:fit:1200/1*mb0KkzYAZDDSvdYC2MM5hg.jpeg" width="150" height="150" />

#
<h3><b>¤ Table of contents ¤</b></h3>

1) <b>How to use</b>
2) <b>Introduction</b>
3) <b>Instructions</b>
4) <b>Part 1: Parameters</b>
5) <b>Part 2: This project is fun and not stressful at all</b>

---
<h3><b>¤ How to use ¤</b></h3>

* Clone the git repository.
* Adjust linker for `readline` depending on your OS.
* Execute `make` in terminal.
* Execute the following line in the terminal: `./minishell`

---
<h3><b>¤ Introduction ¤</b></h3>
<p align="center">In "minishell" we are tasked to recreate the basic functionalities of "shell". The goal of this particular subject is to get used to how processes and file descriptors work. While it is impossible to fully recreate "bash" with the given parameters and time constrains, in the end we have created a functional, albeit modest "shell".

---
<h3><b>¤ Instructions ¤</b></h3>

* Project must be written in C.

* Functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors.

* All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated.
If the subject requires it, you must submit a Makefile which will compile your source files to the required output with the flags -Wall, -Wextra and -Werror, use cc, and Makefile must not relink.

* Makefile must at least contain the rules $(NAME), all, clean, fclean and re.


---
<h3><b>¤ Part 1: Parameters ¤</b></h3>

<p align="left̨">

* Display a prompt when waiting for a new command
* Have a working history.
* Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
* Avoid using more than one global variable to indicate a received signal. Consider
the implications: this approach ensures that your signal handler will not access your
main data structures
* Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
* Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
* Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
* Implement redirections.
* Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
* Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
* Handle $? which should expand to the exit status of the most recently executed
foreground pipeline
* Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.


---
<h3><b>¤ Part 2: This project is fun and not stressful at all ¤</b></h3>

![imageminishell](https://github.com/Valsimot42/minishell/assets/104424918/47e327a9-4ed5-4e20-ab40-5cf352f1d613)

# Huffman Encoding in C


This project is an implementation of the Huffman compression algorithm written in C.


The primary goal, however, is not only to implement the algorithm itself, but to use it as a vehicle for practicing software design at a lower level of abstraction.


While working on this project, I am focusing on:


* designing small modules with clear responsibilities;

* building expressive APIs instead of writing monolithic functions;

* reasoning about ownership and memory management;

* practicing manual resource management (`malloc`, `realloc`, `free`);

* improving naming by describing the domain rather than the implementation;

* writing code that communicates the algorithm before its implementation details.


This is the first project where I am consciously focusing on software design rather than simply writing code that works. Throughout its development, I have started to appreciate the difference between programming and designing software: identifying responsibilities, defining clear boundaries between modules, and thinking in terms of abstractions instead of implementation details.


The code is inspired by the design philosophy often found in systems software, where simplicity, readability, and well-defined interfaces are preferred over unnecessary abstraction.


Suggestions, architectural discussions, code reviews, and design feedback are always welcome. If you notice a way to improve the structure, responsibilities, or overall design, I would genuinely appreciate hearing your perspective.


Although the implementation targets the Huffman algorithm, the broader objective is to develop the mindset required for systems programming and to become a better software engineer by learning to design maintainable software.

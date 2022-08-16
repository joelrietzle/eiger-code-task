# Rolling Hash Algorithm

Make a rolling hash based file diffing algorithm. When comparing original and an updated version of an input, it should return a description ("delta") which can be used to upgrade an original version of the file into the new file. The description provides information of the chunks which:

- Can be reused from the original file
- Have been added or modified and thus would need to be synchronized

The real-world use case for this type of construct could be a distributed file storage system. This reduces the need for bandwidth and storage. If user has a local copy of a file stored in the cloud, then changes between these two instances can be synchronized using diff produced by rolling hash.

A library that does a similar thing is [rdiff](https://linux.die.net/man/1/rdiff). You don't need to fulfill the patch part of the API, only signature and delta.

## Requirements

- Hashing function gets the data as a parameter. Separate possible filesystem operations.
- Chunk size can be fixed or dynamic, but must be split to at least two chunks on any sufficiently sized data.
- Should be able to recognize changes between chunks. Only the exact differing locations should be added to the delta.
- Well-written unit tests function well in describing the operation, no UI necessary.

## Checklist

1. Input/output operations are separated from the calculations
2. detects chunk changes and/or additions
3. detects chunk removals
4. detects additions between chunks with shifted original chunks
```

## Building the project

To build the project, all you need to do, ***after installing all the relevant tools such as CMake and g++***, is to run a similar **CMake** routine
to the the one below:

```bash
mkdir build/ && cd build/
cmake .. -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory
```
## Generate output file for main

```bash
g++ -std=c++20 -o main -I/absolute/path/to/custom/include/directory src/main.cpp src/adler32/adler32.cpp src/fileio/fileio.cpp src/fileio/signature.cpp src/sync/sync.cpp src/mybaseclass.cpp

Run the output file:
./main
```

## Running the tests

By default, the template uses [Google Test](https://github.com/google/googletest/)
for unit testing. Unit testing can be disabled in the options, by setting the
`ENABLE_UNIT_TESTING` (from
[cmake/StandardSettings.cmake](cmake/StandardSettings.cmake)) to be false. To run
the tests, simply run this g++ command from the root to create a main_test output file. An example can look like this:

```bash
g++ -std=c++20 -o main_test -I/Users/joelrietz/eiger-code-task/include/ src/adler32/adler32.cpp src/fileio/fileio.cpp src/fileio/signature.cpp src/sync/sync.cpp src/mybaseclass.cpp test/src/adler32_test.cpp test/src/fileio_test.cpp test/src/tests.cpp test/src/signature_test.cpp test/src/sync_test.cpp -lgtest # to build the Google test output file main_test.
./main_test # to run the Google test file

# you can also run tests with the `-VV` flag for a more verbose output (i.e.
#GoogleTest output as well)
```

## Issues and future improvements
I am going to summarize and break down some possible improvements that could've been done:

## adler32.cpp
  * Improving the Adler 32 checksum calculations through method chaining would have made calculations turn out correctly. 
      For example the RollOut().RollOut().Sum() calculations should have been implemented that way. According to these instructions:
      https://levelup.gitconnected.com/how-to-implement-method-chaining-in-c-3ec9f255972a
      
## fileio.cpp
  * This file was fairly straight forward. An alternative method for handling files would be using the std::filesystem library:
      https://en.cppreference.com/w/cpp/filesystem/file_size
      
## signature.cpp
  * Limited encoding and decoding libraries for C++. Found a base64 encoding and decoding library that I ended up using. However, I see that std::codecvt 
      could be a better implementation as it's a built in standardized library that converts a string from UTF-8 to UTF-32. Implemented like this:
      https://en.cppreference.com/w/cpp/locale/codecvt
      
## sync.cpp
  * This implementation ended up utilizing a lot of maps. Another way would be to use the std::unordered_map library instead as it reduces the complexity for a look-up. However, for this implementation, the order of the elements are of importance which makes an undordered map less suitable.
 
 ## mybaseclass.cpp
  * This implementation is made for creating objects for Adler32, Signature, and Sync using the factory function design. There are different ways to design a factory function and could possibly be improved by using this methodology: 
  https://www.geeksforgeeks.org/design-patterns-set-2-factory-method/
  
## main.cpp
  * There is an issue providing the ifstream file to the BuildSigTable(std::ifstream& infile) function that causes a segmentation fault when running the application. I suspect this is due to a misuse of the ifstream library where it causes an error related to this:
  https://en.cppreference.com/w/cpp/io/ios_base/failure
  
## Conclusion & Evaluation
  * I found this coding task interesting and challenging. It's the first time I do this kind of implementation. The implementation can certainly be   improved in order to pass more tests, referring to the issues and improvements mentioned above. I would love to discuss other possible solutions to this task and how it can be done in a better and more efficient way.
  * If I would do this task again I would start by writing each file and then write it's corresponding test file as it would allow me to understand the inputs, outputs and the flow of the program much better and faster. This would also allow me to find errors earlier and have time to correct them in order to produce a more complete and optimal solution.
  * My hunch is that this task would be more suitable to a language like Golang. Especially when handling byte streams with buffers, readers as well as lookup tables.


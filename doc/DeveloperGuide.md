# CMakeSL Developer Guide

## C++
C++17 is used. No particular compilator is required.

## Libraries
A set of libraries are created in the project:
* common - common stuff like algorithms etc.
* errors - this one was introduced to be able to shadow mock the `errors_observer` class. Now, it's considered to remove this library, or at least, remove shadow mocking and just create an interface for `errors_observer` (that's still a TODO).
* lexer - this one takes a raw `std::string` and returns a vector of tokens
* ast - this one takes the vector of tokens and returns an ast tree.
* sema - this one takes the ast tree and returns sema tree.
* exec - finally, this one takes the sema tree and executes it.
* cmsl_tools - a library with a C interface that provides functions for syntax completion and source indexing.

Additionally, executables are created:
* cmakesl - It's a simple exec that takes path to sources and executes CMakeSL script outside the CMake world. It's used to quickly execute some scripts and see what happens.

## Testing
To enable tests, set `CMAKESL_WITH_TESTS=ON` while CMake configuration.

## Contribution
Just grab sources, make changes and a create pull request to `master` branch.
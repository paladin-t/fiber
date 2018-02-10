## Fiber

**Header only cross platform wrapper of fiber API**

A [fiber](https://en.wikipedia.org/wiki/Fiber_(computer_science)) is a particularly lightweight thread of execution. Which is useful for implementing coroutine, iterator, lightweight thread, etc.

### How to use

Just `#include "fiber.h"` before using this library.

There are quite few interfaces:

~~~~~~~~~~c
FBAPI static bool_t fiber_is_current(const fiber_t* const fb);
FBAPI static fiber_t* fiber_create(fiber_t* primary, size_t stack, fiber_proc run, void* userdata);
FBAPI static bool_t fiber_delete(fiber_t* fb);
FBAPI static bool_t fiber_switch(fiber_t* fb);
~~~~~~~~~~

Read comments [in code](fiber.h) to get the usage, or start with a simple [example](test.c).

### Dependency/Backend

* Windows backend with [`fiber` functions](https://msdn.microsoft.com/en-us/library/windows/desktop/ms684847(v=vs.85).aspx#fiber_functions)
* POSIX backend with [`setcontext` functions](https://en.wikipedia.org/wiki/Setcontext)

### Drafting

This library is supposed to be cross platform as possible. However it's drafting because I've only implemented and tested it on Windows and POSIX systems. Supporting for more platforms will be added in the future; any pull requests are welcome.

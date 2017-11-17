#include "fiber.h"
#include <assert.h>
#include <stdio.h>
#ifdef FB_OS_WIN
#	include <crtdbg.h>
#endif /* FB_OS_WIN */

struct test_t {
	int sum;
	fiber_t* fb0;
	fiber_t* fb1;
	fiber_t* fb2;
};

static void fiber1(fiber_t* fb) {
	struct test_t* t = (struct test_t*)fb->userdata;

	assert(fiber_is_current(t->fb1));
	printf("fiber1: %d\n", ++t->sum);
	fiber_switch(t->fb2);

	assert(fiber_is_current(t->fb1));
	printf("fiber1: %d\n", ++t->sum);
	fiber_switch(t->fb2);

	assert(fiber_is_current(t->fb1));
	printf("fiber1: %d\n", ++t->sum);
	fiber_switch(t->fb2);
}

static void fiber2(fiber_t* fb) {
	struct test_t* t = (struct test_t*)fb->userdata;

	assert(fiber_is_current(t->fb2));
	printf("fiber2: %d\n", ++t->sum);
	fiber_switch(t->fb0);

	assert(fiber_is_current(t->fb2));
	printf("fiber2: %d\n", ++t->sum);
	fiber_switch(t->fb0);

	assert(fiber_is_current(t->fb2));
	printf("fiber2: %d\n", ++t->sum);
	fiber_switch(t->fb0);
}

#ifdef FB_OS_WIN
static void on_exit(void) {
	if (!!_CrtDumpMemoryLeaks()) {
		fprintf(stderr, "Memory leak!\n");

		_CrtDbgBreak();
	}
}
#endif /* FB_OS_WIN */

/**
 * An example which creates 3 fibers (including the primary fiber),
 * and switches several times from one another.
 */
int main() {
	/**< `test_t` is used to store some test data and will be carried by fibers as userdata. */
	struct test_t test;
	memset(&test, 0, sizeof(test));

#ifdef FB_OS_WIN
	atexit(on_exit);
#endif /* FB_OS_WIN */

	/**< Creates the primary fiber before creating the two minor fibers. */
	test.fb0 = fiber_create(0, 0, 0, &test);
	test.fb1 = fiber_create(test.fb0, 0, fiber1, &test);
	test.fb2 = fiber_create(test.fb0, 0, fiber2, &test);

	/**< Switching. */
	assert(fiber_is_current(test.fb0));
	fiber_switch(test.fb1);
	assert(fiber_is_current(test.fb0));
	fiber_switch(test.fb1);
	assert(fiber_is_current(test.fb0));
	fiber_switch(test.fb1);

	/**< Deletes minor fibers before deleting the primary fiber. */
	fiber_delete(test.fb2);
	fiber_delete(test.fb1);
	fiber_delete(test.fb0);

	return 0;
}
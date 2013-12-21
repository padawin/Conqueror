#include "test.h"
#include "testbuilder.h"

void testbuilder()
{
	int a = 1;
	int b = 2;
	int c = 2;
	assert_int_equals(a, b);
	assert_int_equals(b, c);
}

int main()
{
	testbuilder();
	return 1;
}

#include <assert.h>
#include <math.h>

#include "../src/object.h"

int main()
{
    const Object a = 2.0;
    const Object b = 3.0;
    const Object c = 5.0;

    const Object a_b_add_c_mul = object_mul((object_add(a, b)), c);
    const Object a_b_mul_c_add = object_add((object_mul(a, b)), c);
    const Object a_c_add_b_mul = object_mul((object_add(a, c)), b);
    const Object a_c_mul_b_add = object_add((object_mul(a, c)), b);

    assert(fabs(a_b_add_c_mul - 25.0) < 0.000000001);
    assert(fabs(a_b_mul_c_add - 11.0) < 0.000000001);
    assert(fabs(a_c_add_b_mul - 21.0) < 0.000000001);
    assert(fabs(a_c_mul_b_add - 13.0) < 0.000000001);
}

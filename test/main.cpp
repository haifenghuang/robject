// Copyright (C) 2011 by Kristian Rumberg <kristianrumberg@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "rtest.hpp"

extern "C" {
#include "rint.h"
#include "rstring.h"
#include "volvo.h"
}

RTEST_TEST(RObjectUnitTest, createRInt) {
    const int value = 5;

    RInt self = rint_create(value);
    RTEST_ASSERT_TRUE(NULL != self);

    RTEST_ASSERT_EQ(value, rint_getvalue(self));
    rint_destroy(&self);
    RTEST_ASSERT_TRUE(NULL == self);
}

RTEST_TEST(RObjectUnitTest, createRString) {
    const int value = 5;

    RString self = rstring_create("Hello");
    RTEST_ASSERT_TRUE(NULL != self);

    RTEST_ASSERT_FALSE(strcmp("Hello", rstring_cstr(self)));
    rstring_destroy(&self);
    RTEST_ASSERT_TRUE(NULL == self);
}

RTEST_TEST(RObjectUnitTest, createCar) {
    Car car = car_create();
    RTEST_ASSERT_FALSE(strcmp("car", car_cstr(car)));
    car_destroy(&car);
    RTEST_ASSERT_TRUE(car == NULL);
}

RTEST_TEST(RObjectUnitTest, createVolvo) {
    Car car = volvo_create();
    RTEST_ASSERT_FALSE(strcmp("volvo", car_cstr(car)));
    car_destroy(&car);
    RTEST_ASSERT_TRUE(car == NULL);
}

int main(int argc, char** argv)
{
    RTest::runAllTests();
    return 0;
}

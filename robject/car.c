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

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "car.h"

struct CarPrivate_s {
};

ROBJECT_C(Car, car, RObject, robject)

static void car_initialize(Car self)
{
}

static void car_finalize(Car self)
{
}

Car car_create()
{
	Car self = (Car) robject_create(car_class());

	return self;
}

const char* car_cstr(Car self)
{
	CarClass klass = (CarClass)(((RObject) self)->klass);

	if (klass->cstr != NULL) {
		return klass->cstr(self);
	} else {
		return "car";
	}
}

void car_class_initialize(CarClass klass) {
	/* Nothing to override */
}


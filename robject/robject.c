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

#include "robject.h"

static void robject_class_initialize(RObjectClass klass)
{
}

void robject_class_constructor(RObjectClass klass)
{
	robject_class_initialize(klass);
}

static void robject_initialize(RObject obj)
{
	puts("robject_initialize");
}

void robject_constructor(RObject obj)
{
	puts("robject_constructor");
	robject_initialize(obj);
}

static void robject_finalize(RObject obj)
{
	puts("robject_finalize");
}

void robject_destructor(RObject obj)
{
	robject_finalize(obj);
}

RObject robject_create(RObjectClass klass)
{
	RObject obj = NULL;

	assert(klass);
	assert(klass->obj_size);
	obj = (RObject) calloc(klass->obj_size, 1);

	assert(klass);
	obj->klass = klass;

	klass->constructor(obj);

	return obj;
}

void robject_destroy(RObject* obj_pointer)
{
	puts("robject_destroy");

	if (obj_pointer) {
		if (*obj_pointer) {
			RObject obj = *obj_pointer;
			assert(obj);

			RObjectClass klass = obj->klass;
			assert(klass);

			puts("Calling destructor");
			assert(klass->destructor);
			klass->destructor(obj);
			free(obj);
			*obj_pointer = NULL;
		}
	}
}

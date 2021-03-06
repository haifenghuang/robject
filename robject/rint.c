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

#include "rint.h"

struct RIntPrivate_s {
	int value;
};

ROBJECT_C(RInt, rint, RObject, robject)

static void rint_initialize(RInt self)
{
	RIntPrivate priv = self->priv;
	priv->value      = 0;
}

static void rint_finalize(RInt self)
{
}

RInt rint_create(int value)
{
	RInt self = (RInt) robject_create(rint_class());

	RIntPrivate priv = self->priv;
	priv->value      = value;

	return self;
}

int rint_getvalue(RInt self)
{
	RIntPrivate priv = self->priv;
	return priv->value;
}

void rint_class_initialize(RIntClass klass) {
}

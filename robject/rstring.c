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
#include <string.h>

#include "rstring.h"

struct RStringPrivate_s {
	char*  str;
	size_t len;
};

static void rstring_initialize(RString rstring)
{
	RStringPrivate priv = rstring->priv;
	priv->str = NULL;
	priv->len = 0;
}

void rstring_constructor(RObject obj)
{
	RString self = (RString) obj;
 	self->priv   = calloc(sizeof(struct RStringPrivate_s), 1);

	rstring_initialize(self);
	robject_constructor(obj);
}

static void rstring_finalize(RString rstring)
{
	RStringPrivate priv = rstring->priv;

	if (priv->str) {
		free(priv->str);
	}
}

void rstring_destructor(RObject obj)
{
	RString self = (RString) obj;

	rstring_finalize(self);
 	if (self->priv) {
 		free(self->priv);
		self->priv = NULL;
 	}
	robject_destructor(obj);
}

ROBJECT_C_CLASS(RString, rstring)

RString rstring_create(const char* str)
{
	RString self = (RString) robject_create(rstring_class());

	RStringPrivate priv = self->priv;
	priv->str = strdup(str);
	priv->len = strlen(str);

	return self;
}

const char* rstring_cstr(RString self)
{
	RStringPrivate priv = self->priv;

	return priv->str;
}

ROBJECT_C_DESTROY(RString, rstring)

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

#ifndef ROBJECT_H
#define ROBJECT_H

typedef struct RObject_s* RObject;
typedef struct RClass_s*  RClass;

typedef void (*robject_constructor_fp)(RObject self);
typedef void (*robject_destructor_fp)(RObject self);

struct RClass_s {
	robject_constructor_fp constructor;
	robject_destructor_fp  destructor;
	size_t                 obj_size;
};

struct RObject_s {
	RClass klass;
};

// Macro start
void robject_destructor(RObject obj);
void robject_constructor(RObject obj);
// Macro end

RObject robject_create(RClass rclass);

void robject_destroy(RObject* obj_pointer);

#define ROBJECT_H_CONSTRUCTOR(Self, self)  void self##_constructor(RObject obj);

#define ROBJECT_C_CONSTRUCTOR(Self, self)				\
void self##_constructor(RObject obj)					\
{									\
	Self self = (Self) obj;						\
	self->priv   = calloc(sizeof(struct Self##Private_s), 1);	\
									\
	self##_initialize(self);					\
	robject_constructor(obj);					\
}

#define ROBJECT_H_DESTRUCTOR(Self, self) void self##_destructor(RObject obj);

#define ROBJECT_C_DESTRUCTOR(Self, self)	\
void self##_destructor(RObject obj)		\
{						\
	Self self = (Self) obj;			\
						\
	self##_finalize(self);			\
	if (self->priv) {			\
		free(self->priv);		\
		self->priv = NULL;		\
	}					\
	robject_destructor(obj);		\
}

#define ROBJECT_H_DESTROY(Self, self)	void self##_destroy(Self* self_pointer);

#define ROBJECT_C_DESTROY(Self, self)				\
void self##_destroy(Self* self_pointer)				\
{   								\
	RObject* obj_pointer = (RObject*) self_pointer;		\
	robject_destroy(obj_pointer);				\
}

#define ROBJECT_H_CLASS(Self, self) RClass self##_class();

#define ROBJECT_C_CLASS(Self, self)				\
RClass self##_class()						\
{								\
	static struct RClass_s klass = {0, };			\
								\
	if (klass.obj_size == 0) {				\
		klass.constructor = self##_constructor;		\
		klass.destructor  = self##_destructor;		\
		klass.obj_size    = sizeof(struct Self##_s);	\
	}							\
								\
	return &klass;						\
}

#endif /* ROBJECT_H */

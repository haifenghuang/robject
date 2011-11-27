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
typedef struct RObjectClass_s*  RObjectClass;

typedef void (*robject_constructor_fp)(RObject self);
typedef void (*robject_destructor_fp)(RObject self);

struct RObjectClass_s {
	robject_constructor_fp		constructor;
	robject_destructor_fp		destructor;
	size_t				obj_size;
};

struct RObject_s {
	RObjectClass klass;
};

// Macro start
void robject_class_constructor(RObjectClass klass);

void robject_destructor(RObject obj);
void robject_constructor(RObject obj);
// Macro end

RObject robject_create(RObjectClass klass);

void robject_destroy(RObject* obj_pointer);

#define ROBJECT_H_BEGIN(Self, self, Super, super)		\
typedef struct Self##Class_s* Self##Class;			\
typedef struct Self##_s* Self;					\
typedef struct Self##Private_s* Self##Private;			\
								\
ROBJECT_H_CLASS_CONSTRUCTOR(Self, self, Super, super)		\
ROBJECT_H_CONSTRUCTOR(Self, self, Super, super)			\
ROBJECT_H_DESTRUCTOR(Self, self, Super, super)			\
ROBJECT_H_CLASS(Self, self, Super, super)			\
ROBJECT_H_DESTROY(Self, self, Super, super)			\
								\
struct Self##_s { 						\
	struct Super##_s base;					\
	Self##Private    priv;					\
};								\
struct Self##Class_s {						\
	struct Super##Class_s base;

#define ROBJECT_H_END \
};


#define ROBJECT_H_CLASS_CONSTRUCTOR(Self, self, Super, super)  void self##_class_constructor(RObjectClass klass);

#define ROBJECT_H_CONSTRUCTOR(Self, self, Super, super)  void self##_constructor(RObject obj);

#define ROBJECT_C_CONSTRUCTOR(Self, self, Super, super)			\
void self##_constructor(RObject obj)					\
{									\
	Self self = (Self) obj;						\
	self->priv   = calloc(sizeof(struct Self##Private_s), 1);	\
									\
	self##_initialize(self);					\
	super##_constructor(obj);					\
}

#define ROBJECT_C_CLASS_CONSTRUCTOR(Self, self, Super, super)		\
									\
void self##_class_constructor(RObjectClass klass)			\
{									\
	super##_class_constructor(klass);				\
	self##_class_initialize((Self##Class)klass);			\
}

#define ROBJECT_H_DESTRUCTOR(Self, self, Super, super) void self##_destructor(RObject obj);

#define ROBJECT_C_DESTRUCTOR(Self, self, Super, super)	\
void self##_destructor(RObject obj)			\
{							\
	Self self = (Self) obj;				\
							\
	self##_finalize(self);				\
	if (self->priv) {				\
		free(self->priv);			\
		self->priv = NULL;			\
	}						\
	super##_destructor(obj);			\
}

#define ROBJECT_H_DESTROY(Self, self, Super, super)	void self##_destroy(Self* self_pointer);

#define ROBJECT_C_DESTROY(Self, self, Super, super)		\
void self##_destroy(Self* self_pointer)				\
{   								\
	RObject* obj_pointer = (RObject*) self_pointer;		\
	robject_destroy(obj_pointer);				\
}

#define ROBJECT_H_CLASS(Self, self, Super, super)	RObjectClass self##_class();

#define ROBJECT_C_CLASS(Self, self, Super, super)			\
RObjectClass self##_class()						\
{									\
	static struct RObjectClass_s klass = {0, };			\
									\
	if (klass.obj_size == 0) {					\
		self##_class_constructor(&klass);			\
									\
		klass.constructor	= self##_constructor;		\
		klass.destructor	= self##_destructor;		\
		klass.obj_size		= sizeof(struct Self##_s);	\
	}								\
									\
	return &klass;							\
}

#define ROBJECT_C(Self, self, Super, super)			\
static void self##_class_initialize(Self##Class klass);		\
static void self##_initialize(Self self);			\
static void self##_finalize(Self self);				\
								\
ROBJECT_C_CLASS_CONSTRUCTOR(Self, self, Super, super)		\
ROBJECT_C_CONSTRUCTOR(Self, self, Super, super)			\
ROBJECT_C_DESTRUCTOR(Self, self, Super, super)			\
ROBJECT_C_CLASS(Self, self, Super, super)			\
ROBJECT_C_DESTROY(Self, self, Super, super)

#endif /* ROBJECT_H */

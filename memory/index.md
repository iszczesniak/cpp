---
title: Memory model
---

# Introduction

The memory model of C++ describes:

* when data is created and destroyed,

* where (i.e., what part of memory, what data structure) data is
  allocated,

* how data is passed to and returned from a function.

C++ has to respect the basic requirements of an operating system, but
the rest is up to C++.

## The basic requirements of an operating system

When we run a *program*, it becomes a *process* in an operating
system, and a *task* a processor is executing.  A process manages its
memory within the limits imposed by the operating system.  An
operating system offers a process two types of memory: *read-only*,
and *read-write*.

The read-only memory stores the code of the program (i.e., the
processor instructions), and the static data (e.g., string literals).
This memory is shared by all processes of the same program, which can
be a substantial saving for a large program run in a large number
(e.g., Google Chrome).

An *unprivileged* task (a *privileged* task is a kernel task, i.e., a
task of an operating system) cannot do anything that could disturb the
operating system and other processes.  For instance, an unprivileged
task cannot write to its read-only memory.  Every processes is an
unprivileged task.

In the following example we try to write to the read-only memory.  The
code compiles, but is killed by the operating system with the SIGSEGV
(segment violation) signal.

{% highlight c++ %}
{% include_relative sigsegv.cc %}
{% endhighlight %}

All other data is located in the read-write memory, because it can be
changed by a process.  Every process has its own read-write memory,
even when there are many processes of the same program.

## What is up to C++

C++ describes how data are managed in the read-write memory.  C++
strives for time and memory performance: the performance is of the
highest importance, but at the cost of C++ being more complex,
nuanced, and harder to use.

The memory model of C++ is deterministic: we can point out exactly
where and when data are *destroyed*.  This model leads to efficient
and carefull programming, as the objects which are not needed anymore
are immediatelly destroyed.

This comes in stark contrast with other languages, such as Java or C#,
where a programmer not only cannot exactly say where and when data are
destroyed, but simply do not care, because their built-in garbage
collectors take care of that.  The problem is that the garbage
collectors are nondeterministic, i.e., a programmer does not exactlly
know where and when data are destroyed.

In the past, the C++ Standard Committee considered a garbage
collection support, but dropped it for performance reasons.  Nowadays,
C++ requires no garbage collection since it offers advanced container
support and the smart pointers, which automatically destroy data when
needed (which could be considered a form of garbage collection).

# Types of data

The read-write memory stores:

* global and static data,

* local data at a stack (more specifically, a stack per thread of the
  process),

* dynamic data at the heap (a.k.a a free-store).

## The global and static data

Global data are initialized before entering the main function:

{% highlight c++ %}
{% include_relative global.cc %}
{% endhighlight %}

Static data are initialized before its first use:

{% highlight c++ %}
{% include_relative static.cc %}
{% endhighlight %}

## The local data

## The dynamic data

# Function calls

## Passing arguments

## Returning values

# Conclusion

<!-- LocalWords: lvalue lvalues rvalue rvalues -->
<!-- LocalWords: decrementation incrementation -->
<!-- LocalWords: dereference expr unary -->
<!-- LocalWords: glvalue prvalue xvalue -->

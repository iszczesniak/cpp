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

# What is up to C++

C++ describes how data is managed in the read-write memory.  C++
strives for time and memory performance, i.e., the performance is of
the highest importance, as the cost of C++ being more complex, and
nuanced.

The read-write memory stores:

* global and static data,

* dynamic data at the heap (a.k.a a free-store), and

* local data at a stack (more specifically, a stack per thread of the
  process).

This is an example of global data, which is initialized before
entering the main function:

{% highlight c++ %}
{% include_relative global.cc %}
{% endhighlight %}

This is an example of static stata, which is initialized before its
first use:

{% highlight c++ %}
{% include_relative static.cc %}
{% endhighlight %}

<!-- LocalWords: lvalue lvalues rvalue rvalues -->
<!-- LocalWords: decrementation incrementation -->
<!-- LocalWords: dereference expr unary -->
<!-- LocalWords: glvalue prvalue xvalue -->

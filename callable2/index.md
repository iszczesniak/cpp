---
title: Callable - kontynuacja
---

# Wprowadzenie

Wiemy już, że callable jest czymś, co możemy wywołać, czyli użyć w
wyrażeniu wywołania.  Od typu callable zależy z jakimi argumentami
możemy callable wywołać i czy callable zwróci wynik.

Callable może być określone w czasie:

* uruchomienia, czyli w czasie uruchomienia możemy wybrać callable,

* kompilacji, czyli w czasie kompilacji możemy wybrać callable.

# Callable w czasie uruchomienia

Jeżeli callable

<iframe width="800px" height="200px" src="https://godbolt.org/e#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,j:1,lang:c%2B%2B,selection:(endColumn:1,endLineNumber:18,positionColumn:1,positionLineNumber:18,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:'%23include+%3Cset%3E%0A%23include+%3Cvector%3E%0A%0Ausing+namespace+std%3B%0A%0Atemplate+%3Ctemplate+%3Ctypename%3E+typename+C,+typename+T%3E%0Avoid%0Afoo(const+C%3CT%3E+%26c)%0A%7B%0A%7D%0A%0Aint%0Amain()%0A%7B%0A++++foo(set%3Cint%3E%7B1,+2,+3%7D)%3B%0A++++foo(vector%3Cint%3E%7B1,+2,+3%7D)%3B%0A%7D%0A'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:gsnapshot,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,j:1,lang:c%2B%2B,libs:!(),options:'-std%3Dc%2B%2B1z',selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'x86-64+gcc+(trunk)+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"></iframe>

{% highlight c++ %}
{% include_relative motivation3.cc %}
{% endhighlight %}

# Callable w czasie kompilacji

Zmieniamy kod źródłowy.

# Wydajność

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->

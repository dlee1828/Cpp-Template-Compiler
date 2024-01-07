# NOTES

Within any scope, you can initialize new ints and assign existing ints.
When assigning ints (new or existing), you can use a single binary operation between two existing ints.
You can also assign an int to a literal value.

There's a straightforward mapping between this and const member variables in our main struct.
The only difference is that whenever a variable is re-assigned, we actually create a new constexpr variable 
in the struct. We continuously keep track of the struct int storing the current value of the program int.

Also, we use hard-coded templates for binary operations.

Okay, that's easy enough.

Let's now implement if statements.

The general structure of an if statement is this:
if (condition) {

} else {

}
For simplicity, condition can only be a single binary operation like a > b or x == 2.

Here's how we'll implement conditions. Firstly, we'll create a template struct for the condition value itself, which 
will be either true or false.

Then, we create a template struct.
This template struct will accept a boolean template param and the struct will be defined depending on that boolean.
Moreover, the struct will accept as template parameters all outer-scoped ints which are present in either the 
true or false code block. 

Within each struct (the true one and the false one), 
we store all the variables that are either initialized or re-assigned, in the same way we would in the root scope.

However, there's one important difference: each of these structs must have the same set of outer-scoped variables.
For example, consider this code:
if (a == 2) {
    b = 1;
    int x = 1;
    c = x + 1;
}
else {
    b = 3;
    d = 4;
}

When defining the template structs, we'd need for both structs to include values for b, c, and d.
This is done so that in our main struct, we can access any outer-scoped variable using the template struct without actually
knowing which specific struct is being used (the true version or the false version).
If a variable isn't present in a particualr code block but we need to include it, we just set it equal to the value passed 
in through the template parameters. This will leave the value of the int unaffected. 

We pass all these variables into the template parameter list of the template struct.

Then, in our main struct, we simply update the values of all affected variables using this template struct.

That's it!

Note that this already allows us to nest conditionals! How cool!


Now, we need to figure out how to do loops.
Loops are somewhat similar to if statements - we can think of them as a separate struct-defined scope where
outer-scope variables are updated or re-assigned. 
All we need to do is implement the looping recursion, which we can do fairly easily.
The recursion ensures that whatever updates occur to the variables in the loop body are repeated for a specified number
of times.
See examples.cpp for an example of how this is done.




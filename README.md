# Linked list implementation in C
This is a fairly simply linked list implementation, which keeps track of the top and bottom of the list to allow quicker insertion at the ends - which is beneficial for queues.

Lists are created and free'd using `ll_new` and `ll_delete`, respectively. Insertion is done through `ll_insert` or `ll_append`, with removal by `ll_remove` and `ll_removef`. The insert and append functions take a pointer to the data being added, this should point to a value in the heap (i.e. using malloc). The remove function will return a pointer to the data, so that it can be free'd correctly, with the `f` flavour of the function having a function pointer argument to a free'ing function. List nodes can be accessed by hand, through `node->next`, or by using the `ll_at` function.

When inserting, it is quicker to insert at either the top or bottom of the list, with removal being quickest at only the top. On an Intel i7-3770 (Linux 3.19, clang 3.6.0),

Task | Average time per task (s)
---- | -----------------------------
top insertion | 3.109 x 10<sup>-8</sup>
bottom insertion | 3.077 x 10<sup>-8</sup>
append | 2.984 x 10<sup>-8</sup>
random insertion | 1.263 x 10<sup>-4</sup>
top removal | 2.436 x 10<sup>-8</sup>
bottom removal | 1.095 x 10<sup>-4</sup>
random removal | 6.588 x 10<sup>-5</sup>

This is released under the MIT license.

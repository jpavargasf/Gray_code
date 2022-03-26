# Gray_code
 n-bit gray code generation using a binary tree

 Description:  This code uses a binary tree to find a n-bit gray code while also
               building m-bit gray code, when m<n. Or you can see as building a
               binary tree, where at depth n there is a n-bit gray code if read
               from left to right.

 How this works?
               1.Depth n will always have n bits
               2.Difference from depth n and n+1 is the less significant bit, whereas
               n+1 at the left will receive bit 0 and the right 1.
               3.If a node receives the bit 1, the process described in 2 will be
               reversed (left receives 1 and right 0) for all nodes generated from
               this, but this can be reversed again for the next nodes, coming back
               to the original process
               4.The n-bit gray code will be at depth n, if read left to right

 It is possible to use less memory (each node store 1 bit), but it will require another
 print method

 It is possible to store the code into an array, just use a global variable

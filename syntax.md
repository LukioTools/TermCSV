
## Functions

### Example
<b>FUNCTION_NAME(</b>ARG1, ARG2, ...<b>)</b>
<br>
<b>ADD(</b>1,2,4,8<b>)</b><br> *(result) ->1+2+4+8 -> 15*
<br>
<b>MULTIPLY(</b>1,2,4,8<b>)</b> <br> *(result) -> 1\*2\*4\*8 -> 16*

### Explanation
functions fundementaly return only one value, for multiple returns see [Filter](#filters)
<br>
depending on function it might not use all of the arguments

## Filters
todo
### Example
Syntax is like [Functions](#functions)

### Explanation
For either modifying values, filtering only wanted values.
<br>
Returns multiple values so it cannot be an cells endpoint *(first value is used)*

## Cell-Ranges
*Single Cell*: **x:y->x+1:y+1** ~~or x:y~~ 
<br>
~~Whole Column: x:y->~~
<br>
### Explanation
**Cells who dont have an value are ignored**
<br>
Its like c++ ranges [begin, end[ *(last term is excluded)*
<br>
So if you want a single cell x,y you would write it as a range x:y->x+1:y+1 ~~or x:y~~ *(not implemented)*
<br>



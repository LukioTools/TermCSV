
## Functions

### Example
`FUNCTION_NAME(ARG1, ARG2, ...)`
<br>
`ADD(1,2,4,8)` *(result) ->1+2+4+8 -> 15*
<br>
`MULTIPLY(1,2,4,8)` *(result) -> 1\*2\*4\*8 -> 16*

### Explanation
Functions fundementaly return only one value, for multiple returns see [Filter](#filters)
<br>
Depending on function it might not use all of the arguments
If not enough variables are supplied empty *(std::monostate())* is returned

## Filters
todo
### Example
Syntax is like [Functions](#functions)

### Explanation
For either modifying values, filtering only wanted values.
<br>
Returns multiple values so it cannot be an cells endpoint *(first value is used)*

## Cell-Ranges
*Single Cell*: `x:y->x+1:y+1` ~~or `x:y`~~ 
<br>
~~Whole Column: `x:y->x:`~~
<br>
Part of Column: `x:y->x:y+n`
<br>
~~Whole Row: `x:y->:y`~~
<br>
Part of Row: `x:y->x+n:y`
<br>
Constants are defined with !: `!x:!y->n:n`


<br>
### Explanation
**Cells who dont have an value are ignored**
<br>
Its like c++ ranges [begin, end[ *(last term is excluded)*
<br>
So if you want a single cell x,y you would write it as a range x:y->x+1:y+1 ~~or x:y~~ *(not implemented)*
<br>




## Functions

### Example
`FUNCTION_NAME(ARG1, ARG2, ...)`
<br>
`ADD(1,2,4,8)` *->1+2+4+8 -> 15*
<br>
`MULTIPLY(1,2,4,8)` *-> 1\*2\*4\*8 -> 16*

### Explanation
Functions fundementaly return only one value, for multiple returns see [Filter](#filters)
<br>
Depending on function it might not use all of the arguments
<br>
If not enough variables are supplied empty *(std::monostate())* is returned
<br>
For individual functions you shall refer to ~~function-list~~

## Filters
### Example
Syntax is like [Functions](#functions)

`FILTER_NAME(ARG1, ARG2, ...)`
<br>
`EVEN(1,2,3,4,5,6,7)` *-> {2,4,6}*
<br>
`ODD(1,2,3,4,5,6,7)` *-> {1,3,5,7}*
<br>
`GEQ(1,2,3,4,5,6,7,5)` *-> {5,6,7}*
<br>
`LEQ(1,2,3,4,5,6,7,5)` *-> {1,2,3,4,5}*


### Explanation
For either modifying values or filtering only wanted values.
<br>
Returns multiple values so it cannot be an cells endpoint *(first value is used if it is used incorrectly)*
<br>
For individual filter you shall refer to ~~filter-list~~

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



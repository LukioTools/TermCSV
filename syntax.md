## Functions

### Example
`FUNCTION_NAME(ARG1, ARG2, ...)`
<br>
`ADD(1,2,4,8)` *->1+2+4+8 -> {15}*
<br>
`MULTIPLY(1,2,4,8)` *-> 1\*2\*4\*8 -> {16}*
<br>
`ODD(1,2,3,4,5,6,7)` *-> {1,3,5,7}*
<br>
`GEQ(1,2,3,4,5,6,7,5)` *-> {5,6,7}*

### Explanation
Functions fundementaly return a list of values
<br>
Depending on function it might not use all of the arguments
<br>
If not enough variables are supplied empty [Null](#null) is returned
<br>
For individual functions you shall refer to [function-list](#function-list)
<br>


### Function-List

#### ADD
Adds up every **[Number](#numbers)** and returns an [Integer](#integer) if every input is an integer, otherwise returns a [Float](#float)
<br>
If no arguments are provided, returns [Null](#null)

#### MULTIPLY
Multiplies every **[Number](#numbers)** and returns an [Integer](#integer) if every input is an integer, otherwise returns a [Float](#float)
<br>
If no arguments are provided, returns [Null](#null)

#### DIVIDE
Divides every **[Number](#numbers)** and returns a [Float](#float)
<br>
If no arguments are provided, returns [Null](#null)

#### SUB
Subtract every **[Number](#numbers)** and returns an [Integer](#integer) if every input is an integer, otherwise returns a [Float](#float)
<br>
If no arguments are provided, returns [Null](#null)

#### COUNT
Count the number of arguments, returns an [Integer](#integer) of the number of argumens supplied.
Returns an [Integer](#integer) zero if none are supplied.


### Filter-List

#### ~~EVEN~~
Returns only **[Numbers](#numbers)** that are even

#### ~~ODD~~
Returns only **[Numbers](#numbers)** that are odd



## Cell-Ranges

### Usage

*Single Cell*: `x:y->x:y` ~~or `x:y`~~ 
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

### Explanation
**Cells in Whole type operations who dont have an value are ignored**
<br>
**Cells in Part type operations who dont have an value are NOT ignored**
<br>
Its [begin, end] *(last term is included)* for invalid both are set to -1:-1 (unsigned integer limit)
<br>
uint integer limit is also used for whole types of selections
<br>
So if you want a single cell x,y you would write it as a range x:y->x+1:y+1 ~~or x:y~~ *(not implemented)*
<br>


## Values

### Numbers

#### Integer

All numbers, which dont have a decimal point *( ',' or '.' )* are treated as **long** *(int_64)*

#### Float
If it has **one** decimal point*( ',' or '.' )* it is treated as a **double** *(float_64)*

### Strings
If there are two or more decilmal points, or it contains a charachter other than a digit, it is treated as a **string** *(std::ustring aka std::wstring)*

### Timepoint / Date
~~Timestamp or date are marked as ...~~


## Null
Is a std::monostate() present in Eval variant
<br>
Used to represent nonexistant values fe. empty cells and invalid function usage
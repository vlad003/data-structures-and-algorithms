# Array

An array is a data structure that contains a sequence of homogeneous elements.
The number of elements in an array is usually fixed.

## Implementation

One-dimensional arrays are implemented as a contiguous section of memory.

## Usage

### Declaring an array

An example declaration of an array in C is

```c
int NAME[n];
```

That declares an static array of `n` integers. The format is `TYPE NAME[SIZE]`.

Alternatively, an array can be declared dynamically using `malloc`:

```c
int *NAME = malloc(n * sizeof(int));
```

One important thing to note that `sizeof` returns different values depending on
how you've declared the array. If you've declared it statically (the first
case), then `sizeof(NAME) == n * sizeof(int)`. In the second case,
`sizeof(NAME) == sizeof(int*)`. This is because `sizeof` evaluates the size of
the variable it's given; the first `NAME` is an array, while the second is a
pointer. Also, it's not possible to determine the size of dynamically allocated
memory (especially at compile-time when `sizeof` is evaluated).

### Getting and setting values

To set a value, use

```c
NAME[POS] = VAL;
```

Where `0 <= POS < n`.

Similarly, one can access a value using `NAME[POS];`.


## Efficiency

Retrieving and setting values can be done in O(1), since the position of the
value within the data structure (and within memory) can be calculated in
constant time. The location is computed by taking the memory location of the
beginning of the array, and adding `POS * sizeof(int)` to it.

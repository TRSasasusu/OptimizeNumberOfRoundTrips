# OptimizeNumberOfRoundTrips
Optimize number of round trips carrying weighted products by Dynamic Programming.

## Build

```
$ g++ dp.cpp -std=c++11
```

## Example I/O

```
$ ./a.out
number of products? 12
products?
46 46 11 11 11 11 11 11 11 11 11 11
max weight? 102
[{0,2,3,4,5,6,},{1,7,8,9,10,11,},]
```

```
$ ./a.out
number of products? 5
products?
10 20 1 50 45
max weight? 51
[{2,3,},{4,},{0,1,},]
```

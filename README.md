# Optimization turns out to be pessimization!

I have doing this optimization in my hobby OpenGL projects for years. My only sin is I did not measure their performance. I just assumed the one with less operation must be the faster one. Whenever a programmer wants to do get a fractional value of a maximum integer value, he/she cast the numerator and denominator to float before doing division and get the product of the division result and the max value and then cast back the result to integer. See below

```Cpp
// With float conversion
int value = (int)(((float)numerator / denominator) * max_value);
```

Being the smart ass I am, I get the product of max value and numerator before divided by denominator. In that way, I can get away with casting to float and back. but with this method, care must be taken that product of max value and numerator must never exceed the maximum limit of integer!

```Cpp
// Without float conversion
int value = max_value * numerator / denominator;
```

To my dismay, I discovered today that the one with float conversion is the faster one. The culprit could be integer division is several times slower than float division. See [Floating Point and Integer Arithmetic Benchmark](https://github.com/shaovoon/arithmeticbench)

It turns out that it is also the faster than a constant literal divisor.

```Cpp
// Without float conversion with constant divisor
int value = max_value * numerator / 1000;
```

```
C# 7, .NET Framework 4.6.1
===========================
                             With float conversion timing: 1827ms
                          Without float conversion timing: 2326ms
    Without float conversion with constant divisor timing: 1813ms

G++ 7.4.0, -O3
===========================
                             With float conversion timing:  298ms
                          Without float conversion timing: 2067ms
    Without float conversion with constant divisor timing:  869ms
	
Clang++ 6.0.0, -O3
===========================
                             With float conversion timing:  273ms
                          Without float conversion timing: 1169ms
    Without float conversion with constant divisor timing:  470ms

VC++, update 16.4, /Ox
===========================
                             With float conversion timing:  951ms
                          Without float conversion timing: 2087ms
    Without float conversion with constant divisor timing: 1022ms
```

The lesson here is to always measure, measure and measure!
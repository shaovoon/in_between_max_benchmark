# in_between_max_benchmark
Benchmark of calculating the in-between value of a max value.

```Cpp
// With float conversion
int value = (int)(((float)frac.numerator / frac.denominator) * max_value);

// Without float conversion
int value = max_value * frac.numerator / frac.denominator;

// Without float conversion with constant divisor
int value = max_value * frac.numerator / 1000;
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


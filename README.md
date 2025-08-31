### Introduction

Calculates a Legendre polynomial of the first kind, using Rodrigues Formula, up to an order of 255. And outputs the result as text.

While the max order of 255 seem sensible, it can easily be extended.

If the Integer library is replace with signed 64bit integers, the calculation of Legendre polynomials is limited to orders below 14.

##### Usage:

    #include "./legendre.hpp"

    Legendre::Coefficients(10);

Output:

    P(10,x) = 1/256 ( 46189 x^10 - 109395 x^8 + 90090 x^6 - 30030 x^4 + 3465 x^2 - 63 )

##### Note:

If the calculated coefficients are needed as signed integers, with X bits. The Legendre order is limited to a max of N.

| X bits | max N |
| -: | -: |
| 8 | 5 |
| 16 | 9 |
| 32 | 16 |
| 64 | 31 |
| 128 | 60 |
| 256 | 117 |

### Dependencies

- C++11

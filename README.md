# MicroProfiler
Tiny simple easy to use header-only profiler for C++ functions.

## Features

- Easy to use: Simply put `PRS` at the start of all functions you want to profile, or `PRST(x)` at the start of a block you want to profile.
- Call `Prof<>::Report();` when you're done accumulating measurements to print them out.
- Reset measurements: Call `Prof<>::Reset();` to clear the data and start measuring anew.
- Displays total and maximum time spent in a block/function
- Inner workings: Creates a tiny object, timer is started in the constructor, stopped in destructor, that is when the object goes out of scope. Thanks to that you don't need to hunt for all the `return`s to stop the timer.

## Installation

Just copy the .hpp file somewhere into your project.

## Example:

```cpp
#include "MicroProfiler.hpp"

SomeType GetAndProcessData() {
   PRS
   
   SomeType data;

   {
      PRST("Acquisition");
      data = acquire_data();
   }
   {
      PRST("Processing");
      data = process_data();
   }

   return data;
}


int main()
{

   do
   {
       MainLoop()
   }
   while(! UserExitRequested() );

   Proc<>::Report();
   return 0;
}
```

## Example output:
```
$ ./Bignum.exe
Randomness seeded to: 3971051981
                   operator>>= : tot.    2.0030512600s max    0.3294968296s
                   operator<<= : tot.    0.0005254500s max    0.0000009300s
                       qshiftr : tot.    0.0000001700s max    0.0000000500s
                       qshiftl : tot.    0.0002826600s max    0.0000008300s
                         Ltrim : tot.    0.0492305400s max    0.0000081100s
                       Reserve : tot.    0.0044128400s max    0.0000076500s
                    operator+= : tot.    0.0155464500s max    0.0000015800s
                    operator-= : tot.    1.1077280700s max    0.3294969096s
                    operator*= : tot.    0.0383068600s max    0.0000231800s
                          Zero : tot.    0.0085782000s max    0.0000084500s
                    operator>= : tot.    0.0524266500s max    0.0000085700s
                    operator<= : tot.    0.0000316300s max    0.0000000500s
                    operator== : tot.    0.0000436700s max    0.0000000500s
                    operator%= : tot.    5.4254838496s max    0.3297048096s
                        PowMod : tot.    6.0349004600s max    3.0149777500s
===============================================================================
```

## License

Public Domain. Do what you want.

Project Link: [https://github.com/your_username_/MicroProfiler](https://github.com/bwucke/MicroProfiler)

This document was created with help of phind.com AI assistant who has a rather rich imagination so if I missed some confabulation, my apologies.

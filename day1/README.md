# Benchmark results from 2022-12-01 on my machine:

```std::sort``` is faster than the first solution attempt for large $n \approx \text{elf count}$ and does not scale with the choice of $n$. The first solution attempt is faster than ```std::sort``` for small $n \ll \text{elf count}$, because we do not need to sort the whole array. 

```
$ ./benchmark.sh
---------------------------
1996 values, 253 elves, top 1
---------------------------
Sum: 69501
std::sort took 21 microseconds (236 total w/ printing)
Sum: 69501
the first attempt took 1 microseconds (178 total w/ printing)
---------------------------
1996 values, 253 elves, top 3
---------------------------
Sum: 202346
std::sort took 20 microseconds (218 total w/ printing)
Sum: 202346
the first attempt took 1 microseconds (217 total w/ printing)
---------------------------
1996 values, 253 elves, top 16
---------------------------
Sum: 977063
std::sort took 20 microseconds (219 total w/ printing)
Sum: 977063
the first attempt took 6 microseconds (206 total w/ printing)
---------------------------
1996 values, 253 elves, top 32
---------------------------
Sum: 1889140
std::sort took 20 microseconds (234 total w/ printing)
Sum: 1889140
the first attempt took 12 microseconds (219 total w/ printing)
---------------------------
1996 values, 253 elves, top 64
---------------------------
Sum: 3636309
std::sort took 21 microseconds (234 total w/ printing)
Sum: 3636309
the first attempt took 74 microseconds (310 total w/ printing)
---------------------------
1996 values, 253 elves, top 253
---------------------------
Sum: 11295745
std::sort took 21 microseconds (246 total w/ printing)
Sum: 11295745
the first attempt took 84 microseconds (332 total w/ printing)
```
[Try running the benchmark script.](benchmark.sh)

## Conner's Algorithms Library

This package contains a collection of nuanced high-performance implementations of algorithms
that often are considered "too theoretical" for common use. So many algorithms in common
CS curriculum are specified up to a description, but actual high-performance implementations
are hard to come by. This is exceptionally more prevalent for highly-theoretical approximation
and non-deterministic algorithms.

Please, feel free to extend and improve as desired! Additional algorithms and implementations
of the same agorithm can and should be added for comparison purposes. This project has the
second goal of exposing big-oh notation and giving practical performance measures of
popular algorithms.

### Directory Structure

Algorithms are classified accoring to:

- Problem Space (Array, Graph, Optimization, Optimzation, Sampling)
- Problem (K-Means, Graph Search, Knapsack, etc.)
- Type (Deterministic, Randomized, Approximate)
- Implementation (paper or id of this implementation)

Each problem space is given a separate folder in `src/` and each problem gets a separate .cpp
document in its specific folder. Multiple types and implementations are contained in a single
file.

Additionally, a separate document maintains an ordered list of theoretical time and space results,
along with additional reference materials.

### Testing

Testing is an important part of any software system. However, strict "correctness-of-algorithm" testing has been put to the backseat right now. In this package, testing most often takes the form of run-time analysis and noting performance as a function of randomly-generated input.

What this looks like in our case is, for each file `/src/<problemspace>/<problem>.cpp` file, there is a corresponding
`/test/<problemspace>/<problem>.cpp` that performs runtime testing for algorithms for that problem. Additionally, for each problemspace, there is a `/test/<problemspace>/generator.cpp` that generates samples from that problemspace to be used as input for the testing files.

Finally, at `/test/src/timer` we have implemented a convienent timing mechanism to compute the runtime of different algorithms. All these presently exists as convienent methods, but can be also run standalone to see comparisions between different algorithms.

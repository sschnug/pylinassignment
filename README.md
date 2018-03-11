# pylinassignment

## What is this
A proof-of-concept (rectangular) linear-assignment solver, which does:

- wrap a part of [Coin-OR Lemon (C++)](http://lemon.cs.elte.hu/trac/lemon) (very permissive license) using [pybind11](https://github.com/pybind/pybind11)
- formulate the (rectangular) linear-assignment problem as *minimum cost flow* problem (through *bipartite matching*)
  - theoretically this worsens asymptotic-complexity (it's a harder problem), but high-quality implementations often can compete / beat specialized algorithms (*hungarian-algorithm*)
  - allows to solve more general problems like incorporation of additional constraints (not implemented here)
- assume *intergral* costs (integers)
- use Lemon's *network-simplex* solver

Algorithmically *dense cost-matrices* are targeted!

## Status
It's just a proof-of-concept. It does not:

- check inputs
- return the assignment
  - easy to do; but i'm just interested in correct results (objective) and timings for now

## Example
Small example comparing this approach with scipy's solver based on the *hungarian-algorithm*:

    scipy small example: (3,3)

    scipy:  5
    Time (ns): network setup: 0
    Time (ns): network simplex: 0
    lemon:  (1, 5.0)

    Random example: (750,750)

    scipy:  -7467684  ->  26.511250686002313 secs
    Time (ns): network setup: 62
    Time (ns): network simplex: 106
    lemon:  (1, -7467684.0) ->  0.21490485699905548 secs

    Random example: (1000,1250)

    scipy:  -9979270  ->  110.49967523400119 secs
    Time (ns): network setup: 165
    Time (ns): network simplex: 81
    lemon:  (1, -9979270.0) ->  0.3604156650035293 secs

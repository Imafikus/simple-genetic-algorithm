# simple-genetic-algorithm
Simple GA, made for exercise.
It will be primary used for educative purposes.

Algorithm calculates sqare root of the number, and it doesn't really have fitness function.

Population is vector of chromosomes, and chromosomes are also vectors (of 0s and 1s)

Selection is ,,tournament based" which means that it takes random two chromosomes and picks one with the better fitness function.

Crossing over takes random pivot point, and two random vectors from population, then just exchanges bits starting from index zero to pivot.

Mutation takes one random vector from population and randomly changes single bit in that vector.

After these steps we will have new population, if chromosome from that populations satisfies the criterium, iterations are over, if not, process is repated with the new population.



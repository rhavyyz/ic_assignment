from genectic_algorithm import genetic_algorithm
import json, os


print(genetic_algorithm(1000, 0.1, 100, 100, 10))


solutions = []

for population_size in range(1, 2001):
    MUT_RATE = 0.05
    while MUT_RATE <= 1:
        
        for cut_size in range(2, population_size - 1):
            for max_gens in range (1, 2001):
                for T in range(0, 101):

                    try:
                        solutions += [[population_size, MUT_RATE, cut_size, max_gens, T],[genetic_algorithm(population_size, MUT_RATE, cut_size, max_gens, T) for x in range(10)]]
                    except Exception as e:
                        print(e, f"population {population_size}, MUT_RATE {MUT_RATE}, cut_size {cut_size}, max_gens {max_gens}, T {T}" )

                    if len(solutions) > 1e4:
                        with open(f"data/{ len(os.listdir("data"))  + 1}.json", "w") as f:
                            f.write(json.dumps(solutions))
                        solutions.clear() 
        MUT_RATE += 0.05


with open(f"data/{ len(os.listdir("data"))  + 1}.json", "w") as f:
    f.write(json.dumps(solutions))
solutions.clear() 

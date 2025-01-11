from utils import fitness, gen_element
from random import randint, random, choices

def crossover(parent1 : list[int], parent2 : list[int]) -> tuple[list[int], list[int]]:
    division = randint(1, len(parent1)-2)
    
    return [ parent1[:division] + parent2[division:], parent2[:division] + parent1[division:] ]


def init_population(size : int, continuous : bool) -> list[list[int]]:
    pop = []
    while len(pop) < size:
        pop.append(gen_element(100, continuous))
    return pop

def mutate(element : list[int], MUT_RATE : float) -> list[int]:
    cp = element[:]

    if random() <= MUT_RATE:
        cp[randint(0, len(element) - 1)] = randint(0, 1)
        
    return cp

def guess_max(population : list[list[int]], T : int):
    return len(population[0][0]) + (100 if T <= len(population[0][0])/2 else 0)

def reproduction_selector(population : list[list[int]], T : int):
    a, b = choices(population, weights=[p[1]/float(guess_max(population, T)) for p in population], k=2)
    return [a[0], b[0]]

def check(population : list[list[int]], T : int):
    return population[0][1] == guess_max(population, T)
def genetic_algorithm(population_size : int, MUT_RATE : float, cut_size, max_gens : int,  T : int) -> list[int]:
    population = [ ]
    while len(population) < population_size:
        p = gen_element(100, False)  
        population.append([p, fitness(p, T)])

    gen = 1

    while not check(population, T) and gen <= max_gens:
        gen+=1

        population = sorted(population, key= lambda x : x[1], reverse=True)[:cut_size]

        

        while len(population) < population_size:
            child1, child2 =  crossover(*reproduction_selector(population, T))
            child1 = mutate(child1, MUT_RATE)
            child2 = mutate(child2, MUT_RATE)

            population.append([child1, fitness(child1, T)])
            if population_size > len(population):
                population.append([child2, fitness(child2, T)])

    return [gen, check(population, T), [population[0][1], population[0][0]]]


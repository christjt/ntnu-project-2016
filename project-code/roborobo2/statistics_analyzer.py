import json
import os
import sys

results_folder = sys.argv[1]
out = sys.argv[2]


def analyze():
    generations = {}
    statistics_logs = os.listdir(results_folder)
    for log in statistics_logs:
        analyze_log(load_log(os.path.join(results_folder, log)), generations)

    return generations


def analyze_log(statistics, generations):
    for generation in statistics["generations"]:
        generation_num = generation["generation"]
        if generation_num in generations:
            generation_stats = generations[generation_num]
        else:
            generation_stats = Generation()
            generations[generation_num] = generation_stats

        fittest = find_fittest_individual(generation)

        generation_stats.energy_consumed_by_robot.append(fittest["energyConsumedByRobot"])
        generation_stats.energy_consumed_by_group.append(fittest["energyConsumedByGroup"])
        generation_stats.fitness.append(fittest["fitness"])
        generation_stats.predators_eaten.append(fittest["predatorsEaten"])
        generation_stats.robots_eaten.append(fittest["robotsEaten"])
        generation_stats.robots_starved.append(fittest["robotsStarvedToDeath"])


def load_log(log_name):
    with open(log_name, 'r') as f:
        statistics = json.loads(f.read())
    return statistics


def find_fittest_individual(generation):
    best_fitness = 0.0
    for individual in generation["genomes"]:
        for scenario in individual["scenarios"]:
            if scenario["fitness"] > best_fitness:
                best = scenario
    return best


class Generation:
    def __init__(self):
        self.energy_consumed_by_robot = []
        self.energy_consumed_by_group = []
        self.fitness = []
        self.predators_eaten = []
        self.robots_eaten = []
        self.robots_starved = []


generation_results = analyze()

result = {}
for i in generation_results:
    result[i] = generation_results[i].__dict__

json.dump(result, open(out, 'w'), indent=1)



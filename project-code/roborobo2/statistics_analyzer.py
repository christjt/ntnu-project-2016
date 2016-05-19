import json
import os
import sys
import math

results_folder = sys.argv[1]
out = sys.argv[2]


def analyze():
    generations = {}
    statistics_logs = os.listdir(results_folder)
    statistics_logs.sort()
    for log in statistics_logs:
        if log.endswith('.json'):
            print "Processing %s" % log
            analyze_log(load_log(os.path.join(results_folder, log)), generations, len(statistics_logs))

    return generations


def analyze_log(statistics, generations, n_trials):
    for generation in statistics["generations"]:
        generation_num = generation["generation"]
        if generation_num in generations:
            generation_stats = generations[generation_num]
        else:
            generation_stats = Generation()
            generations[generation_num] = generation_stats

        compute_property_statistics("energyConsumedByRobot", "energy_consumed_by_robot", generation_stats, generation, n_trials)
        compute_property_statistics("energyConsumedByGroup", "energy_consumed_by_group", generation_stats, generation, n_trials)
        compute_property_statistics("fitness", "fitness", generation_stats, generation, n_trials)
        compute_property_statistics("predatorsEaten", "predators_eaten", generation_stats, generation, n_trials)
        compute_property_statistics("robotsEaten", "robots_eaten", generation_stats, generation, n_trials)
        compute_property_statistics("robotsStarvedToDeath", "robots_starved", generation_stats, generation, n_trials)

        for individual in generation["genomes"]:
            for scenario in individual["scenarios"]:
                avg_number_of_groups = sum(snapshot["numberOfGroups"] for snapshot in scenario["groupSnapshots"])/200.0
                scenario["numberOfGroups"] = avg_number_of_groups
                sizes = [sum(snapshot["sizes"])/len(snapshot["sizes"]) for snapshot in scenario["groupSnapshots"]]
                scenario["sizes"] = sum(sizes)/len(sizes) if avg_number_of_groups > 0.0 else 0.0

        compute_property_statistics("numberOfGroups", "number_of_groups", generation_stats, generation, n_trials)
        compute_property_statistics("sizes", "group_size", generation_stats, generation, n_trials)


def compute_property_statistics(prop_name, target_prop, statistics, generation, n_trials):
    high = find_individual_with_highest(prop_name, generation)["scenarios"]
    low = find_individual_with_lowest(prop_name, generation)["scenarios"]

    n_scenarios = len(high)
    n_genomes = len(generation["genomes"])
    most = average(prop_name, high, n_scenarios)
    least = average(prop_name, low, n_scenarios)

    property_values = property_averages(prop_name, generation, n_scenarios)
    avg = generation_average(property_values, n_genomes)
    std_dev = standard_deviation(avg, property_values, n_genomes)

    average_prop = "average_" + target_prop
    most_prop = "most_" + target_prop
    least_prop = "least_" + target_prop
    std_dev_prop = "std_dev_" + target_prop

    setattr(statistics, average_prop, getattr(statistics, average_prop) + avg/n_trials)
    setattr(statistics, most_prop, getattr(statistics, most_prop) + most/n_trials)
    setattr(statistics, least_prop, getattr(statistics, least_prop) + least/n_trials)
    setattr(statistics, std_dev_prop, getattr(statistics, std_dev_prop) + std_dev/n_trials)


def generation_average(averages, n_genomes):
    return sum(averages)/n_genomes


def property_averages(prop, generation, n_scenarios):
    return [average(prop, genome["scenarios"], n_scenarios) for genome in generation["genomes"]]


def standard_deviation(mean, values, n):
    return math.sqrt((1.0/n)*sum([math.pow(val - mean, 2) for val in values]))


def average(prop, scenarios, length):
    return sum([scenario[prop] for scenario in scenarios])/length


def load_log(log_name):
    with open(log_name, 'r') as f:
        statistics = json.loads(f.read())
    return statistics


def compute_average_fitness(generation):
    genome_fitness = []
    for genome in generation["genomes"]:
        scenarios = genome["scenarios"]
        avg_scenario_fitness = sum([scenario["fitness"] for scenario in scenarios])/len(scenarios)
        genome_fitness.append(avg_scenario_fitness)

    return sum(genome_fitness)/len(genome_fitness)


def find_individual_with_highest(prop, generation):
    best_value = -10000.0
    for individual in generation["genomes"]:
        scenarios = individual["scenarios"]
        avg_property_value = sum([scenario[prop] for scenario in scenarios])/len(scenarios)
        if avg_property_value > best_value:
            best_value = avg_property_value
            best = individual
    return best


def find_individual_with_lowest(prop, generation):
    worst_value = 100000.0
    for individual in generation["genomes"]:
        scenarios = individual["scenarios"]
        avg_property_value = sum([scenario[prop] for scenario in scenarios])/len(scenarios)
        if avg_property_value < worst_value:
            worst_value = avg_property_value
            worst = individual
    return worst


class Generation:
    def __init__(self):

        self.average_energy_consumed_by_robot = 0.0
        self.most_energy_consumed_by_robot = 0.0
        self.least_energy_consumed_by_robot = 0.0
        self.std_dev_energy_consumed_by_robot = 0.0

        self.average_energy_consumed_by_group = 0.0
        self.most_energy_consumed_by_group = 0.0
        self.least_energy_consumed_by_group = 0.0
        self.std_dev_energy_consumed_by_group = 0.0

        self.most_fitness = 0.0
        self.least_fitness = 0.0
        self.average_fitness = 0.0
        self.std_dev_fitness = 0.0

        self.average_predators_eaten = 0.0
        self.most_predators_eaten = 0.0
        self.least_predators_eaten = 0.0
        self.std_dev_predators_eaten = 0.0

        self.average_robots_eaten = 0.0
        self.most_robots_eaten = 0.0
        self.least_robots_eaten = 0.0
        self.std_dev_robots_eaten = 0.0

        self.average_robots_starved = 0.0
        self.most_robots_starved = 0.0
        self.least_robots_starved = 0.0
        self.std_dev_robots_starved = 0.0

        self.average_number_of_groups = 0.0
        self.most_number_of_groups = 0.0
        self.least_number_of_groups = 0.0
        self.std_dev_number_of_groups = 0.0

        self.average_group_size = 0.0
        self.most_group_size = 0.0
        self.least_group_size = 0.0
        self.std_dev_group_size = 0.0


generation_results = analyze()

result = {}
for i in generation_results:
    result[i] = generation_results[i].__dict__

json.dump(result, open(out, 'w'), indent=1)



import json
import os
import sys
import math

results_folder = sys.argv[1]
out = sys.argv[2]
n = int(sys.argv[3])


def analyze():
    generations = {}
    best = Genome()
    statistics_logs = [log for log in os.listdir(results_folder) if log.endswith('.json')][:n]
    statistics_logs.sort()
    for log in statistics_logs:
        print "Processing %s" % log
        analyze_log(load_log(os.path.join(results_folder, log)), generations, len(statistics_logs), best)

    results = AnalyzedResults()
    results.best_genome = best
    results.statistics = generations
    return results


def analyze_log(statistics, generations, n_trials, best):
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

        best_snapshots = find_genome_with_most_grouped_robots(generation["genomes"])
        n_snapshots = len(best_snapshots)

        for snapshot in best_snapshots:
            if not snapshot:
                continue

            for size in snapshot["sizes"]:
                increment = 1.0/(float(n_snapshots)*n_trials)
                if size not in generation_stats.group_distribution:
                    generation_stats.group_distribution[size] = increment
                else:
                    generation_stats.group_distribution[size] += increment

        best_scenarios = find_individual_with_highest("fitness", generation)["scenarios"]
        fitness = average("fitness", best_scenarios, len(best_scenarios))
        if fitness > best.fitness:
            best.fitness = fitness
            best.weights = generation["best"]


def find_genome_with_most_grouped_robots(generation):
    most_robots = -1
    best_snapshots = None

    for genome in generation:
        best_snapshots = [find_snapshot_with_most_grouped_robots(scenario["groupSnapshots"]) for scenario in genome["scenarios"]]
        n_involved_robots = sum(snapshot[1] for snapshot in best_snapshots)

        if n_involved_robots > most_robots:
            most_robots = n_involved_robots
            best_snapshots = best_snapshots

    return [snapshot[0] for snapshot in best_snapshots]


def find_snapshot_with_most_grouped_robots(snapshots):
    most_robots = -1
    best_snapshot = None
    for snapshot in snapshots:
        involved_robots = sum(snapshot["sizes"])
        if involved_robots > most_robots:
            most_robots = involved_robots
            best_snapshot = snapshot

    return best_snapshot, most_robots


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
    return sum(averages)/float(n_genomes)


def property_averages(prop, generation, n_scenarios):
    return [average(prop, genome["scenarios"], n_scenarios) for genome in generation["genomes"]]


def standard_deviation(mean, values, n):
    return math.sqrt((1.0/n)*sum([math.pow(val - mean, 2) for val in values]))


def average(prop, scenarios, length):
    return sum([scenario[prop] for scenario in scenarios])/float(length)


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


class AnalyzedResults:
    def __init__(self):
        self.best_genome = None
        self.statistics = None


class Genome:
    def __init__(self):
        self.fitness = 0.0
        self.weights = []


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

        self.group_distribution = {}

generation_results = analyze()

result = {}
for i in generation_results.statistics:
    result[i] = generation_results.statistics[i].__dict__

result["best"] = generation_results.best_genome.__dict__

json.dump(result, open(out, 'w'), indent=1)



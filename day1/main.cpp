#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr char default_file[] = "day1/input.txt";
constexpr size_t default_sizeof_toplist = 3;
constexpr size_t sizeof_line = 32;

int
main(int argc, char *argv[])
{
	//* open the file
	printf("Usage: main [n] [input (Default: \"%s\")]\n", default_file);
	size_t sizeof_toplist = argc > 1 ? atoi(argv[1]) : default_sizeof_toplist;
	FILE *const input_file = fopen(argc > 2 ? argv[2] : default_file, "r");

	if (input_file != NULL) {
		printf("Opened %s\n", argc > 2 ? argv[2] : default_file);
	} else {
		perror("Error opening file");
	}

	//* read the file
	size_t i = 0;
	std::vector<int> list;
	std::vector<size_t> elf_idx;
	char line[sizeof_line];

	while (fgets(line, sizeof_line, input_file) != NULL) {
		if (line[0] != '\n') {
			++i;
			static int d;
			sscanf(line, "%d", &d);
			list.push_back(d);
		} else {
			elf_idx.push_back(i);
		}
	}
	elf_idx.push_back(i);
	const size_t list_size = i;
	const size_t elf_count = elf_idx.size() - 1; //* -1 because of the last
	size_t *const elf_load = new size_t[elf_count];
	sizeof_toplist = sizeof_toplist > elf_count ? elf_count : sizeof_toplist;

	for (size_t i = 0; i < elf_count; ++i) {
		elf_load[i] = 0;

		for (size_t j = elf_idx[i]; j < elf_idx[i + 1]; ++j) {
			elf_load[i] += list[j];
		}
	}
	printf("---------------------------------\n");
	printf("%llu values, %llu elves, top %llu\n", list_size, elf_count, sizeof_toplist);
	printf("---------------------------------\n");

	/*
	 * std::sort --- The correct way? (depends)
	 *
	 * std::sort is faster than the first solution attempt for large n ~= elf count,
	 * which is probably known sorting algorithm in disguise. See README.md
	 */
	{
		const auto start = std::chrono::high_resolution_clock::now();

		std::sort(elf_load, elf_load + elf_count, std::greater<size_t>()); //* <---
		const auto end_1 = std::chrono::high_resolution_clock::now();

		size_t toplist_sum = 0;

		for (size_t i = 0; i < sizeof_toplist; ++i) {
			toplist_sum += elf_load[i];
			// printf("%d ", elf_load[i]);
		}
		printf("Sum: %llu\n", toplist_sum);
		const auto end_2 = std::chrono::high_resolution_clock::now();
		const auto diff_1 =
		    std::chrono::duration_cast<std::chrono::microseconds>(end_1 - start);
		const auto diff_2 =
		    std::chrono::duration_cast<std::chrono::microseconds>(end_2 - end_1);
		printf("std::sort took %llu microseconds (%llu total w/ printing)\n",
		       diff_1.count(), diff_1.count() + diff_2.count());
	}
	/*
	 * the first solution attempt --- What I did at first
	 *
	 * The first solution attempt is faster than std::sort for small n << elf count,
	 * because we don't have to sort the whole array. See README.md
	 */
	{
		const auto start = std::chrono::high_resolution_clock::now();
		size_t *const toplist = new size_t[sizeof_toplist];
		toplist[0] = 0;

		for (size_t i = 0; i < elf_count; ++i) { //* <---
			for (size_t j = 0; j < sizeof_toplist; ++j) {
				if (elf_load[i] > toplist[j]) {
					for (size_t k = sizeof_toplist - 1; k > j; --k) {
						toplist[k] = toplist[k - 1];
					}
					toplist[j] = elf_load[i];
					break;
				}
			}
		}
		const auto end_1 = std::chrono::high_resolution_clock::now();

		size_t toplist_sum = 0;

		for (size_t i = 0; i < sizeof_toplist; ++i) {
			toplist_sum += toplist[i];
			// printf("%d ", toplist[i]);
		}
		printf("Sum: %llu\n", toplist_sum);
		const auto end_2 = std::chrono::high_resolution_clock::now();
		const auto diff_1 =
		    std::chrono::duration_cast<std::chrono::microseconds>(end_1 - start);
		const auto diff_2 =
		    std::chrono::duration_cast<std::chrono::microseconds>(end_2 - end_1);
		printf("the first attempt took %llu microseconds (%llu total w/ printing)\n",
		       diff_1.count(), diff_1.count() + diff_2.count());
	}
	/*
	 * End of the first solution attempt
	 */

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}
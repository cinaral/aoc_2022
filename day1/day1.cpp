#include "read_file.hpp"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr char dflt_file[] = "day1/input.txt";
constexpr size_t dflt_toplist_size = 3;
constexpr size_t line_buf_size = 64;
using Val_T = unsigned;

int
main(int argc, char *argv[])
{
	//* open and read the file
	printf("Usage: main [n] [input (Default: \"%s\")]\n", dflt_file);
	size_t toplist_size = argc > 1 ? atoi(argv[1]) : dflt_toplist_size;
	FILE *const input_file = fopen(argc > 2 ? argv[2] : dflt_file, "r");

	if (input_file != NULL) {
		printf("Opened %s\n", argc > 2 ? argv[2] : dflt_file);
	} else {
		perror("Error opening file");
	}
	std::vector<std::vector<char>> rows;
	std::vector<size_t> col_sizes;
	std::vector<size_t> grp_end_idx;
	read_file<line_buf_size>(input_file, rows, col_sizes, grp_end_idx);

	//* parse the lines and groups
	std::vector<std::vector<Val_T>> vals_in_grps;

	for (size_t i = 0; i < grp_end_idx.size(); ++i) {
		//* iterate over groups...
		const size_t grp_start_idx = i == 0 ? 0 : grp_end_idx[i - 1];
		std::vector<Val_T> vals;
		// printf("Group %zu: ", i);

		for (size_t j = grp_start_idx; j < grp_end_idx[i]; ++j) {
			//* iterate over lines in group...
			const size_t line_len = col_sizes[j];
			char str[line_buf_size];
			// printf("[%zu]", j);

			for (size_t k = 0; k < line_len; ++k) {
				//* iterate over characters in line...
				str[k] = rows[j][k];
				// printf("%c", line_arr[j][k]);
			}
			str[line_len] = '\0';        //* null termination
			const Val_T val = atoi(str); //* parse into value if needed
			vals.push_back(val);
			// printf("%s(%d)", str, val);
		}
		vals_in_grps.push_back(vals);
		// printf("\n");
	}
	printf("\n");

	const size_t elf_count = vals_in_grps.size();

	//* find the top n elves
	Val_T *const elf_cal = new Val_T[elf_count];
	toplist_size = toplist_size > elf_count ? elf_count : toplist_size;

	for (size_t i = 0; i < elf_count; ++i) {
		elf_cal[i] = 0;

		for (auto j : vals_in_grps[i]) {
			elf_cal[i] += j;
		}
	}
	printf("---------------------------\n");
	printf("%zu elves, calories top %zu\n", elf_count, toplist_size);
	printf("----------------------------\n");

	/*
	 * std::sort --- The correct way? (depends)
	 *
	 * std::sort is faster than the first solution attempt for large n ~= elf count,
	 * which is probably known sorting algorithm in disguise. See README.md
	 */
	{
		const auto start = std::chrono::high_resolution_clock::now();
		std::sort(elf_cal, elf_cal + elf_count, std::greater<Val_T>()); //* <---
		Val_T toplist_sum = 0;

		for (size_t i = 0; i < toplist_size; ++i) {
			toplist_sum += elf_cal[i];
			// printf("(%zu)%u ", i + 1, elf_loads[i]);
		}
		const auto end = std::chrono::high_resolution_clock::now();
		const auto diff =
		    std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		printf("sum: %u, using std::sort took %llu microseconds\n", toplist_sum,
		       diff.count());
	}
	/*
	 * the first solution attempt --- What I did at first
	 *
	 * The first solution attempt is faster than std::sort for small n << elf count,
	 * because we don't have to sort the whole array. See README.md
	 */
	{
		const auto start = std::chrono::high_resolution_clock::now();
		Val_T *const toplist = new Val_T[toplist_size];
		toplist[0] = 0;

		for (size_t i = 0; i < elf_count; ++i) { //* <---
			for (size_t j = 0; j < toplist_size; ++j) {
				if (elf_cal[i] > toplist[j]) {
					for (size_t k = toplist_size - 1; k > j; --k) {
						toplist[k] = toplist[k - 1];
					}
					toplist[j] = elf_cal[i];
					break;
				}
			}
		}
		Val_T toplist_sum = 0;

		for (size_t i = 0; i < toplist_size; ++i) {
			toplist_sum += elf_cal[i];
			// printf("(%zu)%u ", i + 1, elf_loads[i]);
		}
		const auto end = std::chrono::high_resolution_clock::now();
		const auto diff =
		    std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		printf("sum: %u, using the first attempt took %llu microseconds\n", toplist_sum,
		       diff.count());
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
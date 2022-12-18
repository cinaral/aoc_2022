#include "read_file.hpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr char default_file[] = "day5/input.txt";
constexpr size_t line_buf_size = 64;
constexpr size_t crate_width = 4;
constexpr size_t crate_shift = 1;
using Ccol_T = std::vector<char>; //* a column of boxes

int
main(int argc, char *argv[])
{
	//* open and read the file
	printf("Usage: main [input (Default: \"%s\")]\n", default_file);
	FILE *const input_file = fopen(argc > 1 ? argv[1] : default_file, "r");

	if (input_file != NULL) {
		printf("Opened %s\n", argc > 1 ? argv[1] : default_file);
	} else {
		perror("Error opening file");
	}
	std::vector<std::vector<char>> rows;
	std::vector<size_t> col_sizes;
	std::vector<size_t> grp_end_idx;
	read_file<line_buf_size>(input_file, rows, col_sizes, grp_end_idx);

	//* parse the lines and groups
	std::vector<Ccol_T> crates_a; //* crate columns, part a
	std::vector<Ccol_T> crates_b; //* crate columns, part b

	for (size_t i_grp = 0; i_grp < grp_end_idx.size(); ++i_grp) {
		//* iterate over groups...
		const auto grp_start_idx = i_grp == 0 ? 0 : grp_end_idx[i_grp - 1];
		// printf("Group %zu:\n", i_grp);

		for (size_t j_row = grp_start_idx; j_row < grp_end_idx[i_grp]; ++j_row) {
			//* iterate over lines in group...
			const auto col_size = col_sizes[j_row];
			char str[line_buf_size];

			if (i_grp < 1) {
				size_t k_crate = 0;

				for (size_t k_col = crate_shift; k_col < col_size;
				     k_col += crate_width) {
					auto crate = rows[j_row][k_col];

					if (crate == '1') {
						break; //* skip numbers
					}

					if (k_crate >= crates_a.size()) {
						auto ccol = std::vector<char>{crate};
						crates_a.push_back(ccol);
					} else {
						crates_a[k_crate].push_back(crate);
					}
					//* iterate over characters in line...
					const char c = rows[j_row][k_col];
					str[k_col] = c;
					++k_crate;
				}
			} else {
				for (size_t k_col = 0; k_col < col_size; ++k_col) {
					//* iterate over characters in line...
					const char c = rows[j_row][k_col];
					str[k_col] = c;
				}
				//* add null termination char
				str[col_size] = '\0';

				//* move the boxes
				static unsigned num, from, dest;
				sscanf(str, "move %u from %u to %u\n", &num, &from, &dest);

				//* part a
				for (size_t l = 0; l < num; ++l) {
					crates_a[dest - 1].push_back(crates_a[from - 1].back());
					crates_a[from - 1].pop_back();
				}

				//* part b
				std::vector<char> crane;
				for (size_t l = 0; l < num; ++l) {
					crane.push_back(crates_b[from - 1].back());
					crates_b[from - 1].pop_back();
				}
				std::reverse(crane.begin(), crane.end());

				for (auto i : crane) {
					crates_b[dest - 1].push_back(i);
				}
				// printf("move %u from %u to %u\n", num, from, dest);
				// for (auto i : crates_a) {
				//	for (auto j : i) {
				//		printf("%c", j);
				//	}
				//	printf("\n");
				// }
			}
			if (i_grp < 1 && j_row == grp_end_idx[i_grp] - 1) {
				const size_t ccol_size = crates_a.size();
				for (size_t i = 0; i < ccol_size; ++i) {
					//* reverse the vector
					std::reverse(crates_a[i].begin(), crates_a[i].end());
					//* and remove air
					while (crates_a[i].back() == ' ') {
						crates_a[i].pop_back();
					}
				}
				//* make a copy for part b
				std::copy(crates_a.begin(), crates_a.end(),
				          std::back_inserter(crates_b));
			}
		}
	}
	printf("CrateMover 9000: ");
	for (auto i : crates_a) {
		printf("%c", i.back());
	}
	printf("\n");

	printf("CrateMover 9001: ");
	for (auto i : crates_b) {
		printf("%c", i.back());
	}
	printf("\n");

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}
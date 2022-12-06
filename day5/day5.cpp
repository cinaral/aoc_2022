#include "read_file.hpp"
#include <array>
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
	std::vector<Ccol_T> crates; //* create columns

	for (size_t i_grp = 0; i_grp < grp_end_idx.size(); ++i_grp) {
		//* iterate over groups...
		const auto grp_start_idx = i_grp == 0 ? 0 : grp_end_idx[i_grp - 1];
		printf("Group %zu: ", i_grp);

		for (size_t j_row = grp_start_idx; j_row < grp_end_idx[i_grp]; ++j_row) {
			//* iterate over lines in group...
			const auto col_size = col_sizes[j_row];
			char str[line_buf_size];
			printf("\n");

			if (i_grp < 1) {
				size_t k_crate = 0;

				for (size_t k_col = crate_shift; k_col < col_size;
				     k_col += crate_width) {
					auto crate = rows[j_row][k_col];

					if (k_crate >= crates.size()) {
						crates.push_back(std::vector<char>{crate});
					} else {
						auto it = crates.begin();
						auto c = std::vector<char>{crate};
						crates[k_crate].insert(it + j_row, c .end());
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
				////* add null termination char
				// str[col_size] = '\0';
				printf("%-32s", str);
				////* convert to val if needed
				// static unsigned num, from, dest;
				// sscanf(str, "move %u from %u to %u\n", &num, &from, &dest);
				// printf("move %u from %u to %u", num, from, dest);
				// const auto from_idx = (from - 1) * crate_width + crate_shift;
				// const auto dest_idx = (dest - 1) * crate_width + crate_shift;

				// for (size_t l = 0; l < num - 1; ++l) {
				//	crates[dest_idx].push_back(crates[from_idx].back());
				//	crates[from_idx].pop_back();
				// }
			}

			if (i_grp < 1) {
				for (auto i : crates) {
					for (auto j : i) {
						printf("%c", j);
					}
				}
			}
		}
		printf("\n");
	}
	printf("\n");

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}
#include "read_file.hpp"
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <vector>

constexpr char default_file[] = "day6/input.txt";
constexpr size_t line_buf_size = 4096; //* max line length
constexpr size_t marker_size = 14;
using Val_T = unsigned long long;


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

	for (size_t i_grp = 0; i_grp < grp_end_idx.size(); ++i_grp) {
		//* iterate over groups...
		const auto grp_start_idx = i_grp == 0 ? 0 : grp_end_idx[i_grp - 1];
		printf("Message Index(es) of  Group %zu:\n", i_grp);

		for (size_t j_row = grp_start_idx; j_row < grp_end_idx[i_grp]; ++j_row) {
			//* iterate over lines in group...
			const auto col_size = col_sizes[j_row];
			std::deque<char> char_hist;
			unsigned dropped_chars = 0;

			for (size_t k_col = 0; k_col < col_size; ++k_col) {
				//* iterate over characters in line...
				const char c = rows[j_row][k_col];

				for (size_t i = 0; i < char_hist.size(); ++i) {
					if (c == char_hist[i]) {
						//* count dropped chars
						for (size_t j = 0; j < i + 1; ++j) {
							char_hist.pop_front();
							++dropped_chars;
						}
					}
				}
				char_hist.push_back(c);

				if (char_hist.size() >= marker_size) {
					printf("%zu", dropped_chars + marker_size);
					printf("[");

					for (size_t i = 0; i < marker_size; ++i) {
						printf("%c", char_hist[i]);
					}
					printf("] ");
					break;
				}
			}
		}
		printf("\n");
	}printf("\n");
	printf("\n");

	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}

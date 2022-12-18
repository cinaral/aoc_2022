/*
 * template_cpp_project
 *
 * MIT License
 *
 * Copyright (c) 2022 Cinar, A. L.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef READ_FILE_HPP_CINARAL_221204_1924
#define READ_FILE_HPP_CINARAL_221204_1924

#include <cstdio>
#include <cstdlib>
#include <vector>

/*
 * Read a file into multiple vectors to identify non-empty rows, column sizes and line grouping.
 *
 * `read_file(input_file, OUT:rows, OUT:col_sizes, OUT:grp_end_idx)`
 *
 * 1. `input_file`: input file
 *
 * OUT:
 * 2. `rows`: non-empty lines
 * 3. `col_sizes`: column size of each row (row length)
 * 4. `grp_end_idx`: index of the last row of each non-empty block followed by newline(s)
 */

template <size_t BUF_SIZE>
inline void
read_file(FILE *const input_file, std::vector<std::vector<char>> &rows,
          std::vector<size_t> &col_sizes, std::vector<size_t> &grp_end_idx)
{
	if (input_file != NULL) {
		static char line_buf[BUF_SIZE];
		size_t row_counter = 0;

		while (fgets(line_buf, BUF_SIZE, input_file) != NULL) {
			std::vector<char> line;

			for (size_t i = 0; i < BUF_SIZE; ++i) {
				if (line_buf[i] == '\n' || line_buf[i] == '\0') {
					if (i > 0) { //* if line is not empty
						++row_counter;
						rows.push_back(line);
						col_sizes.push_back(i);
					} else {
						if (grp_end_idx.size() == 0 ||
						    row_counter != grp_end_idx.back()) {
							//* empty line following a non-empty line...
							grp_end_idx.push_back(row_counter);
						}
					}
					break; //* stop reading the line
				} else {
					line.push_back(line_buf[i]);
				}
			}
		}
		if (row_counter > 0) { //* if the first line is non-empty
			grp_end_idx.push_back(row_counter);
		}
		const size_t grp_size = grp_end_idx.size();
		const size_t row_size = row_counter;
		printf("Read %zu row(s) in %zu group(s).\n", row_size, grp_size);
	} else {
		perror("No file to read");
	}
}

#endif
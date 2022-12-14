#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr char default_file[] = "day2/input.txt";
constexpr size_t sizeof_line = 32;

int
main(int argc, char *argv[])
{
	//* open the file
	printf("Usage: main [input (Default: \"%s\")]\n", default_file);
	FILE *const input_file = fopen(argc > 1 ? argv[1] : default_file, "r");

	if (input_file != NULL) {
		printf("Opened %s\n", argc > 1 ? argv[1] : default_file);
	} else {
		perror("Error opening file");
	}

	//* read the file
	size_t i = 0;
	std::vector<char> theirs;
	std::vector<char> ours;
	char line[sizeof_line];

	while (fgets(line, sizeof_line, input_file) != NULL) {
		if (line[0] != '\n') {
			++i;
			static char their;
			static char our;
			sscanf(line, "%c %c", &their, &our);
			theirs.push_back(their);
			ours.push_back(our);
		}
	}
	const size_t move_count = i;

	{
		int total_score = 0;

		for (size_t i = 0; i < move_count; ++i) {
			switch (ours[i]) {
			case 'X':
				total_score += 6;
				break;
			case 'Y':
				total_score += 3;
				break;
			case 'Z':
				total_score += 0;
				break;
			default:
				break;
			}
			switch (theirs[i]) {
			case 'A':
				if (ours[i] == 'Y') {
					total_score += 6;
				} else if (ours[i] == 'X') {
					total_score += 3;
				}
				break;
			case 'B':
				if (ours[i] == 'Z') {
					total_score += 6;
				} else if (ours[i] == 'Y') {
					total_score += 3;
				}

				break;
			case 'C':
				if (ours[i] == 'X') {
					total_score += 6;
				} else if (ours[i] == 'Z') {
					total_score += 3;
				}
				break;
			default:
				break;
			}
		}
		printf("score a %d\n", total_score);
	}
	{
		int total_score = 0;

		for (size_t i = 0; i < move_count; ++i) {

			switch (ours[i]) {
			case 'Z':
				total_score += 6;
				break;
			case 'Y':
				total_score += 3;
				break;
			case 'X':
				total_score += 0;
				break;
			default:
				break;
			}
			switch (theirs[i]) {
			case 'A':
				switch (ours[i]) {
				case 'Z':
					total_score += 2;
					break;
				case 'Y':
					total_score += 1;
					break;
				case 'X':
					total_score += 3;
					break;
				default:
					break;
				}
				break;
			case 'B':
				switch (ours[i]) {
				case 'Z':
					total_score += 3;
					break;
				case 'Y':
					total_score += 2;
					break;
				case 'X':
					total_score += 1;
					break;
				default:
					break;
				}
				break;
			case 'C':
				switch (ours[i]) {
				case 'Z':
					total_score += 1;
					break;
				case 'Y':
					total_score += 3;
					break;
				case 'X':
					total_score += 2;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		printf("score b %d\n", total_score);
		//* process
	}
	//* close the file
	if (fclose(input_file) != 0) {
		perror("Error closing file");
	}
	return 0;
}
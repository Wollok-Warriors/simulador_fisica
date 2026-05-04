#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	const char *name;
	const char *description;
	const char *binary;
} Simulation;

static const Simulation sims[] = {
	{ "atwood",      "Atwood machine — two masses over a pulley", "build/atwood"      },
	{ "block_slope", "Block on slope — friction & force vectors", "build/block_slope" },
};

static const int SIM_COUNT = sizeof(sims) / sizeof(sims[0]);


static void print_menu(void) {
	printf("\n║   Physics Simulator   ║\n");
	for (int i = 0; i < SIM_COUNT; i++)
		printf("  [%d] %-14s — %s\n", i + 1, sims[i].name, sims[i].description);
	printf("  [0] exit\n\n");
	printf("Pick Scenario: ");
}

static void run(const Simulation *s) {
	printf("\nOpening '%s'...\n\n", s->name);
	int ret = system(s->binary);
	if (ret != 0)
		fprintf(stderr, "Error: '%s' ended with code %d\n", s->binary, ret);
}

int main(void) {
	int choice;

	while (1) {
		print_menu();

		if (scanf("%d", &choice) != 1) {
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);
			printf("Invalid entry, enter a number.\n");
			continue;
		}

		if (choice == 0) {
			printf("Bye.\n\n");
			break;
		}

		if (choice < 1 || choice > SIM_COUNT) {
			printf("Invalid option, choose between 0, %d.\n", SIM_COUNT);
			continue;
		}

		run(&sims[choice - 1]);
	}

	return 0;
}

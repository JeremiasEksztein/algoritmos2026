#ifndef TEST_H
#define TEST_H

#include <string.h>
#include <stdio.h>

typedef struct {
	char cpu[21];
	char gpu[21];
	char ram[21];
	size_t mips;
} Computer;

int computer_seed_arr(Computer *arr, size_t n);

int computer_eq(const Computer *lhs, const Computer *rhs)
{
	return (memcmp(lhs->cpu, rhs->cpu, sizeof(Computer))) ? 0 : 1;
}

void computer_show(const Computer *c)
{
	printf("CPU: %s\tGPU: %s\tRAM: %s\tMIPS: %lu\n", c->cpu, c->gpu, c->ram, c->mips);
}

int computer_cmp(const void *lhs, const void *rhs)
{
	const Computer *a = lhs;
	const Computer *b = rhs;

	return strcmp(a->ram, b->ram);
}

static Computer arr[50] = {
    {"Intel i3-8100", "GTX 1050", "8GB", 1000},
    {"Intel i5-8400", "GTX 1060", "16GB", 1500},
    {"Intel i7-8700", "RTX 2060", "16GB", 2000},
    {"Intel i9-9900K", "RTX 2080", "32GB", 3000},
    {"Ryzen 3 2200G", "Vega 8", "8GB", 900},
    {"Ryzen 5 2600", "RX 580", "16GB", 1400},
    {"Ryzen 7 2700X", "RX 5700", "16GB", 2100},
    {"Ryzen 9 3900X", "RTX 3080", "32GB", 3500},
    {"Intel i3-10100", "GTX 1650", "8GB", 1100},
    {"Intel i5-10400", "GTX 1660", "16GB", 1600},

    {"Intel i7-10700K", "RTX 2070", "16GB", 2200},
    {"Intel i9-10900K", "RTX 2080 Ti", "32GB", 3200},
    {"Ryzen 3 3100", "GTX 1050 Ti", "8GB", 1000},
    {"Ryzen 5 3600", "RTX 2060", "16GB", 1800},
    {"Ryzen 7 3700X", "RTX 2070", "16GB", 2300},
    {"Ryzen 9 3950X", "RTX 3090", "64GB", 4000},
    {"Intel i3-12100", "GTX 1650", "8GB", 1200},
    {"Intel i5-12400", "RTX 3060", "16GB", 2000},
    {"Intel i7-12700K", "RTX 3070", "32GB", 2800},
    {"Intel i9-12900K", "RTX 3080 Ti", "32GB", 3600},

    {"Ryzen 5 5600X", "RTX 3060 Ti", "16GB", 2200},
    {"Ryzen 7 5800X", "RTX 3070", "32GB", 2700},
    {"Ryzen 9 5900X", "RTX 3080", "32GB", 3500},
    {"Ryzen 9 5950X", "RTX 3090", "64GB", 4200},
    {"Intel i3-13100", "GTX 1660", "8GB", 1300},
    {"Intel i5-13400", "RTX 3050", "16GB", 2100},
    {"Intel i7-13700K", "RTX 4070", "32GB", 3000},
    {"Intel i9-13900K", "RTX 4090", "64GB", 4500},
    {"Ryzen 5 7600", "RTX 4060", "16GB", 2400},
    {"Ryzen 7 7700X", "RTX 4070 Ti", "32GB", 3100},

    {"Ryzen 9 7900X", "RTX 4080", "32GB", 3800},
    {"Ryzen 9 7950X", "RTX 4090", "64GB", 4600},
    {"Intel i5-9600K", "GTX 1070", "16GB", 1700},
    {"Intel i7-9700K", "RTX 2060", "16GB", 2100},
    {"Intel i9-9900KS", "RTX 2080", "32GB", 3300},
    {"Ryzen 5 1600", "RX 570", "8GB", 800},
    {"Ryzen 7 1700", "RX 580", "16GB", 1200},
    {"FX-8350", "GTX 970", "8GB", 700},
    {"Pentium G4560", "GT 1030", "4GB", 500},
    {"Celeron G3930", "iGPU", "4GB", 300},

    {"Apple M1", "Integrated", "8GB", 2500},
    {"Apple M2", "Integrated", "16GB", 3000},
    {"Apple M3", "Integrated", "24GB", 3800},
    {"Xeon E5-2670", "Quadro K2200", "32GB", 2000},
    {"Xeon W-2295", "RTX A4000", "64GB", 3500},
    {"Threadripper 2950X", "RTX 2080", "64GB", 3700},
    {"Threadripper 3990X", "RTX 3090", "128GB", 5000},
    {"Atom x5-Z8350", "iGPU", "2GB", 200},
    {"Core 2 Duo E8400", "GT 710", "4GB", 400},
    {"Core 2 Quad Q6600", "GTX 750", "8GB", 600}
};

#endif

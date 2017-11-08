#include <AOS-unix/printk.h>
#include <AOS-unix/cpuid.h>

/* получаем всю информацию о cpu */
int print_info_cpu()
{
	unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);
	switch (ebx) {
		case MAGIC_INTEL:	/* Intel Magic Code */
			print_intel();
			break;
		
		case MAGIC_AMD:		/* AMD Magic Code */
			print_amd();
			break;
		
		default:
			printk("Unknown x86 CPU Detected\n");
			break;
	}

	return 0;
}

/* список Intel */
char *Intel[] = {
	"Brand ID Not Supported.", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Intel(R) Pentium(R) III Xeon(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) III processor-M", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Xeon(R) Processor", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) 4 processor-M", 
	"Mobile Intel(R) Pentium(R) Celeron(R) processor", 
	"Reserved", 
	"Mobile Genuine Intel(R) processor", 
	"Intel(R) Celeron(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Celeron(R) processor", 
	"Mobile Geniune Intel(R) processor", 
	"Intel(R) Pentium(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor"
};

/* Архитектура процессора */
char *Intel_Other[] = {
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Celeron(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved"
};

/* информация об Intel */
int print_intel(void)
{
	printk("Intel Specific Features:\n");
	unsigned long eax, ebx, ecx, edx, max_eax, signature, unused;
	int model, family, type, brand, stepping, reserved;
	int extended_family = -1;
	cpuid(1, eax, ebx, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	type = (eax >> 12) & 0x3;
	brand = ebx & 0xff;
	stepping = eax & 0xf;
	reserved = eax >> 14;
	signature = eax;

	printk("Type %d - ", type);

	switch (type) {
		case 0:
			printk("Original OEM");
			break;
		
		case 1:
			printk("Overdrive");
			break;
		
		case 2:
			printk("Dual-capable");
			break;
		
		case 3:
			printk("Reserved");
			break;
	}

	printk("\nFamily %d - ", family);

	switch (family) {
		case 3:
			printk("i386");
			break;
		
		case 4:
			printk("i486");
			break;
		
		case 5:
			printk("Pentium");
			break;
		
		case 6:
			printk("Pentium Pro");
			break;
		
		case 15:
			printk("Pentium 4");
	}

	printk("\n");
	if (family == 15) {
		extended_family = (eax >> 20) & 0xff;
		printk("Extended family %d\n", extended_family);
	}

	printk("Model %d - ", model);
	
	switch (family) {
		case 3:
			break;
		
		case 4:
			switch(model) {
				case 0:
				case 1:
					printk("DX");
					break;
			
				case 2:
					printk("SX");
					break;
			
				case 3:
					printk("487/DX2");
					break;
			
				case 4:
					printk("SL");
					break;
			
				case 5:
					printk("SX2");
					break;
			
				case 7:
					printk("Write-back enhanced DX2");
					break;
			
				case 8:
					printk("DX4");
					break;
			}
			break;

		case 5:
			switch(model) {
				case 1:
					printk("60/66");
					break;
			
				case 2:
					printk("75-200");
					break;
			
				case 3:
					printk("for 486 system");
					break;
			
				case 4:
					printk("MMX");
					break;
			}
			break;
		case 6:
			switch(model) {
				case 1:
					printk("Pentium Pro");
					break;
			
				case 3:
					printk("Pentium II Model 3");
					break;
			
				case 5:
					printk("Pentium II Model 5/Xeon/Celeron");
					break;
			
				case 6:
					printk("Celeron");
					break;
			
				case 7:
					printk("Pentium III/Pentium III Xeon - external L2 cache");
					break;
			
				case 8:
					printk("Pentium III/Pentium III Xeon - internal L2 cache");
					break;
			}
			break;
		
		case 15:
			break;
	}

	printk("\n");
	cpuid(0x80000000, max_eax, unused, unused, unused);
	/**
	 	Если максимальное расширенное значение eax достаточно велико, чтобы поддерживать строку бренда процессора
		(значения 0x80000002 до 0x80000004), то мы будем использовать эту информацию, чтобы вернуть информацию о бренде.
		В противном случае мы вернемся к таблицам брендов выше для обратной совместимости со старыми процессорами.
		Согласно Руководству разработчика программного обеспечения Intel, если поддерживаются расширенные значения eax,
		то все 3 значения для строки бренда процессора поддерживаются, но мы будем проверять, чтобы убедиться и быть в безопасности. 
	 **/
	if (max_eax >= 0x80000004) {
		printk("Brand: ");

		if (max_eax >= 0x80000002) {
			cpuid(0x80000002, eax, ebx, ecx, edx);
			print_regs(eax, ebx, ecx, edx);
		}
		if (max_eax >= 0x80000003) {
			cpuid(0x80000003, eax, ebx, ecx, edx);
			print_regs(eax, ebx, ecx, edx);
		}
		if (max_eax >= 0x80000004) {
			cpuid(0x80000004, eax, ebx, ecx, edx);
			print_regs(eax, ebx, ecx, edx);
		}

		printk("\n");

	} else if (brand > 0) {
		printk("Brand %d - ", brand);

		if (brand < 0x18) {
			if (signature == 0x000006B1 || signature == 0x00000F13) {
				printk("%s\n", Intel_Other[brand]);
			} else {
				printk("%s\n", Intel[brand]);
			}
		} else {
			printk("Reserved\n");
		}
	}

	printk("Stepping: %d Reserved: %d\n", stepping, reserved);
	
	return 0;
}

/* печатаем регистры */
void print_regs(int eax, int ebx, int ecx, int edx) {
	int j;
	char string[17];
	string[16] = '\0';

	for (j = 0; j < 4; j++) {
		string[j] = eax >> (8 * j);
		string[j + 4] = ebx >> (8 * j);
		string[j + 8] = ecx >> (8 * j);
		string[j + 12] = edx >> (8 * j);
	}

	printk("%s", string);
}

/* информация AMD */
int print_amd(void) {
	printk("AMD Specific Features:\n");
	unsigned long extended, eax, ebx, ecx, edx, unused;
	int family, model, stepping, reserved;
	cpuid(1, eax, unused, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	stepping = eax & 0xf;
	reserved = eax >> 12;

	printk("Family: %d Model: %d [", family, model);

	switch (family) {
		case 4:
			printk("486 Model %d", model);
			break;
		
		case 5:
			switch (model) {
				case 0:
				case 1:
				case 2:
				case 3:
				case 6:
				case 7:
					printk("K6 Model %d", model);
					break;
			
				case 8:
					printk("K6-2 Model 8");
					break;
			
				case 9:
					printk("K6-III Model 9");
					break;
			
				default:
					printk("K5/K6 Model %d", model);
					break;
			}
			break;
		
		case 6:
			switch (model) {
				case 1:
				case 2:
				case 4:
					printk("Athlon Model %d", model);
					break;
			
				case 3:
					printk("Duron Model 3");
					break;
			
				case 6:
					printk("Athlon MP/Mobile Athlon Model 6");
					break;
			
				case 7:
					printk("Mobile Duron Model 7");
					break;
			
				default:
					printk("Duron/Athlon Model %d", model);
					break;
			}
			break;
	}

	printk("]\n");
	cpuid(0x80000000, extended, unused, unused, unused);
	
	if (extended == 0) {
		return 0;
	}
	
	if (extended >= 0x80000002) {
		unsigned int j;
		printk("Detected Processor Name: ");

		for (j = 0x80000002; j <= 0x80000004; j++) {
			cpuid(j, eax, ebx, ecx, edx);
			print_regs(eax, ebx, ecx, edx);
		}

		printk("\n");
	}

	if (extended >= 0x80000007) {
		cpuid(0x80000007, unused, unused, unused, edx);
		if (edx & 1) {
			printk("Temperature Sensing Diode Detected!\n");
		}
	}

	printk("Stepping: %d Reserved: %d\n", stepping, reserved);

	return 0;
}

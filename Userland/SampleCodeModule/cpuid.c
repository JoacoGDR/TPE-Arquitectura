/*
 * Copyright (c) 2006-2007 -  http://brynet.biz.tm - <brynet@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* You need to include a file with fairly(ish) compliant printf prototype, Decimal and String support like %s and %d and this is truely all you need! */
//#include <stdio.h> /* for printf(); */

/* Required Declarations */
int do_intel(void);
int do_amd(void);
void printregs(int eax, int ebx, int ecx, int edx);
extern void syscall_write(char * s, int l);

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

/* Simply call this function detect_cpu(); */
int detect_cpu(void) { /* or main() if your trying to port this as an independant application */
	unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);
	switch(ebx) {
		case 0x756e6547: /* Intel Magic Code */
		do_intel();
		break;
		case 0x68747541: /* AMD Magic Code */
		do_amd();
		break;
		default:
		syscall_write("Unknown x86 CPU Detected\n", 25);
		break;
	}
	return 0;
}

/* Intel Specific brand list */
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

/* This table is for those brand strings that have two values depending on the processor signature. It should have the same number of entries as the above table. */
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

/* Intel-specific information */
int do_intel(void) {
	syscall_write("Intel Specific Features:\n", 25);
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
	//syscall_write("Type %d - ", type);
	switch(type) {
		case 0:
		syscall_write("Original OEM", 12);
		break;
		case 1:
		syscall_write("Overdrive", 9);
		break;
		case 2:
		syscall_write("Dual-capable", 12);
		break;
		case 3:
		syscall_write("Reserved", 8);
		break;
	}
	syscall_write("\n", 1);
	//syscall_write("Family %d - ", family);
	switch(family) {
		case 3:
		syscall_write("i386", 4);
		break;
		case 4:
		syscall_write("i486", 4);
		break;
		case 5:
		syscall_write("Pentium", 7);
		break;
		case 6:
		syscall_write("Pentium Pro", 11);
		break;
		case 15:
		syscall_write("Pentium 4", 9);
	}
	syscall_write("\n", 1);
	if(family == 15) {
		extended_family = (eax >> 20) & 0xff;
		//syscall_write("Extended family %d\n", extended_family);
	}
	//syscall_write("Model %d - ", model);
	switch(family) {
		case 3:
		break;
		case 4:
		switch(model) {
			case 0:
			case 1:
			syscall_write("DX", 2);
			break;
			case 2:
			syscall_write("SX", 2);
			break;
			case 3:
			syscall_write("487/DX2", 7);
			break;
			case 4:
			syscall_write("SL", 2);
			break;
			case 5:
			syscall_write("SX2", 3);
			break;
			case 7:
			syscall_write("Write-back enhanced DX2", 23);
			break;
			case 8:
			syscall_write("DX4", 3);
			break;
		}
		break;
		case 5:
		switch(model) {
			case 1:
			syscall_write("60/66", 5);
			break;
			case 2:
			syscall_write("75-200", 6);
			break;
			case 3:
			syscall_write("for 486 system", 14);
			break;
			case 4:
			syscall_write("MMX", 3);
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			syscall_write("Pentium Pro", 11);
			break;
			case 3:
			syscall_write("Pentium II Model 3", 18);
			break;
			case 5:
			syscall_write("Pentium II Model 5/Xeon/Celeron", 31);
			break;
			case 6:
			syscall_write("Celeron", 7);
			break;
			case 7:
			syscall_write("Pentium III/Pentium III Xeon - external L2 cache", 48);
			break;
			case 8:
			syscall_write("Pentium III/Pentium III Xeon - internal L2 cache", 48);
			break;
		}
		break;
		case 15:
		break;
	}
	syscall_write("\n", 1);
	cpuid(0x80000000, max_eax, unused, unused, unused);
	/* Quok said: If the max extended eax value is high enough to support the processor brand string
	(values 0x80000002 to 0x80000004), then we'll use that information to return the brand information. 
	Otherwise, we'll refer back to the brand tables above for backwards compatibility with older processors. 
	According to the Sept. 2006 Intel Arch Software Developer's Guide, if extended eax values are supported, 
	then all 3 values for the processor brand string are supported, but we'll test just to make sure and be safe. */
	if(max_eax >= 0x80000004) {
		syscall_write("Brand: ", 7);
		if(max_eax >= 0x80000002) {
			cpuid(0x80000002, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000003) {
			cpuid(0x80000003, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000004) {
			cpuid(0x80000004, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		syscall_write("\n", 1);
	} else if(brand > 0) {
		//syscall_write("Brand %d - ", brand);
		if(brand < 0x18) {
			if(signature == 0x000006B1 || signature == 0x00000F13) {
				syscall_write(/*"%s\n",*/ Intel_Other[brand], 20);
			} else {
				syscall_write(/*"%s\n", */Intel[brand], 20);
			}
		} else {
			syscall_write("Reserved\n", 9);
		}
	}
	//syscall_write("Stepping: %d Reserved: %d\n", stepping, reserved);
	return 0;
}

/* Print Registers */
void printregs(int eax, int ebx, int ecx, int edx) {
	int j;
	char string[17];
	string[16] = '\0';
	for(j = 0; j < 4; j++) {
		string[j] = eax >> (8 * j);
		string[j + 4] = ebx >> (8 * j);
		string[j + 8] = ecx >> (8 * j);
		string[j + 12] = edx >> (8 * j);
	}
	syscall_write(/*"%s", */string, 17);
}

/* AMD-specific information */
int do_amd(void) {
	syscall_write("AMD Specific Features:\n", 25);
	unsigned long extended, eax, ebx, ecx, edx, unused;
	int family, model, stepping, reserved;
	cpuid(1, eax, unused, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	stepping = eax & 0xf;
	reserved = eax >> 12;
	//syscall_write("Family: %d Model: %d [", family, model);
	switch(family) {
		case 4:
		syscall_write("486 Model", 9 /*%d", model*/); ///////////////////////////////////////////////
		break;
		case 5:
		switch(model) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 6:
			case 7:
			syscall_write("K6 Model", 8 /*%d", model*/);///////////////////////////////////////////////////
			break;
			case 8:
			syscall_write("K6-2 Model 8", 12);
			break;
			case 9:
			syscall_write("K6-III Model 9", 14);
			break;
			default:
			syscall_write("K5/K6 Model", 11 /*%d", model*/);////////////////////////////////////////////////////////
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			case 2:
			case 4:
			syscall_write("Athlon Model", 12 /*%d", model*/);////////////////////////////////////////////////////////
			break;
			case 3:
			syscall_write("Duron Model 3", 13);
			break;
			case 6:
			syscall_write("Athlon MP/Mobile Athlon Model 6", 31);
			break;
			case 7:
			syscall_write("Mobile Duron Model 7", 20);
			break;
			default:
			syscall_write("Duron/Athlon Model", 18 /*%d", model*/);////////////////////////////////////////////////////////
			break;
		}
		break;
	}
	syscall_write("]\n", 2);
	cpuid(0x80000000, extended, unused, unused, unused);
	if(extended == 0) {
		return 0;
	}
	if(extended >= 0x80000002) {
		unsigned int j;
		syscall_write("Detected Processor Name: ", 25);
		for(j = 0x80000002; j <= 0x80000004; j++) {
			cpuid(j, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		syscall_write("\n", 2);
	}
	if(extended >= 0x80000007) {
		cpuid(0x80000007, unused, unused, unused, edx);
		if(edx & 1) {
			syscall_write("Temperature Sensing Diode Detected!\n", 36);
		}
	}
	//syscall_write("Stepping: %d Reserved: %d\n", stepping, reserved);
	return 0;
}
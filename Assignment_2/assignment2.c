#include <assignment2.h>

int32_t main(int32_t argc, char *argv[])
{
	int32_t fd;

	if(argc!=2) { // Case 0 - 1 ) If file name is not given on cli.
		printf("Usage: assignment2 <file>\n");
		return 0;
	}

	fd = open(argv[1], O_RDWR|O_SYNC);
	if(fd<0) { // Case 0 - 2 ) If can't open file.
		printf("Error %d Unable to open %s\n", fd, argv[1]);
		return 0;
	}

	Elf64_Ehdr ehdr;
	Elf64_Shdr* sh_tbl;
	
	read_elf_header(fd, &ehdr); // Read hear part of file
	
    if(!is_elf( ehdr )) { // Determine if file is ELF format or not.
		return 0; // If not, terminate program.
	}
	else // Else print ELF.
		printf("ELF\n");
	
	// Then, we have to change string "rodata rodata rodata Can you modify this?" to "I modified it" located inside .rodata section of ELF file.



	print_elf_header(ehdr); // Else, print elf header.

	sh_tbl = malloc(ehdr.e_shentsize * ehdr.e_shnum);
	if(!sh_tbl) {
		printf("Failed to allocate %d bytes\n", (ehdr.e_shentsize * ehdr.e_shnum));
	}
	print_section_headers(fd, ehdr, sh_tbl);

	conv_rodata(fd, ehdr, sh_tbl);

	return 0;

}


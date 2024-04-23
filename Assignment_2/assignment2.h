#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <elf.h>

bool is_elf(Elf64_Ehdr eh);
void read_elf_header(int32_t fd, Elf64_Ehdr *elf_header);
void print_elf_header(Elf64_Ehdr elf_header);
char *read_section(int32_t fd, Elf64_Shdr sh);
void print_section_headers(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[]);

//Implement this function to check whether an input file is an elf file or not.
bool is_elf( Elf64_Ehdr eh )
{
	if(eh.e_ident[1] == 0x45 && eh.e_ident[2] == 0x4c && eh.e_ident[3] == 0x46) // If left condition is occur, we can determine file as .ELF file.
		return true; // Then, return true.
	else // If not, return false.
		return false;
}

void read_elf_header(int32_t fd, Elf64_Ehdr *elf_header)
{
	assert(elf_header != NULL);
	assert(lseek(fd, (off_t)0, SEEK_SET) == (off_t)0);
	assert(read(fd, (void *)elf_header, sizeof(Elf64_Ehdr)) == sizeof(Elf64_Ehdr));
}

void print_elf_header(Elf64_Ehdr elf_header)
{
	printf("Storage class\t= ");
	switch(elf_header.e_ident[EI_CLASS])
	{
		case ELFCLASS32:
			printf("32-bit objects\n");
			break;

		case ELFCLASS64:
			printf("64-bit objects\n");
			break;

		default:
			printf("Unknwon CLASS\n");
			break;
	}

	printf("Data format\t= ");
	switch(elf_header.e_ident[EI_DATA])
	{
		case ELFDATA2LSB:
			printf("2's complement, little endian\n");
			break;

		case ELFDATA2MSB:
			printf("2's complement, big endian\n");
			break;

		default:
			printf("Unknwon Format\n");
			break;
	}

	printf("OS ABI\t\t= ");
	switch(elf_header.e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV:
			printf("UNIX System V ABI\n");
			break;

		case ELFOSABI_HPUX:
			printf("HP-UX\n");
			break;

		case ELFOSABI_NETBSD:
			printf("NetBSD\n");
			break;

		case ELFOSABI_LINUX:
			printf("Linux\n");
			break;

		case ELFOSABI_SOLARIS:
			printf("Sun Solaris\n");
			break;

		case ELFOSABI_AIX:
			printf("IBM AIX\n");
			break;

		case ELFOSABI_IRIX:
			printf("SGI Irix\n");
			break;

		case ELFOSABI_FREEBSD:
			printf("FreeBSD\n");
			break;

		case ELFOSABI_TRU64:
			printf("Compaq TRU64 UNIX\n");
			break;

		case ELFOSABI_MODESTO:
			printf("Novell Modesto\n");
			break;

		case ELFOSABI_OPENBSD:
			printf("OpenBSD\n");
			break;

		case ELFOSABI_ARM_AEABI:
			printf("ARM EABI\n");
			break;

		case ELFOSABI_ARM:
			printf("ARM\n");
			break;

		case ELFOSABI_STANDALONE:
			printf("Standalone (embedded) app\n");
			break;

		default:
			printf("Unknown (0x%x)\n", elf_header.e_ident[EI_OSABI]);
			break;
	}

	printf("Filetype \t= ");
	switch(elf_header.e_type)
	{
		case ET_NONE:
			printf("N/A (0x0)\n");
			break;

		case ET_REL:
			printf("Relocatable\n");
			break;

		case ET_EXEC:
			printf("Executable\n");
			break;

		case ET_DYN:
			printf("Shared Object\n");
			break;
		default:
			printf("Unknown (0x%x)\n", elf_header.e_type);
			break;
	}

	printf("Machine\t\t= ");
	switch(elf_header.e_machine)
	{
		case EM_NONE:
			printf("None (0x0)\n");
			break;

		case EM_386:
			printf("INTEL x86 (0x%x)\n", EM_386);
			break;

		case EM_X86_64:
			printf("AMD x86_64 (0x%x)\n", EM_X86_64);
			break;

		case EM_AARCH64:
			printf("AARCH64 (0x%x)\n", EM_AARCH64);
			break;

		default:
			printf(" 0x%x\n", elf_header.e_machine);
			break;
	}
	printf("\n");
}

char *read_section(int32_t fd, Elf64_Shdr sh)
{
	char* buff = malloc(sh.sh_size);
	if(!buff) {
		printf("%s:Failed to allocate %ldbytes\n",
				__func__, sh.sh_size);
	}

	assert(buff != NULL);
	assert(lseek(fd, (off_t)sh.sh_offset, SEEK_SET) == (off_t)sh.sh_offset);
	assert(read(fd, (void *)buff, sh.sh_size) == sh.sh_size);

	return buff;
}

void print_section_headers(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[])
{
	uint32_t i;
	char* sh_str;

	assert(lseek(fd, (off_t)eh.e_shoff, SEEK_SET) == (off_t)eh.e_shoff);

	for(i=0; i<eh.e_shnum; i++) {
		assert(read(fd, (void *)&sh_table[i], eh.e_shentsize) == eh.e_shentsize); // Read each type's section header.
	}

	/* section-header string-table */
	sh_str = read_section(fd, sh_table[eh.e_shstrndx]); // Get entire string of section header string table.

	for(i=0; i<eh.e_shnum; i++) {
		if(!strncmp((sh_str + sh_table[i].sh_name), ".rodata", 7)) // Print out section header name by using section header string and offset of name.
		{
			printf("%s section info\n", (sh_str + sh_table[i].sh_name));
			printf("    file offset = 0x%08lx\n", sh_table[i].sh_offset);
			printf("           size = 0x%08lx\n", sh_table[i].sh_size);
		}
	}

}

void conv_rodata(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[]){
	uint32_t i;
	char* sh_str;

	assert(lseek(fd, (off_t)eh.e_shoff, SEEK_SET) == (off_t)eh.e_shoff); // Check start position of section header table is exist.

	for( i=0; i < eh.e_shnum; i++ )
		assert(read(fd, (void *)&sh_table[i], eh.e_shentsize) == eh.e_shentsize); // Read each type's section header.

		// assert() is function which returns stderr when content inside is false. If inside is true, then nothing happens.
		// read function w/ option of (int fd, void *buf, size_t n_bytes) reads data in fd, store data in buf, and reads n_bytes.
		// above, it reads fd, stores in sh_table(and using type conversion and & to give address of target array), and read section header's entire size by using eh.e_shentsize.
		// Also, due to lseek above, starting position of reading is offset of starting position of section header.
		// Comparing read position is same as e_shentsize(abbreviate of Elf_Section_Header_Entity_Size and it is field name) position inside of ELF header.

	/* section-header string-table */
	sh_str = read_section(fd, sh_table[eh.e_shstrndx]);

	for( i = 0; i < eh.e_shnum; i++ ){

		if( !strncmp( (sh_str + sh_table[i].sh_name), ".rodata", 7 ) ){
			long data_size = sh_table[i].sh_size;

			char rodata_tmp[data_size];
			assert( rodata_tmp != NULL );
			assert( lseek( fd, (off_t)sh_table[i].sh_offset, SEEK_SET ) == (off_t)sh_table[i].sh_offset ); // Set file's starting position as .rodata's start position.

			char tmp;
			size_t string_start_offset = 0;

			while(1){
				assert( lseek( fd, (off_t)sh_table[i].sh_offset + string_start_offset, SEEK_SET ) == (off_t)sh_table[i].sh_offset + string_start_offset );
				// Re define starting position of file descriptor as next position of final part of current string.
				read( fd, (void*)&tmp, 1 ); // Read one value to find current position has characters.

				if( tmp > 0x19 && tmp < 0x127 && string_start_offset < data_size ){ // Check if read value has character property and if it occurs, exec below step.
					off_t start_pos = (off_t)sh_table[i].sh_offset + string_start_offset; // Defining starting position's offset by adding start position of current section and calculated offset.
					assert( lseek( fd, start_pos, SEEK_SET ) == start_pos ); // Set starting postion.
					assert( read( fd, (void*)rodata_tmp, ( data_size - string_start_offset ) ) ); // Read entire file froms tarting pos to end of current section.

					char* target_str = strstr( rodata_tmp, "rodata rodata rodata Can you modify this?" ); // Then, find if "rodata rodata rodata Can you modify this?" exist in current string.

					if( target_str != NULL ){ // If we found right one, Fix it.
						assert( lseek( fd, start_pos, SEEK_SET ) == start_pos ); // Define start pos of fd as first position of string.
						assert( write( fd, "I modified it", 13 ) == 13 );
						assert( write( fd, "\0", 1 ) == 1 );
					}

					// Else, keep going to found next string.
					string_start_offset += strlen(rodata_tmp); // Calculate next starting offset.
				}
				else if( string_start_offset > data_size )
					break;
				else
					string_start_offset++;
			}

			break;
		}
	}

}

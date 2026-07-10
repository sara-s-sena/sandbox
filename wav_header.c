/* Curriculum for this file: 1. Understand WAV format (you research, explain back to me)
2. Write the WAV header in C (just the struct, no sound yet)
3. Understand sine waves as sound (the math, runnable example)
4. Generate one single note as a WAV file
5. Play it in Windows, confirm it works
6. Build the note frequency table
7. Build the melody array
8. Loop through melody, write all notes to one WAV file
9. Play the full song 
*/

// Write the header in C
// should we start with an #include <stdint.h> for fixed-width integer types? Yes.

#include <stdint.h>

// what do we need to include for file I/O? We need <stdio.h> for file operations.
#include <stdio.h>

/* what does sizeof(WAVHeader) return? It returns the total size in bytes of the WAVHeader structure, which includes all the members defined within it. This size can be used to allocate memory or to write the header to a file. How do I know without running the code? You can calculate the size of the WAVHeader structure by adding up the sizes of its individual members. The sizes of the members are as follows:
- riff_id: 4 bytes
- riff_size: 4 bytes
- wave_id: 4 bytes
- fmt_id: 4 bytes
- fmt_size: 4 bytes
- audio_format: 2 bytes // How do you know it's 2 bytes? Because uint16_t is a 16-bit unsigned integer, which is 2 bytes in size. But you said uint32_t = 4 GB? Yes, uint32_t is a 32-bit unsigned integer, which can represent values up to 4,294,967,295 (approximately 4 GB). However, uint16_t is a 16-bit unsigned integer, which can represent values up to 65,535. The size of the data type determines how many bytes it occupies in memory. In this case, audio_format is defined as uint16_t, so it occupies 2 bytes in the WAVHeader structure. 
- num_channels: 2 bytes
- sample_rate: 4 bytes
- byte_rate: 4 bytes
- block_align: 2 bytes
- bits_per_sample: 2 bytes
- data_id: 4 bytes
- data_size: 4 bytes
Adding these together gives a total size of 44 bytes for the WAVHeader structure./ */

int main(void) {
    printf("Size of WAVHeader: %zu bytes\n", sizeof(WAVHeader)); // %zu is the format specifier for size_t, which is the type returned by sizeof. Is "sizeof" something created by me or is it a built-in function? It is a built-in operator in C that returns the size, in bytes, of a variable or data type. What does it mean to return the size of a variable or data type and why is it useful? It means that sizeof gives you the amount of memory (in bytes) that a variable or data type occupies. This is useful for memory allocation, understanding data structures, and ensuring that you are using the correct amount of memory for your variables. For example, if you want to allocate memory for an array of WAVHeader structures, you can use sizeof(WAVHeader) to determine how much memory to allocate.
    return 0;
}

// How do I compile this code? You can compile this code using a C compiler like GCC. For example, you can use the following command in your terminal or command prompt:
// gcc -o wav_header wav.header.c Where is -o? The -o option specifies the name of the output file that will be generated after compilation. In this case, it will create an executable file named "wav_header". What happens if I don't use -o? If you don't use the -o option, the compiler will generate an output file with a default name, usually "a.out" on Unix-like systems or "a.exe" on Windows. So it's not necessary to use -o, but it allows you to specify a custom name for the output file.


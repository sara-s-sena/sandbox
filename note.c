/* In this file, we will: 1. Initialize Configuration VariablesBefore opening any files, 
define the parameters of your audio. You need to set:Audio settings: The sample rate (e.g., 44100), 
the duration (e.g., 2 seconds), and the frequency of your note (e.g., 440 Hz).Calculated totals: 
Calculate the total number of samples ($44100 \times 2 = 88200$ samples) 
and the total data size in bytes ($88200 \times 2 \text{ bytes per sample} = 176400 \text{ bytes}$).2. 
Allocate Memory for Audio DataAllocate an array to hold your audio samples. Since you are likely using 
16-bit signed audio, this will be an array of int16_t.You can use standard array declaration or dynamic 
memory allocation (malloc).3. Generate the Audio Data (The Math Loop)Run a loop from i = 0 up to your 
total number of samples to generate the sine wave:Calculate the sine value using your 
formula: $A \cdot \sin(2\pi \cdot f \cdot i / \text{sample\_rate})$.Scale the result to fit into the 
16-bit signed integer range (multiplying by a maximum volume like 32767).Store each calculated value
inside your allocated memory array.4. Construct the WAV HeaderCreate your header structure in memory
and populate its fields with the exact metadata required by the WAV format:Write "RIFF" into the
chunkID.Calculate and write the chunkSize (the total size of the file minus 8 bytes).Write "WAVE" 
into the format field.Populate the sub-chunks ("fmt "), setting the audio format to 1 (PCM / uncompressed), 
channels to 1 (Mono), sample rate to 44100, and bits per sample to 16.Populate the "data" sub-chunk 
with the size of your raw audio array.5. Open the File for WritingOpen a file pointer to write binary 
data to your disk.Use fopen("note.wav", "wb"). (The "wb" mode is crucial because it stands for Write 
Binary; without it, Windows/Linux might corrupt your raw byte data).6. Sequential Write to DiskWrite 
the data to the file in the exact order the operating system expects to read it:Write the Header: Use
fwrite() to copy your populated WAV header structure to the file first.Write the Audio Array: Use 
fwrite() immediately after to append your entire array of generated sine wave samples.7. Cleanup
and CloseClose the file pointer using fclose() to ensure all data is safely flushed from memory
cache to your actual disk.Free any dynamically allocated memory (free()).Return 0 from main() 
to signal success!Once this sequence completes, your terminal will have a freshly minted, 
playable .wav file waiting for you. */ 

#include <stdint.h> // for int16_t
#include <stdio.h> // for printf() and file I/O 
#include <math.h> // for sin() and M_PI
#include <stdlib.h> // for malloc() and free()
#include "note.h" // for WAVHeader structure and Note enum
#include <string.h> // for memcpy()
// What's next? Now we can proceed to implement the steps outlined in the comments above, starting with defining the configuration variables for our audio file.

#define SAMPLE_RATE 44100 // samples per second

/* Define an array of 15 MelodyNote values. Each entry has a note from the Note enum, an octave number (4 or 5), and a duration in samples (e.g., 44100 for 1 second).  */
/* To get a duration in samples, we use this conversion: duration_in_samples = (duration_in_milliseonds + SAMPLE_RATE) / 1000. */
/* For a minor waltz, 3/4 time you want:

Time signature: 3/4 — every group of 3 notes, the first is long (strong beat), the next two are short (weak beats). That's what makes it feel like a waltz.
Notes: minor key — use A minor, which uses the notes A, B, C, D, E, F, G.
Tempo: slow, around 120 BPM. At 120 BPM, one beat = 500ms. */


int main(void) {

    MelodyNote melody[15] = {
        {A, 4, 22050}, // beat 1: A4 for 0.5 seconds (strong beat)
        {C, 5, 11025}, // beat 2: C5 for 0.25 seconds (weak beat)
        {E, 5, 11025}, // beat 3: E5 for 0.25 seconds (weak beat)
        {E, 5, 22050}, // beat 1: E5 for 0.5 seconds (strong beat)
        {D, 5, 11025}, // beat 2: D5 for 0.25 seconds (weak beat)
        {C, 5, 11025}, // beat 3
        {D, 5, 22050}, // beat 1 - strong
        {B, 4, 11025}, // beat 2
        {G_sharp,4,11025}, // beat 3
        {A, 4, 22050}, // beat 1 - strong
        {E, 5, 11025}, // beat 2
        {A, 5, 11025}, // beat 3
        {C, 5, 22050}, // beat 1 - strong
        {B, 4, 11025}, // beat 2
        {A, 4, 22050} // beat 1 - resolution
    };

    // Loop that computes total_samples by summing all duration_samples fields - starting with int total_samples = 0;
    int total_samples = 0;
    for (int i = 0; i < 15; i++) {
        total_samples += melody[i].duration_samples; // why [i] like this? Because we are accessing the duration_samples field of the i-th element of the melody array.
    }

    // data_size 
    int data_size = total_samples * sizeof(int16_t);

    // Allocate the sample array with malloc
    int16_t *samples = (int16_t *)malloc(data_size);
    if (samples == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1; // Exit with an error code
    }
    
    
    // Outer loop that iterates over the 15 melody notes. Inner loop that generates samples for the current note using note_freq(). int sample_index = 0 before the outer loop.
    int sample_index = 0;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < melody[i].duration_samples; j++) {
            double time_sec = (double)sample_index / SAMPLE_RATE;
            int16_t sample = (int16_t)(32767 * sin(2.0 * M_PI * note_freq(melody[i].note, melody [i].octave) * time_sec));
            samples[sample_index] = sample;
            sample_index++; // what does ++ do? It is a shorthand way of writing "sample_index = sample_index + 1". It is equivalent to "sample_index += 1
        }
    }

    // Construct the WAV header
    WAVHeader header; // Is it a definition? Yes, this line defines a variable named 'header' of type 'WAVHeader'. Why it doesn't have #define? Because 'WAVHeader' is a structure type that has been defined earlier in the code, and we are creating an instance of that structure. The '#define' directive is used for defining constants or macros, not for defining variables or instances of structures. In this case, we are simply declaring a variable of the 'WAVHeader' type to hold the metadata for our WAV file.
    // I just found out WAVHeader is defined in note.h.
    // Populate the WAV header fields
    memcpy(header.riff_id, "RIFF", 4); // what is "memcpy"? It is a standard library function in C that copies a specified number of bytes from one memory location to another. In this case, it copies the string "RIFF" into the "riff_id" field of the WAV header. Why not just use "="? Because "riff_id" is an array of characters, and in C, you cannot assign a string directly to an array using the "=" operator. Instead, you need to use a function like "memcpy" to copy the string into the array. What happens if we use "="? If you try to use "=" to assign a string to an array, you will get a compilation error because arrays cannot be assigned values in that way. The correct approach is to use "memcpy" or "strncpy" to copy the string into the array.
    header.riff_size = 36 + data_size; // 36 bytes for the header and 2 for the data_size? Yes or no? No, the 36 bytes refers to the size of the WAV header (which includes the RIFF header, format chunk, and data chunk headers) excluding the actual audio data. The "data_size" variable represents the size of the audio data in bytes. Therefore, "riff_size" is calculated as 36 (header size) + data_size (size of the audio data). The total size of the WAV file will be 36 bytes for the header plus the size of the audio data.
    memcpy(header.wave_id, "WAVE", 4);
    memcpy(header.fmt_id, "fmt ", 4);
    header.fmt_size = 16; // PCM format chunk size
    header.audio_format = 1; // PCM
    header.num_channels = 1; // Mono
    header.sample_rate = SAMPLE_RATE;
    header.byte_rate = SAMPLE_RATE * header.num_channels * sizeof(int16_t); // sample
    header.block_align = header.num_channels * sizeof(int16_t); // 2 bytes per sample
    header.bits_per_sample = 16; // 16 bits per sample
    memcpy(header.data_id, "data", 4);
    header.data_size = data_size;

    // From where did you take those numbers? The numbers used to populate the WAV header fields are based on the WAV file format specification and the parameters defined earlier in the code. Here's a breakdown of where each number comes from:
    // - "RIFF" and "WAVE": These are standard identifiers for the WAV file format, indicating that the file is a RIFF file and that it contains WAVE audio data
    // - fmt_size = 16: This is the size of the format chunk for PCM audio, which is always 16 bytes for uncompressed PCM data.
    // - audio_format = 1: This indicates that the audio format is PCM (Pulse Code Modulation), which is the standard format for uncompressed audio data in WAV files.
    // - num_channels = 1: This indicates that the audio is mono (single channel). If it were stereo, this value would be 2.
    // - sample_rate = SAMPLE_RATE: This is the sample rate defined earlier in the code (44100 samples per second).
    // - byte_rate = SAMPLE_RATE * num_channels * sizeof(int16_t): This calculates the number of bytes per second of audio data, based on the sample rate, number of channels, and size of each sample (2 bytes for 16-bit audio).
    // - block_align = num_channels * sizeof(int16_t): This calculates the number of bytes for one sample frame, which is the number of channels multiplied by the size of each sample (2 bytes for 16-bit audio).
    // - bits_per_sample = 16: This indicates that each audio sample is 16 bits (2 bytes) in size.
    // - data_size = data_size: This is the size of the audio data in bytes, calculated earlier based on the total number of samples and the size of each sample.




    // Open the file for writing
    FILE *file = fopen("note.wav", "wb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing!\n");
        free(samples); // Free the allocated memory before exiting
        return 1; // Exit with an error code
    }

    // Close the file after writing the header and audio data
    fwrite(&header, sizeof(WAVHeader), 1, file); // Write the WAV header to the file
    fwrite(samples, sizeof(int16_t), total_samples, file); // Write the audio samples to the file
    // Close the file after writing
    fclose(file); 


    // Free the allocated memory
    free(samples);
    return 0;
}


#ifndef NOTE_H // why do we need this? It is a header guard that prevents multiple inclusions of the same header file, which can cause compilation errors. What happens if we remove it? If we remove it, and the header file is included multiple times in different source files, it can lead to redefinition errors and other issues during compilation. 
#define NOTE_H // This line defines the macro NOTE_H, which is used in conjunction with the #ifndef directive to create the header guard. If NOTE_H is not defined, the contents of the header file will be included; otherwise, they will be skipped.

#include <stdint.h> // for fixed-width integer types, such as int16_t and uint32_t
#include <math.h> // for pow() function used in note_freq

/* // Define the WAV header structure based on the WAV file format specification. The WAV file format consists of a RIFF header, a format chunk, and a data chunk. */
typedef struct {
// Format Chunk
    // RIFF Header
    char riff_id[4];        // "RIFF"
    uint32_t riff_size;    // Size of the entire file minus 8 bytes for the RIFF header. Why uint32_t? Because it's a 32-bit unsigned integer. Does that mean the maximum file size is 4GB? Yes, that's correct. So I am the one who needs to make sure the file size does not exceed 4GB. How do I calculate the file size? It is the size of the data chunk plus the size of the format chunk plus 36 bytes for the header. Example: If the data chunk is 1,000,000 bytes and the format chunk is 16 bytes, then the total file size would be 1,000,000 + 16 + 36 = 1,000,052 bytes. Therefore, riff_size would be 1,000,052 - 8 = 1,000,044 bytes. What does it has to do with uint32_t? It is used to store the size of the file in bytes, which can be a large number, so we use a 32-bit unsigned integer to accommodate that. What is the maximum value of uint32_t? The maximum value of uint32_t is 4,294,967,295 (2^32 - 1). What happens if the file size exceeds this limit? If the file size exceeds this limit, it will cause an overflow and result in incorrect file size information in the header. How can we prevent this? We can prevent this by ensuring that the total size of the WAV file does not exceed 4GB when generating or writing the file.
    char wave_id[4];        // "WAVE" What does this mean? It indicates that the file is in WAV format. Why 4 bytes? Because the string "WAVE" is 4 characters long, and each character is 1 byte in size. Where is the string "WAVE"? Will it appear somewhere afterwards? It appears in the header of the WAV file, specifically in the format chunk, to identify the file as a WAV file. It is not repeated elsewhere in the file.
    char fmt_id[4];     // "fmt " What does this mean? It indicates the start of the format chunk in the WAV file. Wait, is it WAV or WAVE? It is WAV. What's the difference between WAV and WAVE? WAV is the file extension, while WAVE is the format name. Why is there a space after "fmt"? The space is included to make the identifier 4 bytes long, as required by the WAV file format specification. Where is the string "fmt "? Will it appear somewhere afterwards? It appears in the header of the WAV file to identify the format chunk. It is not repeated elsewhere in the file.
    uint32_t fmt_size; // Size of the format chunk (16 for PCM). What is even "format chunk"? The format chunk contains information about the audio format, such as the number of channels, sample rate, and bit depth. Why is it 16 for PCM? Because the PCM format has a fixed size of 16 bytes for its format chunk. What is PCM? PCM stands for Pulse Code Modulation, which is a method used to digitally represent analog signals. It is the standard form of digital audio in computers and various Blu-ray, Compact Disc and DVD formats. What does it mean that it is "fixed size"? It means that the size of the format chunk is always 16 bytes for PCM audio, regardless of the specific audio data being stored. What happens if we use a different audio format? If we use a different audio format, the size of the format chunk may vary depending on the specific format being used. For example, if we use a compressed audio format like MP3, the size of the format chunk may be larger than 16 bytes.
    uint16_t audio_format; // Audio format (1 for PCM). What does this mean? It indicates the audio format used in the WAV file. Why is it 1 for PCM? Because PCM is the standard uncompressed audio format, and it is represented by the value 1 in the WAV file specification. What are other possible values for audio_format? Other possible values include 3 for IEEE float, 6 for A-law, and 7 for mu-law. What happens if we use a different audio format? If we use a different audio format, we need to set the audio_format field to the corresponding value for that format. For example, if we use IEEE float, we would set audio_format to 3.
    uint16_t num_channels; // Number of channels (1 for mono, 2 for stereo). What does channels do? Channels determine how many separate audio signals are present in the audio data. Realistic example of a mono audio signal: A mono audio signal is a single audio channel that contains the same sound information for both the left and right speakers. For example, if you record a person speaking with a single microphone, the resulting audio signal would be mono, as it captures only one channel of audio. When played back through stereo speakers, the same sound will be heard from both the left and right speakers. Realistic example of a stereo audio signal: A stereo audio signal consists of two separate audio channels, typically referred to as the left and right channels. For example, if you record a live concert with two microphones placed at different locations on the stage, you can capture the sound from different perspectives. The left microphone captures the sound from one side of the stage, while the right microphone captures the sound from the other side. When played back through stereo speakers, the listener will hear distinct sounds coming from the left and right speakers, creating a sense of spatial depth and directionality in the audio.
    // Is it me who chooses the number of channels? Yes, you can choose the number of channels based on your audio requirements. For example, if you want to create a mono audio file, you would set num_channels to 1. If you want to create a stereo audio file, you would set num_channels to 2. What happens if we use more than 2 channels? If you use more than 2 channels, it will create a multi-channel audio file, which can be used for surround sound or other advanced audio setups. However, not all audio players may support multi-channel audio playback.
    uint32_t sample_rate; // Sample rate (e.g., 44100 Hz). What does this mean? It indicates the number of samples of audio carried per second. Why is it 44100 Hz? 44100 Hz is the standard sample rate for audio CDs, providing a good balance between audio quality and file size. What are other common sample rates? Other common sample rates include 22050 Hz, 48000 Hz, and 96000 Hz. What happens if we use a different sample rate? Using a different sample rate will affect the audio quality and file size. Higher sample rates can capture more detail in the audio but will result in larger file sizes. Lower sample rates may reduce audio quality but will create smaller files.
    // Wait, I used int for sample_rate, but I used uint32_t for riff_size and fmt_size. Why? The sample_rate is typically a smaller value (e.g., 44100), so using an int is sufficient. However, riff_size and fmt_size can be much larger values, so we use uint32_t to accommodate the potential size of the WAV file and format chunk. 
    uint32_t byte_rate;  // Byte rate (sample_rate * num_channels * bits_per_sample / 8). What does this mean? It indicates the number of bytes of audio data processed per second. Why is it calculated as sample_rate * num_channels * bits_per_sample / 8? This formula calculates the total number of bytes needed to represent one second of audio data based on the sample rate, number of channels, and bit depth. What happens if we use a different calculation? Using a different calculation may result in incorrect byte rate information, which can lead to playback issues or file corruption.
    uint16_t block_align; // Block align (num_channels * bits_per_sample / 8). Why do we need to multiply by num_channels? Because block align represents the number of bytes for one sample across all channels. What happens if we remove block align? Removing block align would make it difficult for audio players to correctly interpret the audio data, potentially leading to playback issues or file corruption.
    uint16_t bits_per_sample; // Bits per sample (e.g., 16). What does this mean? It indicates the number of bits used to represent each audio sample. Why is it 16? 16 bits per sample is a common bit depth that provides a good balance between audio quality and file size. What are other common bit depths? Other common bit depths include 8, 24, and 32 bits per sample. What happens if we use a different bit depth? Using a different bit depth will affect the audio quality and file size. Higher bit depths can capture more detail in the audio but will result in larger file sizes. Lower bit depths may reduce audio quality but will create smaller files.

    // Data Chunk
    char data_id[4];     // "data" What does this mean? It indicates the start of the data chunk in the WAV file. Why is it 4 bytes? Because the string "data" is 4 characters long, and each character is 1 byte in size.
    uint32_t data_size; //  Why not everything has a char[]? Because data_size is a 32-bit unsigned integer that represents the size of the audio data in bytes. It is not a string, so it does not need to be stored as a char array. What happens if we use a char[] instead? Using a char array would not accurately represent the size of the audio data, leading to incorrect file size information and potential playback issues. So what are we doing when we write "uint32_t data_size;"? are we defining something? Yes, we are defining a member of the WAV header structure that will hold the size of the audio data in bytes. This member is of type uint32_t, which is a 32-bit unsigned integer, allowing it to store values from 0 to 4,294,967,295. This is important for accurately representing the size of the audio data in the WAV file.
} WAVHeader; // why do we write "WAVHeader"? It is the name of the structure we are defining. Why is it at the end? In C, the name of the structure is typically placed at the end of the struct definition to indicate that this is the type name that can be used to declare variables of this structure type. What happens if we remove "WAVHeader"? If we remove "WAVHeader", we would not have a named type for the structure, making it more difficult to declare variables of this type. We would have to use "struct" every time we want to declare a variable of this structure type, which can be less convenient and less readable.

/* Typedef enum names Note with one entry per note (A#, D, F#, G#, E, A, B, C.), where each entry's value is the semitone offset from the table:
"C    = -9
C#   = -8
D    = -7
D#   = -6
E    = -5
F    = -4
F#   = -3
G    = -2
G#   = -1
A    =  0
A#   =  1
B    =  2"

For example, C = -9.
*/
typedef enum {
    A_sharp = 1,
    D = -7,
    F_sharp = -3,
    G_sharp = -1,
    E = -5,
    A = 0,
    B = 2,
    C = -9
} Note;

/* A function note_freq that takes a Note and an int octave and returns a double. 
Inside it: compute n = 12 * (octave - 4) + note, then return 440.0 * pow(2.0, n / 12.0). */
    static double note_freq(Note note, int octave) { // why adding 'static' before 'double'? It is used to declare a static variable, which is a variable that is shared by all instances of the function. In other words, it is a variable that is not local to the function, but is shared by all instances of the function. Being more specific, it is a variable that is not local to the function, but is shared by all instances of the function. So what is the difference between a static variable and a local variable? A static variable is a variable that is shared by all instances of the function, while a local variable is a variable that is local to the function. 
    int n = 12 * (octave - 4) + note; // Calculate the number of semitones away from A4
    return 440.0 * pow(2.0, n / 12.0); // Calculate the frequency using the formula // What does the pow() function do? The pow() function raises the first argument (base) to the power of the second argument (exponent). In this case, it calculates 2 raised to the power of (n / 12.0), which is used to determine the frequency of the note based on its semitone offset from A4.
} 

/* Add a MelodyNote struct with three fields: a Note (the enum defined above), an int octave, and an int for the duration in samples */

typedef struct {
    Note note; // The musical note (e.g., A, C#, etc.)
    int octave; // The octave of the note (e.g., 4 for A4)
    int duration_samples; // The duration of the note in samples
} MelodyNote;

#endif
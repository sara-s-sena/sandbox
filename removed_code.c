#define DURATION 10 // seconds // Can it be 10 seconds? Yes, you can set the duration to 10 seconds or any other positive integer value. Just keep in mind that increasing the duration will increase the total number of samples and the size of the resulting WAV file. For example, if you set DURATION to 10 seconds, the total number of samples would be 44100 * 10 = 441000 samples, and the data size would be 441000 * 2 bytes per sample = 882000 bytes. Make sure your system has enough memory and storage space to handle larger files. How many MB is 882000 bytes? 882000 bytes is approximately 0.84 MB (megabytes). You can calculate this by dividing the number of bytes by 1,048,576 (the number of bytes in a megabyte): 882000 / 1,048,576 ≈ 0.84 MB. Does 16-bit can bear 0.84 MB? Yes, a 16-bit audio file can easily handle 0.84 MB of data.
// Define the frequency of the note (A4 = 440 Hz)
#define FREQUENCY 440.0 // frequency of A4 in Hz. 
// WHat's next? Next, we will calculate the total number of samples and the total data size in bytes based on the defined sample rate and duration.
// SHould we start with int main() now? 

    // Calculate the total number of samples
    int total_samples = SAMPLE_RATE * DURATION; // 44100 * 10 = 441000 samples

    // Calculate the total data size in bytes (16-bit audio = 2 bytes per sample)
    int data_size = total_samples * sizeof(int16_t); // 441000 * 2 = 882000 bytes

    printf("Total samples: %d\n", total_samples);
    printf("Total data size: %d bytes\n", data_size);


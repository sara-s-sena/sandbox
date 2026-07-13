# open note.wav using wave.open()
import wave # is 'wave' referring to my file or a built-in module? It's a built-in module.
import numpy
# import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
import os


wave_file = wave.open('note.wav', 'rb') # rb means read binary.


print(f"Sample rate: {wave_file.getframerate()}")  # why 'f' before the string? What happens if we don't use 'f'? If we don't use 'f', the string will be treated as a regular string and the variables will not be interpolated. Interpolation is the process of substituting values for placeholders in a string. Placeholders? Placeholders are the variables that are substituted for in the string. What is being substituted in out string? The sample rate, number of channels, sample width, and total number of frames. What is it being substituted for? Are we substituting "sample rate, number of channels, sample width, and total number of frames" for "sample rate, number of channels, sample width, and total number of frames"? No, we are substituting the values of the sample rate, number of channels, sample width, and total number of frames for the placeholders in the string. Show me what is the placeholder: {wave_file.getframerate()}.
print(f"Number of channels: {wave_file.getnchannels()}")
print(f"Sample width: {wave_file.getsampwidth()}")
print(f"Total number of frames: {wave_file.getnframes()}")


audio_data = wave_file.readframes(wave_file.getnframes())
#close the wave file
wave_file.close()
audio_array = numpy.frombuffer(audio_data, dtype=numpy.int16) # why are we using dtype? dtype is the data type of the array, in this case 16-bit signed integers. Why do we need to convert the audio data to a numpy array? We need to convert the audio data to a numpy array because numpy is a library that allows us to perform numerical operations on arrays. What is the array here exactly? it is the audio data = audio data = numbers? yes or no? yes, the audio data is a numpy array of 16-bit signed integers. Show me exactly how it looks like:
print(audio_array[:10]) # show me the first 10 elements of the audio array.

# create the time axis: divide each sample index by the sample rate to get the time in seconds
time_axis = numpy.linspace(0, len(audio_array) / 44100, num=len(audio_array)) # assuming a sample rate of 44100 Hz


plt.plot(time_axis, audio_array) # what is this line doing? This line is plotting the audio data against the time axis using matplotlib. The x-axis represents time in seconds, and the y-axis represents the amplitude of the audio signal. What does plot mean? Plot means to create a graph or chart that represents data visually. In this case, we are creating a line graph of the audio waveform. 
plt.xlabel('Time (s)') # what is xlabel? xlabel is a function in matplotlib that sets the label for the x-axis of the plot.
plt.ylabel('Amplitude')
plt.title('Waveform of note.wav') # what is title? title is a function in matplotlib that sets the title of the plot.
plt.grid() # what is grid? grid is a function in matplotlib that adds a grid to the plot, making it easier to read the values on the axes. What is a grid? A grid is a set of horizontal and vertical lines that intersect to form squares or rectangles, which can help in visualizing data on a graph. 
plt.savefig('waveform.png') # what is show? show is a function in matplotlib that displays the plot in a window. It renders the plot and allows the user to interact with it, such as zooming or saving the image. 

# what is all that above? 
# The code above reads the audio data from a wave file, converts it to a numpy array, creates a time axis, and then plots the waveform of the audio data using matplotlib.

# Define FPS = 30 and samples_per_frame = 44100 // 30
FPS = 30
samples_per_frame = 44100 // FPS

# clear figure 
plt.clf() # what is clf? clf is a function in matplotlib that clears the current figure, allowing you to create a new plot without overlapping with the previous one. Which previous one? The previous plot of the waveform of note.wav.

# Take the first slice of audio_array - samples 0 to samples_per_frame
first_slice = audio_array[:samples_per_frame]

# Plots that slice with amplitude on y and sample index on x
plt.plot(first_slice)
plt.xlabel('Sample Index')
plt.ylabel('Amplitude')
plt.title('First Slice of note.wav') ## do we really need this here? Yes, it is good practice to include a title for clarity, especially if you are saving or sharing the plot.

# saves it as frame_0000.png
plt.savefig('frame_0000.png') # what is savefig? savefig is a function in matplotlib that saves the current figure to a file. Figure? A figure in matplotlib is the entire window or page that contains all the plots, axes, labels, and other elements.
plt.close()

# create a frames/ directory using os.makedirs - import os at the top
os.makedirs('frames', exist_ok=True) # what is makedirs? in simple words, makedirs is a function in the os module that creates a directory (or multiple directories) at the specified path. Can I instead create it through the terminal? Yes. Wait, should I write this function here and also create it through the terminal? No.

# Loop from 0 to total_frames (using len(audio_array) // samples_per_frame)
total_frames = len(audio_array) // samples_per_frame
for i in range(total_frames):
    # Take a slice of audio_array for the current frame
    start_index = i * samples_per_frame # Calculate the starting index for the current frame based on the frame number and samples per frame.
    end_index = start_index + samples_per_frame # Calculate the ending index for the current frame by adding samples per frame to the starting index.
    frame_slice = audio_array[start_index:end_index] # What are we doing here? We are extracting a slice of the audio array that corresponds to the current frame. Describe what "audio_array[start_index:end_index]" is doing, from beginning to end. I mean, how do we read it? We read it as "take the elements of audio_array starting from start_index up to, but not including, end_index.". Why [] ? The square brackets [] are used for indexing and slicing in Python.

    # Clear the figure
    plt.clf()

    # Plot the current slice with amplitude on y and sample index on x
    plt.plot(frame_slice)
    plt.xlabel('Sample Index')
    plt.ylabel('Amplitude')
    plt.title(f'Frame {i:04d} of note.wav') # i:04d means that the frame number will be formatted as a 4-digit integer, with leading zeros if necessary. For example, frame 1 will be displayed as 0001.


    # keep y-axis fixed at -32767 to 32767 on every frame
    plt.ylim(-32767, 32767) # ylim is a function in matplotlib that sets the limits of the y-axis.

    # Save the current frame as a PNG file in the frames/ directory
    plt.savefig(f'frames/frame_{i:04d}.png')



    plt.close()

# ffmpeg -framerate 30 -i frames/frame_%04d.png -i note.wav -c:v libx264 -pix_fmt yuv420p -shortest output.mp4

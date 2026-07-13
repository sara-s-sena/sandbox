sandbox
=======

A personal study repository for low-level programming experiments in C.

sinewave-wav-generator
======================

`note.c` generates a `note.wav` file - a digitally synthesized, monophonic (one note at a time) audio recording of a 15-note melody in A minor.

The program calculates the exact frequency of each musical note using the mathematics of equal temperament (the tuning system where an octave is divided into 12 equal semitones, each a factor of 2^(1/12) apart in frequency), generates sound by computing a sine wave at that frequency (measuring the amplitude of the wave 44,100 times per second), and saves the result as a WAV file by manually writing the 44-byte metadata header that tells any audio player how to interpret the data (sample rate, bit depth, number of channels), followed by the raw sequence of amplitude values.

Why
===

I wanted to see how a programming language creates music from scratch. Math becoming sound.

DEMO
====

[Watch on Youtube](https://youtube.com/shorts/0ry-g9C1UuA?si=wDYRQ_GvoSo7QZpA)

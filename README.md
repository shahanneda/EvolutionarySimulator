# Evolutionary Simulator
## An implementation of the NEAT (Neuroevolution of Augmenting Topologies) algorithm 

This project implements the NEAT algorithm, which is an evolutionary approeach to training neural networks, and provides a GUI that allows visualisation of the algorithm.

The algorithm is impelmented in an abstract way that allows any type of task to be plugged in.
Currently, there is a Snake and XOR task.


Written in pure C++, with no external dependencies relating to the neural networks / evolution.
GUI made using ImGUI/OpenGL/WebGL, can run both in the browser using web assembly, and locally.

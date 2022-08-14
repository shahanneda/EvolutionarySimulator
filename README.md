# Evolutionary Simulator
## An implementation of the NEAT (Neuroevolution of Augmenting Topologies) algorithm 
![image](https://user-images.githubusercontent.com/17485954/184552404-6c99ba69-5545-4a8b-9515-2ff747309405.png)

[Run the simulator online running in assembly by clicking this link](https://shahan.ca/EvolutionarySimulator/)

This project implements the NEAT algorithm, which is an evolutionary approeach to training neural networks, and provides a GUI that allows visualisation of the algorithm.

The algorithm is implemented in an abstract way that allows any type of task to be plugged in.
Currently, there is a Snake and XOR task.


Written in pure C++, with no external dependencies relating to the neural networks / evolution.
GUI made using ImGUI/OpenGL/WebGL, can run both in the browser using web assembly, and locally. It is much faster when running natively compared to in web assembly.


<!-- ![image](https://user-images.githubusercontent.com/17485954/184552414-a5f3c04c-23a7-4d09-937a-49cc12e7f15d.png) -->

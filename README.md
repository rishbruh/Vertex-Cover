# Vertex Cover Problem

This repo contains files related to Vertex cover problem covered in the graduate course ECE650 @ UWaterloo


The idea is to help the local police department minimize their installation of security cameras at traffic intersections - based on Vertex Cover problem

Languages: Python, C++
Multithread
Cmake
MiniSAT
Linux
Multiprocessing

a) A1 deals with gathering GPS Coordinate Input of the Streets and Calculating the Intersections (Using Vertices and Edges Concept of an Undirected Graph) (Python)

b) A2 deals with Given a Set of Street Coordinates in the form of Vertices,Edges We used the BFS Algorithm to find the shortest path between two Vertices in the Graph. (C++)

c) A3 has a random generator to generate "legal" street coordinates as input to our Python program from assignment1. The Output from Assignment1 was provided to the Input of Assignment2 to calculate the shortest path between any two vertices. We incorporate Multi-threaded programming, IPC(Inter-Process Communication) using Pipes to connect the Standard Output,Input of various programs. (C++,Python)

d) In A4 we are asked to solve the Vertex cover problem using CNF-SAT solver

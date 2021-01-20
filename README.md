# Generic Problem Solving Server

Provides a generic implemantion of a server using sockets and multi-threading.
The Solver inetrface specifies the methods for The "Problem" and "Solution" using The ClientHandler which is an API for handaling Streams of data recived by the socket.

This project was built based on the SOLID design pattrem priniciples and provides an easy way for managing server-side comunication.

Implementing the search for the shortest path by checking with a few algorithms such as: A*, BFS, DFS and BestFs.
In addition, creating an empirical experiment and comparing the algorithms results.

To Compile:
````
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
 ````
Add the PORT number while running the program.

git: https://github.com/KarinShimel/searchAlgo.Comp .

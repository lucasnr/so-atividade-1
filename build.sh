#!/bin/bash

g++ src/auxiliar.cpp -o dist/auxiliar
g++ src/sequencial.cpp -o dist/sequencial
g++ -pthread src/threads.cpp -o dist/threads
g++ src/processos.cpp -o dist/processos
echo "Done"

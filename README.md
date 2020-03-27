Name: Youssef Hussein
Class: CSC284 
Assignemnt 4

description:
Using sigment trees constructed from a list of sorted integer for the end points of interevals. Then performs Insertion and Deletion operation on the interevals using the data structure. The output isthe length of the interival of the output

challenges:
The code comiles successfully and runs on the small example test case in file in0.txt; however when run on bigger test cases the Insertion operation seems to pass successfully but the deletion doesn't seem to work as intented.


build:
mkdir -p build
cd build
cmake ..
make 
./exec < <input_file> > <output_file>
diff <output_file> <answer_key>


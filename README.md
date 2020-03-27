Name: Youssef Hussein
Class: CSC284 
Assignemnt 4

description:
Using sigment trees constructed from a list of sorted integer for the end points of interevals. Then performs Insertion and Deletion operation on the interevals using the data structure. The output isthe length of the interival of the output

challenges: the code passes all the test cases successfully

build:
mkdir -p build
cd build
cmake ..
make 
./exec < <input_file> > <output_file>
diff <output_file> <answer_key>


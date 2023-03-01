#include<iostream>
#include "main.h"
// Vector class which can be useful for taking x,y,z and applying vector properties on them.

int main(){

    std::cout<<"Four Vector Analysis\n";
    
    // Taking Input parameters
    std::string datafile;
    std::string distribution;
    int number_of_bins;
    double xmin;
    double xmax;
    std::cout<<"Enter data file name : ";
    std::cin>>datafile;
    std::cout<<"Enter distribution type : ";
    std::cin>>distribution;
    std::cout<<"Number of Bins : ";
    std::cin>>number_of_bins;
    if(number_of_bins==0){
        std::cout<<"Number of Bins cannot be 0\n";
        exit(1);
    }
    std::cout<<"Enter X(min) for the histogram : ";
    std::cin>>xmin;
    std::cout<<"Enter X(max) for the histogram : ";
    std::cin>>xmax;

    // Initialize the Reader class which will read the data from the input file.
    Reader reader(datafile);
    // A variable which will be a vector of Datatype FourVector stores the file content.
    std::vector<FourVector> data = reader.readFile();
    // An output class which performs computations to produce the 1D Histogram of given data.
    Output output(data,number_of_bins,xmin,xmax,distribution);
    // Calling out the output system for running Histogram simulation.
    output.histogram();
    return 0;
}

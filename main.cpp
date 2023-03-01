#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include <cassert>

// Vector class which can be useful for taking x,y,z and applying vector properties on them.
class Vector {
    private:
        double x;
        double y;
        double z;
    
    public:
        Vector(double _x, double _y, double _z){
            x = _x;
            y = _y;
            z = _z;
        }

        // Getter functions in case we need them. 
        double x_vector_value(){
            return x;
        }
        double y_vector_value(){
            return y;
        }
        double z_vector_value(){
            return z;
        }

        // Calculate Magnitude of given vector.
        double magnitude(){
            return std::sqrt(x*x+y*y+z*z);
        }
};

// FourVector class which inherits the Vector class and adds energy value to it.
class FourVector: public Vector {
    private :
        double e;

    public:
        FourVector(double _x, double _y, double _z, double _e):Vector(_x,_y,_z){
            e = _e;
        }

        // Getter function in case we need them.
        double e_vector_value(){
            return e;
        }

        // Calculating the mass of given vector.
        double mass_of_vector(){
            return std::sqrt(e*e-(pow(x_vector_value(),2)+pow(y_vector_value(),2)+pow(z_vector_value(),2)));
        }
};

/* Reader class which takes a fileName and reads the data from the file and 
   interprets the data into FourVector datatype. 
*/
class Reader {
    private :
        std::string fileName;
    
    public :
        Reader(std::string _fileName){
            fileName = _fileName;
        }

        std::vector<FourVector> readFile(){
            std::vector<FourVector> data;
            std::ifstream infile(fileName);

            if(!infile.is_open()){
                std::cout<<"Could not open file\n";
                return data;
            }   

            double x,y,z,e;
            while(infile>>x>>y>>z>>e){
                FourVector input(x,y,z,e);
                data.push_back(input);
            }
            infile.close();
            return data;
        }
};

class Writer {
    public : 
    void writeFile(std::vector<double> X,std::vector<double> Y) {
            std::ofstream outfile("output.dat");
            if(!outfile.is_open()){
                std::cout<<"Could not open file\n";
                return;
            }   

            for (int i=0; i<X.size(); i++) {
                outfile << X[i] << " " <<Y[i] << std::endl;
            }
        }
};
// Output class for performing required modifications and running simulations.
class Output{
    private :
        std::vector<double> bins;
        std::vector<int> frequency;
        int total_bins;
        double xmin;
        double xmax;
        double bin_width;
        std::string distribution;
        std::vector<FourVector> data;
    public :
        Output(std::vector<FourVector> &_data, int _total_bins, double _xmin, double _xmax, std::string _distribution){
            total_bins = _total_bins;
            xmin = _xmin;
            xmax = _xmax;
            distribution = _distribution;
            data = _data;
            bin_width = (xmax-xmin)/total_bins;
            for (int i=0; i<total_bins; i++){
                bins.push_back(xmin + i*bin_width);
                frequency.push_back(0);
            }
            for (auto it = data.begin(); it != data.end(); it++){
                double x = it->e_vector_value();
                if(x>xmin && x<xmax){
                    frequency[(x-xmin)/bin_width]++;
                }
            }
        }

        // Functions for calculating individual distributions.
        double distribution_pT(std::vector<FourVector>::iterator it){
            double pX = it->x_vector_value();
            double pY = it->y_vector_value();
            double pZ = it->z_vector_value();
            return std::sqrt(pX*pX + pY*pY + pZ*pZ);  
        }
        double distribution_pX(std::vector<FourVector>::iterator it){
            double pX = it->x_vector_value();
            return pX;
        }
        double distribution_pY(std::vector<FourVector>::iterator it){
            double pY = it->y_vector_value();
            return pY;
        }
        double distribution_pZ(std::vector<FourVector>::iterator it){
            double pZ = it->z_vector_value();
            return pZ;
        }
        double distribution_energy(std::vector<FourVector>::iterator it){
            double pE = it->e_vector_value();
            return pE;
        }
        double distribution_mass(std::vector<FourVector>::iterator it){
                    double pM = it->mass_of_vector();
                    return pM;
        }
        void distribution_unavailable(){
            std::cout<<"The requested distribution is unavailable\n";
            exit(1);
        }
        
        // Getter function
        int getDistributionIndex(){
            if(distribution == "pT"){
                return 0;
            }else if(distribution == "pX"){
                return 1;
            }else if(distribution == "pY"){
                return 2;
            }else if(distribution == "pZ"){
                return 3;
            }else if(distribution == "energy"){
                return 4;
            }else if(distribution == "mass"){
                return 5;
            }
            return -1;
        }

        // Histrogram function
        void histogram(){
            std::cout<<"Creating Histogram...\n";
            // Indexing Distributions to get equivalent mapping parameter which could further be utilized in switch-case
            int distributionIndex = getDistributionIndex();
            // Vectors to store X and Y axis values.
            std::vector<double> X; // Bincenter based on distribution
            std::vector<double> Y; // Probability
            for(int i=0; i<total_bins; i++){
                double bincenter = (bins[i]+bins[i+1])/2;
                for (auto it = data.begin(); it != data.end(); it++){
                    double p_distribution;
                    switch(distributionIndex){
                        case 0:
                            p_distribution = distribution_pT(it); // For each iteration we get corresponding distribution quantity.
                            break;
                        case 1:
                            p_distribution = distribution_pX(it);
                            break;
                        case 2:
                            p_distribution = distribution_pY(it);
                            break;
                        case 3:
                            p_distribution = distribution_pZ(it);
                            break;
                        case 4:
                            p_distribution = distribution_energy(it);
                            break;
                        case 5:
                            p_distribution = distribution_mass(it);
                            break;
                        default:
                            distribution_unavailable();
                    }   
                    // Count the occurance for a specified distribtuion.
                    if(p_distribution>bincenter-bin_width/2 && p_distribution<=bincenter+bin_width/2){
                        frequency[i]++;
                    }
                }
                // Finding probablity of occurance.
                double probability = frequency[i] / (double)(data.size()*bin_width);
                X.push_back(bincenter);
                Y.push_back(probability);
            }
            // Writing the output to a data file. 
            Writer output;
            output.writeFile(X,Y);
            std::cout<<"Output has been written successfully into output.dat file\n";
        }
};


void test_all() {

    // Test Vector class
    Vector v(1.0, 2.0, 3.0);
    assert(v.x_vector_value() == 1.0);
    assert(v.y_vector_value() == 2.0);
    assert(v.z_vector_value() == 3.0);
    assert(v.magnitude() == std::sqrt(14.0));

    // Test FourVector class
    FourVector fv(1.0, 2.0, 3.0, 4.0);
    assert(fv.x_vector_value() == 1.0);
    assert(fv.y_vector_value() == 2.0);
    assert(fv.z_vector_value() == 3.0);
    assert(fv.e_vector_value() == 4.0);
    assert(fv.mass_of_vector() == std::sqrt(2.0));

    // Test Reader class
    Reader reader("test.dat");
    std::vector<FourVector> data = reader.readFile();
    assert(data.size() == 3);
    assert(data[0].x_vector_value() == 1.0);
    assert(data[0].y_vector_value() == 2.0);
    assert(data[0].z_vector_value() == 3.0);
    assert(data[0].e_vector_value() == 4.0);
    assert(data[1].x_vector_value() == 5.0);
    assert(data[1].y_vector_value() == 6.0);
    assert(data[1].z_vector_value() == 7.0);
    assert(data[1].e_vector_value() == 8.0);
    assert(data[2].x_vector_value() == 9.0);
    assert(data[2].y_vector_value() == 10.0);
    assert(data[2].z_vector_value() == 11.0);
    assert(data[2].e_vector_value() == 12.0);

    // Test Output class
    Output output(data, 10, 0.0, 20.0, "pT");
    assert(output.getDistributionIndex() == 0);
    assert(output.distribution_pT(data.begin()) == std::sqrt(14.0));
    assert(output.distribution_pX(data.begin()) == 1.0);
    assert(output.distribution_pY(data.begin()) == 2.0);
    assert(output.distribution_pZ(data.begin()) == 3.0);
    assert(output.distribution_energy(data.begin()) == 4.0);
    assert(output.distribution_mass(data.begin()) == std::sqrt(2.0));
}


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

    // Running tests to verify the working for functions.
    test_all();
    return 0;
}

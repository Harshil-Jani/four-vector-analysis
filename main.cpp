#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

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
            // TODO : Apply correct formula. This is just dummy implementation.
            return x_vector_value()+y_vector_value()+z_vector_value()+e_vector_value();
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

// Output class for performing required modifications and running simulations.
class Output{
    private :
        std::vector<double> bins;
        int total_bins;
        double xmin;
        double xmax;
        std::string distribution;

    public :
        Output(std::vector<FourVector> &data, int _total_bins, double _xmin, double _xmax, std::string _distribution){
            total_bins = _total_bins;
            xmin = _xmin;
            xmax = _xmax;
            distribution = _distribution;
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

        // Functions for calculating individual distributions.
        void distribution_pT(){
            std::cout<<"This is alloted to pT distribution\n";
        }
        void distribution_pX(){
            std::cout<<"This is alloted to pX distribution\n";
        }
        void distribution_pY(){
            std::cout<<"This is alloted to pY distribution\n";
        }
        void distribution_pZ(){
            std::cout<<"This is alloted to pZ distribution\n";
        }
        void distribution_energy(){
            std::cout<<"This is alloted to energy distribution\n";
        }
        void distribution_mass(){
            std::cout<<"This is alloted to mass distribution\n";
        }
        void distribution_unavailable(){
            std::cout<<"The requested distribution is unavailable\n";
        }
        
        // Histrogram function
        void histogram(){
            std::cout<<"Creating Histogram...\n";
            int distributionIndex = getDistributionIndex();
            switch(distributionIndex){
                case 0:
                    distribution_pT();
                    break;
                case 1:
                    distribution_pX();
                    break;
                case 2:
                    distribution_pY();
                    break;
                case 3:
                    distribution_pZ();
                    break;
                case 4:
                    distribution_energy();
                    break;
                case 5:
                    distribution_mass();
                    break;
                default:
                    distribution_unavailable();
            }
            // TODO : From here complete the distribution formulae and write the X and Y values in output file.
        }
};

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

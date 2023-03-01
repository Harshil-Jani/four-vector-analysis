#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include <cassert>

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

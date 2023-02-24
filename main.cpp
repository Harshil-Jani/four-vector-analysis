#include<iostream>
#include<cmath>

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

        double x_vector_value(){
            return x;
        }
        double y_vector_value(){
            return y;
        }
        double z_vector_value(){
            return z;
        }

        double magnitude(){
            return std::sqrt(x*x+y*y+z*z);
        }
};

class FourVector: public Vector {
    private :
        double e;
    public:
        FourVector(double _x, double _y, double _z, double _e):Vector(_x,_y,_z),e(_e){}
        
        double e_vector_value(){
            return e;
        }

        double mass_of_vector(){
            // TODO : Know what can be the correct formulation to find mass. As of now, I am writing simple calculations.
            return x_vector_value()+y_vector_value()+z_vector_value()+e_vector_value();
        }
};

int main(){
    Vector data1(1,2,3);
    FourVector data2(1,2,3,4);
    std::cout<<data1.magnitude()<<"\n";
    std::cout<<data2.mass_of_vector()<<"\n";
    std::cout<<"Four Vector Analysis\n";
    return 0;
}
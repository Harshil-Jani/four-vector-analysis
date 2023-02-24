#include<iostream>

class Data {
    private:
        double x;
        double y;
        double z;
        double e;
    
    public:
        Data(double _x, double _y, double _z, double _e){
            x = _x;
            y = _y;
            z = _z;
            e = _e;
        }

        double x_vector(){
            return x;
        }
        double y_vector(){
            return y;
        }
        double z_vector(){
            return z;
        }
        double e_vector(){
            return e;
        }
};
int main(){
    Data data(1,2,3,4);
    std::cout<<data.e_vector()<<"\n";
    std::cout<<"Four Vector Analysis\n";
    return 0;
}
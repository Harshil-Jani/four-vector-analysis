
#include"main.h";

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
    // Test all functions
    test_all();
    std::cout<<"Passed All Tests\n";
    return 0;
}
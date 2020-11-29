// Get the variable limits of g++ compiler on Windows using the numeric_limits class template in the <limits> header

#include <iostream>
#include <limits>  // preprocesser keyword

using namespace std;


template<typename T>  // template allows you to use an undefined type. Would have to declare type when passing a variable in usually
void showMinMax(){
    cout << "Min & Max for variable of type " << typeid(T).name() << endl;
    cout << "Min: " << numeric_limits<T>::min() << endl;  // feed in undefined variable T to the numeric_limits class and take max() function of the object
    cout << "Max: " << numeric_limits<T>::max() << endl;
}

int main(){
    showMinMax<double>();
}
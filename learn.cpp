#include <iostream> // A header file. This line is a prepocessor directive that tells the code to compile its content as well

/*The main function is the entry point of the program. It is where the program starts executing.
The return type of main is int, which means it returns an integer value to the operating system when it finishes executing.
The return value 0 indicates that the program executed successfully.
*/

//namespaces

namespace first{
    int var = 1;// variable of type integer declared
}

namespace second{
    int var = 1;//variale of same name as in the namespace 'first' declared and will pass with no error
}

//variables with the same name will be flagged only if they are in the same namespace

int main(){

    // std - Standard (represents standard namespace)   :: - scope resolution operator (like a pointer)    cout - Character output   endl - End line
    std::cout << "I am bip" << std::endl;
    std::cout << "I like sticks" << '\n'; // \n is better performance wise because it does not flush the output buffer
    /*However here line buffering occurs when we write to terminal, meaning it auto flushes every time it encounters \n
    When writing to files \n does not flush
    Also this comment is a multi-line comment, which is used to write comments that span multiple lines.
    */

    //Variables are declared by providing the type and the name
    int x; // declaration of variable x of type int (integer)
    x = 5; // assignment of value 5 to variable x
    //If several variables share the same name amongst name spaces, namespace must be provided or it will default to main.
    //If not in main then an error will be raised

    //std::cout << first::var;

    // doubles are basically floats from python, they are used to store decimal numbers
    double y = 5.5; // declaration and assignment of variable y of type double (double precision floating point number)

    //characters are used to store single characters, they are enclosed in single quotes
    char z = 'a'; // declaration and assignment of variable z of type char (character)

    //booleans are used to store true or false values
    bool isTrue = true; // declaration and assignment of variable isTrue of type bool (boolean)

    //strings are used to store sequences of characters, they are enclosed in double quotes and are provided by the standard namespace (std)
    std::string name = "bip"; // declaration and assignment of variable name of type std::string (string)

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "z: " << z << std::endl;
    std::cout << "isTrue: " << isTrue << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "Hello, " << name << std::endl;

    //constants are variables whose values cannot be changed after they are initialized. They are declared using the const keyword.
    const int constantValue = 10; // declaration and assignment of constant variable constantValue of type int (integer)
    std::cout << "constantValue: " << constantValue << std::endl;

    return 0;
}
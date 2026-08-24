#include <iostream> // A header file. This line is a prepocessor directive that tells the code to compile its content as well
#include <cmath>//Contains math functions
#include <ctime>//Contains time functions

/*The main function is the entry point of the program. It is where the program starts executing.
The return type of main is int, which means it returns an integer value to the operating system when it finishes executing.
The return value 0 indicates that the program executed successfully.
*/

//typedef - a reserved keyword used to create an additional name (or the 'alias') for a data type. It can help readability and reduce typos
//typedef int integer;

//namespaces
namespace first{
    int namespace_var = 1;// variable of type integer declared
}

namespace second{
    int namespace_var = 2;//variale of same name as in the namespace 'first' declared and will pass with no error
}

//Declaration of function printMessage before main, so it can be used in main without any issues.
//This allows the function to be defined after main, which can help with code organization and readability.
void printMessage(std::string message);//Data type of expected argument specified

//variables with the same name will be flagged only if they are in the same namespace
int main(){

    printMessage("Hello from the printMessage function!");

    //assumes that you are using the standard namespace (but in this case only for string)
    //can be used instead of typedef like: using string = std::string
    using std::string;

    // std - Standard (represents standard namespace)   :: - scope resolution operator (like a pointer)
    // cout - Character output   endl - End line
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

    std::cout << first::namespace_var << std::endl;

    // doubles are basically floats from python, they are used to store decimal numbers
    double y = 5.5; // declaration and assignment of variable y of type double (double precision floating point number)

    //characters are used to store single characters, they are enclosed in single quotes
    char z = 'a'; // declaration and assignment of variable z of type char (character)

    //booleans are used to store true or false values
    bool isTrue = true; // declaration and assignment of variable isTrue of type bool (boolean)

    //strings are used to store sequences of characters, they are enclosed in double quotes and are provided by the standard namespace (std)
    string person = "bip"; // declaration and assignment of variable name of type std::string (string)

    //Output
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "z: " << z << std::endl;
    std::cout << "isTrue: " << isTrue << std::endl;
    std::cout << "name: " << person << std::endl;
    std::cout << "Hello " << person << std::endl;

    //constants are variables whose values cannot be changed after they are initialized. They are declared using the const keyword.
    const int constantValue = 10; // declaration and assignment of constant variable constantValue of type int (integer)
    std::cout << "constantValue: " << constantValue << std::endl;

    //Arithemtic operations are the same as python, with the added operators: '++' or '--' for increments of 1
    //Math functions:

    //std::max(x, y) - gets highest value
    //std::min(x, y) - gets lowest value
    //pow(x, y) - gets x to the power of y
    //sqrt(x) - gets square root of x
    //abs(x) - gets absolute value of x
    //round(x) - rounds x
    //ceil(x) - rounds up x
    //floor(x) - rounds down x


    //type conversion can be both implicit and explicit

    double convertible_var = (int) 3.14;//Explicitly casts 3.14 to an integer by truncating it and then implicitly casts integer to a double
    char letter = 100;//Will implicitly assign 'letter' the character of the given ascii value

    //cout is followed by the insertion operator: <<
    //cin (accepts an input from the user in terminal) is followed by the extraction operatorL >>

    string name;

    std::cout << "What's your name?: ";
    std::cin >> name;
    
    //If statements
    int check;

    //Square brackets can be skipped if there is only one statement
    if(name == "Madhav"){
        std::cout << "You are a kid monkey " << name << std::endl;
        check = 1;
    }
    else if(name == "Navami"){
        std::cout << "Du bist gut genug" << std::endl;
        check = 2;
    }
    else{
        std::cout << "Hello " << name << std::endl;
        check = 0;
    }

    //std::getline(std::cin, name); cin by default only reads up to the first whitespace character. getline reads the entire line until a newline character
    //std::getline(std::cin >> std::ws, name); std::ws discards leading whitespace characters from the input stream before reading the line.

    //Switch case
    switch(check){
        case 1:
            std::cout << "You happy?" << std::endl;
            break;
        case 2:
            std::cout << "Du bist gut genug" << std::endl;
            break;
        default:
            std::cout << "How are you today" << std::endl;
    }

    //ternary operators
    int age;
    std::cout << "How old are you?: ";
    std::cin >> age;

    // Ternary operator example
    string result = (age >= 18) ? "You are an adult." : "You are not an adult.";//Colon acts as an else statement, and the question mark acts as an if statement
    std::cout << result << std::endl;

    //Logical operators
    //The exact same as java
    // && - logical AND
    // || - logical OR
    // ! - logical NOT

    //string methods
    string str = "Hello, World!";
    std::cout << "Length of str: " << str.length() << std::endl;
    std::cout << "Substring of str: " << str.substr(7, 5) << std::endl; // Extracts substring starting at index 7 with length 5
    std::cout << "Is str empty: " << str.empty() << std::endl; // Checks if string is empty
    std::cout << "Character at index 1: " << str.at(1) << std::endl; // Accesses character at index 1
    std::cout << "Find 'World' in str: " << str.find("World") << std::endl; // Finds the index of substring "World"
    std::cout << "Replace 'World' with 'C++': " << str.replace(str.find("World"), 5, "C++") << std::endl; // Replaces substring "World" with "C++"
    std::cout << "Modified str: " << str << std::endl; // Displays modified string
    std::cout << "Append '!!!' to str: " << str.append("!!!") << std::endl; // Appends "!!!" to the end of the string
    std::cout << "Final str: " << str << std::endl; // Displays final string
    std::cout << "Insert 'C++ ' at index 7: " << str.insert(7, "C++ ") << std::endl; // Inserts "C++ " at index 7
    std::cout << "Final str after insert: " << str << std::endl; // Displays final string after insert
    std::cout << "Erase 'C++ ' from str: " << str.erase(7, 4) << std::endl; // Erases 4 characters starting from index 7
    std::cout << "Final str after erase: " << str << std::endl;
    str.clear(); // Clears the string
    std::cout << "Clear str: " << str << std::endl; // Clears the string
    std::cout << "Final str after clear: " << str << std::endl;

    //While loops
    int count = 0;
    while(count < 5){
        std::cout << "Count: " << count << std::endl;
        count++;
    }

    //Do while loops (Executes the code once and then checks the condition)
    int do_count = 0;
    do{
        std::cout << "Do Count: " << do_count << std::endl;
        do_count++;
    }while(do_count < 5);

    //For loops
    for(int i = 0; i < 5; i++){//First statement is the initialization, second is the condition, and third is the increment/decrement
        std::cout << "For Count: " << i << std::endl;
    }

    //'continue' skips the current iteration of the loop and moves to the next iteration

    //Random number generation (pssuedo-random, not truly random)
    srand(time(NULL)); // Seed the random number generator with the current time
    int random_number = rand() % 100 + 1; // Generate a random number between 1 and 100
    std::cout << "Random number: " << random_number << std::endl;

    //Arrays are a collection of elements of the same type, stored in contiguous memory locations. They can be accessed using an index.
    int arr[] = {1, 2, 3, 4, 5}; // declaration and initialization of an array of integers with 5 elements
    std::cout << "Array elements: ";
    for(int i = 0; i < 5; i++){
        std::cout << arr[i] << " "; // Accessing array elements using index
    }
    std::cout << std::endl;
    
    //sizeof() operator returns the size of a variable or data type in bytes. It can be used to determine the size of an array.
    std::cout << "Size of arr: " << sizeof(arr) << " bytes" << std::endl;
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Size of double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
    std::cout << "Size of bool: " << sizeof(bool) << " bytes" << std::endl;

    //for-each loop (range-based for loop) introduced in C++11, allows you to iterate over elements of a container (like an array) without using an index.
    std::cout << "For-each loop: ";
    for(int element : arr){
        std::cout << element << std::endl; // Accessing array elements directly
    }

    //multidimensional arrays are arrays of arrays, allowing you to create a grid or matrix-like structure. They can be accessed using multiple indices.
    int multi_arr[2][3] = {{1, 2, 3},
                           {4, 5, 6}}; // declaration and initialization of a 2D array (2 rows and 3 columns)
    std::cout << "Multidimensional array elements: " << std::endl;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            std::cout << multi_arr[i][j] << " "; // Accessing 2D array elements using row and column indices
        }
        std::cout << std::endl;
    }

    //Pointers are variables that store the memory address of another variable.
    // They are declared using the '*' operator and can be dereferenced using the same operator.
    int num = 42; // declaration and assignment of variable num of type int (integer)
    int* ptr = &num; // declaration and assignment of pointer variable ptr that stores the address of num using the address-of operator '&'
    std::cout << "Value of num: " << num << std::endl;
    std::cout << "Address of num: " << ptr << std::endl; // Displaying the memory address stored in ptr
    std::cout << "Value at address stored in ptr: " << *ptr << std::endl; // Dereferencing ptr to access the value of num

    //Passing by reference allows you to pass the address of a variable to a function, allowing the function to modify the original variable.
    // This is done using the '&' operator in the function parameter list.
    int original = 10; // declaration and assignment of variable original of type int (integer)
    std::cout << "Original value before function call: " << original << std::endl;
    // Function that takes an integer reference as a parameter and modifies its value
    auto modifyValue = [](int& ref) { // Lambda function that takes an integer reference
        ref += 5; // Modifies the original variable by adding 5
    };
    modifyValue(original); // Calling the function and passing the original variable by reference
    std::cout << "Original value after function call: " << original << std::endl;

    //Const parameters are used to prevent a function from modifying the value of the argument passed to it.
    // This is done by adding the 'const' keyword before the parameter type in the function declaration.
    auto printConstValue = [](const int& ref) { // Lambda function that takes a constant integer reference
        std::cout << "Value inside function: " << ref << std::endl; // Prints the value of the constant reference
        // ref += 5; // This line would cause a compilation error because ref is a constant reference and cannot be modified
    };
    printConstValue(original); // Calling the function and passing the original variable by constant reference

    //Nullptr is a keyword introduced in C++11 that represents a null pointer. It is used to indicate that a pointer does not point to any valid memory address.
    // Using nullptr instead of NULL or 0 improves type safety and avoids ambiguity in pointer assignments.
    ptr = nullptr; // Declaring a pointer and initializing it to nullptr
    //It is important to check if a pointer is nullptr before dereferencing it to avoid undefined behavior or segmentation faults.
    if(ptr == nullptr){ // Checking if the pointer is nullptr
        std::cout << "Pointer is null." << std::endl; // Prints a message
    } else {
        std::cout << "Pointer is not null." << std::endl; // This line will not be executed in this case
    }

    //Function templates allow you to create functions that can operate on different data types without having to write multiple versions of the same function.
    // This is done using the 'template' keyword followed by a template parameter list.
    //template <typename T> // Template declaration with a type parameter T
    //auto add = [](T a, T b) { // Lambda function that takes two parameters of type T and returns their sum
    //    return a + b; // Returns the sum of a

    return 0;
}

//Functions can be declared and defined outside of main, but must be declared before they are used in main.
// They can also be declared and defined inside main, but this is not recommended for readability and maintainability.

//This function is after main, but is declared before main, so it can be used in main without any issues.

void printMessage(std::string message){//Function that takes a string as an argument to the parameter 'message' and prints it to the console
    std::cout << message << std::endl;
}

//Function overloading is a feature in C++ that allows you to have multiple functions with the same name but different parameter lists.
// The compiler determines which function to call based on the arguments passed to the function.
// This can make your code more readable and easier to maintain, as you can use the same function name for similar operations.

//Variable scope in C++ is limited within its block or function and cannot be called outside that scope.
//However, variables declared in a namespace can be accessed outside of that namespace.
// This is done using the scope resolution operator (::) followed by the namespace name and the variable name.
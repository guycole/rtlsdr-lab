#include <iostream>
#include <string>

#define DEFAULT_BUFFER_LENGTH 512

uint8_t bitbuffer[DEFAULT_BUFFER_LENGTH] = {0};
uint8_t *bitptr;

void decode(const std::string& buffer) {
    std::cout << buffer << std::endl;

    // buffer looks like "*f6d8c9833540611d6ebdee841425;"
    // test for "*"" and ";" 
    std::size_t asterisk = buffer.find("*");
    if (asterisk == std::string::npos) {
        std::cout << "not found x" << std::endl;
        // error
    }

    std::size_t semicolon = buffer.find(";");
    if (semicolon == std::string::npos) {
        std::cout << "not found ;" << std::endl;
        // error
    }

    // remove the * and ;
    std::string temp_string = buffer.substr(asterisk + 1, semicolon - asterisk - 1);

    int limit = temp_string.length();
    char* char_array = new char[limit + 1];

    strcpy(char_array, temp_string.c_str()); 
    for (int ii = 0; ii < limit; ii++) { 
        std::cout << char_array[ii]; 
    } 

    std::cout << std::endl;

/*
    // convert hex string to binary
    std::fill(std::begin(bitbuffer), std::end(bitbuffer), 0);

   
    int ndx1 = limit-1;
    std::size_t ndx2 = 0;

    while (ndx1 >= 0) {
        std::cout << temp_string[ndx1] << std::endl;
        ndx2 = ndx1;
        std::string buffer2 = temp_string.substr(ndx1, 1);

        int num = std::stoi(buffer2, 0, 16);
        std::cout << "converted:" << num << std::endl;
        ndx1--;
    }
*/
/*
    std::cout << candidate << std::endl;
    std::cout << candidate.length() << std::endl;

    for (std::size_t ii = 0; ii < candidate.length(); ii++) {
        std::cout << candidate[ii] << std::endl;
    }
    */

// 89a30f8d58b982abf57364e2ea61
// 1000 1 001 

    // 1111 0 110 
// 2 4 8 16 = 30 // 6

// 801e31
// 1000 0 000 
// 16 / 0

// 81a98e
// 1000 0 001 
// 16 / 1

// 822152f
// 1000 0 010

    //string r = s1.substr(3, 2);

    //std::string s = "5f0066";
    //int num = std::stoi(buffer, 0, 16);
    //std::cout << num << "\n";
}

int main(int argc, char* argv[]) {
    std::string buffer = "*8da2;";

    while (std::getline(std::cin, buffer)) {
        if (buffer.empty()) {
            break;
        }

        decode(buffer);
    }

    return 0;
}
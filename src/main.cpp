#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include <zlib.h>
#include <openssl/sha.h>

int main(int argc, char** argv) {

    
    if (argc < 2){
        std::cerr <<    
                "usage: nanogit <command> [<args>]\n"
                "\n"
                "commands:\n"
                "  init [path]    Create an empty nanogit repository\n";

                return 0;
    }

    return 0;
}
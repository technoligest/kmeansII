#include "handlers/inputArguments.hh"



int main(int argc, char **argv) {
    Argument args;
    if (!args.parse_args(argc, argv))
        return 1;
//    if (args.decorate)
//        std::cout << "==================" << std::endl;
////    for (int i = 0; i < args.times; i ++)
////        std::cout << args.content << " " << args.name << "!" << std::endl;
//    if (args.decorate)
//        std::cout << "==================" << std::endl;

    return 0;
}
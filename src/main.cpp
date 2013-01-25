
#include <functional>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <istream>
#include <exception>
#include <array>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "geometry.hpp"
#include "linear_algebra.hpp"

#include "forth.hpp"

namespace po = boost::program_options;

int main(int argc, char const * const * const argv)
{
    using namespace std;
    
    auto t = Object::makeTriangle(Math::vec3(0, -.6, 11), 
                                    Math::vec3(-.5, -.5, 11),
                                    Math::vec3(0.5, -.5, 11));
                                    
    auto r = Object::makeRay(Math::vec3(0.0, 0.0, 0.0),
                             Math::vec3(0.0, 0.0, 1.0));
                             
    auto mi = Object::test_intersection(t, r);

    if (get<0>(mi))
    {
        cout << "Have intersection: " << get<1>(mi) << endl;
    }
    else
        cout << "No intersection" << endl;
    
#if 0
    using namespace std;
    using namespace boost::filesystem;
    
    // input file
    string ifile;
    
    
    istream *input = nullptr;
    bool prompt = true;
    
    
    try 
    {
        // test for program options
        po::options_description desc("options");
        desc.add_options()
            ("help,h", "display options")
            ("version,v", "displays version")
            ("input-file,i", po::value<string>(&ifile), "input file");

        po::variables_map vm;

        po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);

        po::notify(vm);

        // has user asked for the version number?
        if (vm.count("version"))
        {
            cout << "RayForth A1" << endl;
            return 0;
        }
        // has user asked for parameter help?
        if (vm.count("help"))
        {
            cout << "RayForth A1" << endl << endl;
            cout << "ray <options>" << endl;
            cout << desc << endl;
            return 0;
        }
        
        // has user given us an input file?
        if (vm.count("input-file"))
        {
            path p(ifile);
            // if selected -, then use cin
            if (ifile == "-")
            {
                input = &cin;
                prompt = false;
            }
            else           
            // check to see if the file exists
            if (exists(p) and (is_regular_file(p) or is_symlink(p)))
            {
                input = new ifstream(ifile);
                prompt = false;
            }
            else
            {
                cerr << "The file " << ifile << "is not found." << endl;
                return 1;
            }
        }
        else
        {
            input = &cin;
            prompt = true;
        }
    }
    catch(exception& e) {
        cerr << e.what() << "\n";
    }
    catch (...)
    {
        cerr << "error\n";
    }
    
    cerr << "RayForth 0.3  Copyright (C) 2012 Jeffrey Drake\n";
    cerr << "RayForth comes with absolutely no warranty.\n";
    cerr << "Type 'bye' to exit." << endl;
    
    // process
    Forth::executeForth(*input);
    
    if (input != &cin)
    {
        delete input;
    }
    
    if (prompt) {} // eliminate warnings

    std::cout << std::endl;
 #endif
    return 0;
}

#include <functional>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <istream>
#include <exception>
//#include <glm/glm.hpp>
#include <array>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "geometry.hpp"

namespace po = boost::program_options;

#include "gd.h"

int main(int argc, char const * const * const argv)
{
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
            cerr << "// 0"<< endl;
        po::variables_map vm;
        cerr << "//0s" << endl;
//        auto xx = po::parse_command_line(argc, argv, desc);
        cerr << "//0b" << endl;
        po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
//        po::store(xx, vm);
        cerr << "// 1" << endl;
        po::notify(vm);
        cerr << "// 2x" << endl;
        return 0;
        cerr << "// 2" << endl;            
        // has user asked for the version number?
        if (vm.count("version"))
        {
            cout << "RayForth A1" << endl;
            return 0;
        }
        cerr << "// 3" << endl;
        // has user asked for parameter help?
        if (vm.count("help"))
        {
            cout << "RayForth A1" << endl << endl;
            cout << "ray <options>" << endl;
            cout << desc << endl;
            return 0;
        }
        cerr << "// 4" << endl;
        
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
    }
    catch(exception& e) {
        cerr << e.what() << "\n";
    }
    catch (...)
    {
        cerr << "error\n";
    }
    
    // process
    
    if (input != &cin)
    {
        delete input;
    }
    
    
    
/*    
    
    std::cout << "Ray A1" << std::endl;
    
    std::vector<Object::MaybeIntersection> image;
    unsigned width = 640;
    unsigned height = 640;
    unsigned total = width * height;
    image.reserve(total);
    Math::Vec3 direction = Math::vec3(0, 0, 1.0);
    
    auto object = Object::makeSphere(Math::vec3(0.5, 0.5, 0.5), 0.25);
//    auto object = Object::makeTriangle(Math::vec3(0.45, 0.45, 0.5),
//                                       Math::vec3(0.55, 0.45, 0.5),
//                                       Math::vec3(0.65, 0.55, 0.5));
    
    for (unsigned i = 0; i != total; ++i)
    {
//        std::cout << "Hit testing: " << 
//            static_cast<int>((static_cast<float>(i+1) / static_cast<float>(total)) * 100) << "%\r";
        unsigned x = i % width;
        unsigned y = (height - i / width);
        
        float fx = static_cast<float>(x) / static_cast<float>(width);
        float fy = static_cast<float>(y) / static_cast<float>(height);
        
        auto r = Object::makeRay(Math::vec3(fx, fy, 0.0f), direction);
        auto is = Object::test_intersection(object, r);
        
        image.push_back(is);
    }
    
    // output boolean hit test
    std::vector<int> boolimg(image.size());
    std::transform(std::begin(image), std::end(image),
        std::begin(boolimg), Object::intersection_index);
        
    gdImagePtr im2 = gdImageCreate(width, height);
    int black = gdImageColorAllocate(im2, 0, 0, 0);
    int white = gdImageColorAllocate(im2, 255, 255, 255);
    
    for (unsigned x = 0; x != width; ++x)
        for (unsigned y = 0; y != height; ++y)
        {
            gdImageSetPixel(im2, x, y, (boolimg[y*width+x] == 0 ? black : white));
        }
    
    FILE *out = fopen("output2.png", "wb");
    gdImagePngEx(im2, out, 9);
    fclose(out);
    gdImageDestroy(im2);


    // output gray scale 
    std::vector<std::array<uint8_t, 3>> boolgs(image.size());
    std::transform(std::begin(image), std::end(image),
        std::begin(boolgs), Object::intersection_colour);
        
    gdImagePtr im3 = gdImageCreateTrueColor(width, height);

    for (unsigned x = 0; x != width; ++x)
        for (unsigned y = 0; y != height; ++y)
        {
            std::array<uint8_t, 3> c = boolgs[y * width + x];
//            if (c[0] != 0)
//                std::cerr << "Colour: " << c << std::endl;
            int colour = gdImageColorAllocate(im3, c[0], c[1], c[2]);
            gdImageSetPixel(im3, x, y, colour);
        }
    
    FILE *out2 = fopen("output3.png", "wb");
    gdImagePngEx(im3, out2, 9);
    fclose(out2);
    gdImageDestroy(im3);


 */   
    std::cout << std::endl;
 
    return 0;
}
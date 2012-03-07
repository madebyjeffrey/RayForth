
#include <functional>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <fstream>
//#include <glm/glm.hpp>
#include <array>

#include "geometry.hpp"
//#include "scene.hpp"

// Set CImg environment
#define cimg_display 0

#include "CImg.h"

int main(int argc, char const * const * const argv)
{
    std::cout << "Ray A1" << std::endl;
    
    std::vector<Object::MaybeIntersection> image;
    unsigned width = 320;
    unsigned height = 240;
    unsigned total = width * height;
    image.reserve(320 * 240);
    Math::Vec3 direction = Math::vec3(0, 0, 1.0);
    
    auto object = Object::makeSphere(Math::vec3(0.5, 0.5, 0.5), 0.25);
    
    for (unsigned i = 0; i != total; ++i)
    {
        std::cout << "Hit testing: " << 
            static_cast<int>((static_cast<float>(i+1) / static_cast<float>(total)) * 100) << "%\r";
        unsigned y = i % width;
        unsigned x = i / width;
        
        float fx = static_cast<float>(x) / static_cast<float>(width);
        float fy = static_cast<float>(y) / static_cast<float>(height);
        
        auto r = Object::makeRay(Math::vec3(fx, fy, 0.0f), direction);
        auto is = Object::test_intersection(object, r);
        
        image.push_back(is);
    }
    
    std::cout << std::endl;
    
    std::cout << "Rendering image." << std::endl;
    
    std::vector<std::array<uint8_t, 3>> rendered(image.size());
    std::transform(std::begin(image), std::end(image),
                   std::back_inserter(rendered), Object::intersection_colour);
  
      using namespace cimg_library;
      
//      CImg< T > & 	draw_point (const int x0, const int y0, const tc *const color, const float opacity=1)
//      Draw a 2d colored point (pixel). 
//      unsigned char *d = (unsigned char*)(rendered.data());
//    unsigned char pixel[3] = { 0xff, 0, 0};
    std::array<unsigned char, 3> pixel = { 0xff, 0, 0};
    
    CImg<unsigned char> output(width, height, 1, 3, pixel.data());
    for (size_t i = 0; i < image.size(); ++i)
    {
        std::cout << "Output pixel: " << std::setw(9) << i+1 << "\r";
        output.draw_point<uint8_t>(i % width, i / width, rendered[i].data());
}
    output.save_png("output.png");
 
     std::cout << std::endl;       
    
        

//      CImg<unsigned char> output(d, width, height, 1, 4);
//      output.save_png("output.png");
      
      
  /*  
    size_t tot = total * 4;
//    unsigned char *memory = new unsigned char[tot];
    unsigned char *d = (unsigned char*)(rendered.data());
  
      unsigned result = LodePNG_encode32_file("output.png", d, width, height);
      if (result == 0)
          std::cout << "File saved to output.png" << std::endl;
      else std::cout << "Had an error." << std::endl;
    */
//    unsigned LodePNG_encode32_file(const char* filename, const unsigned char* image, unsigned w, unsigned h);
//    unsigned result = LodePNG_encode32(&memory, &tot, d, width, height);
  /*  
    if (result == 0)
    {
        std::ofstream file("output.png");
        
        std::copy(memory, memory + tot, std::ostream_iterator<unsigned char>(file));
        
        std::cout << "File output: output.png" << std::endl;
    }
     
    delete memory;
    */
/*    auto r = Object::makeRay(Math::vec3(0.5 - 0.006855609620524, 0.5, 0.0), Math::vec3(0, 0, 1.0));
    
    auto i = Object::test_intersection(s, r);
    
    std::cout << "Sphere intersection of Ray: ";
    
//    auto scene = makeScene(320, 240, s);
    
    if (i == Object::nullIntersection())
        std::cout << "no intersection" << std::endl;
    else
    {
        auto intersection = std::get<1>(i);
        auto point = std::get<0>(intersection);
        auto angle = std::get<1>(intersection);
        
        std::cout << "intersection at " << point << " with angle " << angle << std::endl;
    }
  */      
    return 0;
}
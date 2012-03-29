
#include <istream>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <list>
#include <utility>
#include <map>
#include <sstream>
#include <functional>

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/variant/static_visitor.hpp>

#include "forth.hpp"

#include "forth_words.hpp"

#include "linear_algebra.hpp"
#include "geometry.hpp"

#include "gd.h"


namespace Forth
{
	// Makes a vec3
	Status vec3(Stack &stack)
	{
		using namespace boost;
	
		if (stack.size() < 3)
		{
			return std::make_tuple(false, "Stack underflow. vec3 requires three numbers.");
		}
	
		try 
		{
			double z = get<double>(pop(stack));
			double y = get<double>(pop(stack));
			double x = get<double>(pop(stack));		
	
			Math::Vec3 v = Math::vec3(x,y,z);
	
			push(stack, v);
		}
		catch (bad_get)
		{
			return std::make_tuple(false, "Data type mismatch. vec3 requires three numbers.");
		}
	
		return std::make_tuple(true, "");
	}
	
	// needs a vec3 and a number
	Status makeSphere(Stack &stack)
	{
		using namespace boost;
		
		if (stack.size() < 2)
			return std::make_tuple(false, "Stack underflow. make-sphere requires a vec3 and a number.");
		
		auto x = pop(stack);
		auto y = pop(stack);
		
		try 
		{
			Math::Vec3 v = get<Math::Vec3>(x);
			double d = get<double>(y);
		
			auto s = Object::makeSphere(v, d);
			push(stack, s);
		}
		catch (bad_get)
		{
			// Might be in different order...
			try
			{
				Math::Vec3 v = get<Math::Vec3>(y);
				double d = get<double>(x);
				
				auto s = Object::makeSphere(v, d);
				push(stack, s);
				goto end;
			}
			catch (bad_get)
			{		
				return std::make_tuple(false, "Data type mismatch. make-sphere requires a vec3 and a number.");
			}
			
			return std::make_tuple(false, "Data type mismatch. make-sphere requires a vec3 and a number.");
		}
		end:
		return std::make_tuple(true, "");
	
	}

	// needs a 3x vec3 
	Status makeTriangle(Stack &stack)
	{
		using namespace boost;
		
		if (stack.size() < 3)
			return std::make_tuple(false, "Stack underflow. make-triangle requires a three vec3s.");
		
		try 
		{
			Math::Vec3 v1 = get<Math::Vec3>(pop(stack));
			Math::Vec3 v2 = get<Math::Vec3>(pop(stack));
			Math::Vec3 v3 = get<Math::Vec3>(pop(stack));
		
			auto s = Object::makeTriangle(v1, v2, v3);
			push(stack, s);
		}
		catch (bad_get)
		{
			return std::make_tuple(false, "Data type mismatch. make-triangle requires a three vec3s.");
		}
		return std::make_tuple(true, "");
	
	}

 	// Stack: Triangle/Sphere Width Height OutputFile -- 
	Status renderScene(Stack &stack)
	{
		using namespace boost;
		
		if (stack.size() < 4)
			return std::make_tuple(false, "Stack underflow. render-scene requires: Triangle/Sphere Width Height OutputFile.");
		
		try 
		{
			std::string file = get<std::string>(pop(stack));
			double h = get<double>(pop(stack));
			double w = get<double>(pop(stack));
			auto object = pop(stack);
			
			std::vector<Object::MaybeIntersection> image;
			std::function<Object::MaybeIntersection(Object::Ray)> intersect;
			
			unsigned width = static_cast<unsigned>(w);
			unsigned height = static_cast<unsigned>(h);
			
			unsigned total = width * height;
			image.reserve(total);
			
			Math::Vec3 direction = Math::vec3(0, 0, 1.0);
			
			for (unsigned i = 0; i != total; ++i)
			{
				unsigned x = i % width;
				unsigned y = (height - i / width);
			
				float fx = static_cast<float>(x) / static_cast<float>(width);
				float fy = static_cast<float>(y) / static_cast<float>(height);
			
				auto r = Object::makeRay(Math::vec3(fx, fy, 0.0f), direction);
				auto is = apply_visitor(Object::intersection(r), object);
		
				image.push_back(is);
			}
			
			
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
		
		
			FILE *out2 = fopen(file.c_str(), "wb");
			gdImagePngEx(im3, out2, 9);
			fclose(out2);
			gdImageDestroy(im3);
			

			
		}
		catch (bad_get)
		{
			return std::make_tuple(false, "Data type mismatch. render-scene requires: Triangle/Sphere Width Height OutputFile.");
		}
		return std::make_tuple(true, "");	
	}

}
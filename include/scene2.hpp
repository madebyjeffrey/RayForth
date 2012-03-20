
#ifndef SCENE_HPP
#define SCENE_HPP

#include <tuple>
#include "apply_tuple.hpp"
#include <glm/glm.hpp>
#include <boost/variant.hpp>
#include <vector>
#include <list>

#include "geometry.hpp"

template<class... Object>
class Scene 
{ 
	std::list<Object> objects;
	float width, height;

public:
	void addObjects(const Object& t)
	{
		objects.push_back(t);
	}
	
	void addObjects(const Object& t, const Object&... ts)
	{
		objects.push_back(t);
		addObjects(ts...);
	}

	Scene(const Object&... ts) : objects(sizeof...(ts)) 
	{
		addObjects(ts...);
	}
};

template<class... T>
auto makeScene(float w, float h, const T&... ts) -> Scene<T...>
{
	Scene<T...> scene(ts...);

	scene.width = w;
	scene.height = h;

	return scene;
}

template<class T, class... Args>
struct processObjectsWithRay
{
	Ray &r;
	processObjectsWithRay(Ray &ray) : r(ray) {}

	auto operator ()(T t) -> MaybeIntersection
	{
		return test_intersection(t, r);
	}

	auto operator ()(T t, Args... args) -> MaybeIntersection
	{
		auto i = test_intersection(t, r);

		if (i == nullIntersection())
		{
			return (*this)(args...);
		}
		return nullIntersection();
	}
};

template<class... T>
auto runScene(Scene<T...>& s) -> void
{
	float x, y;
	x = 0; y = 0;

	//p.capacity(s.width * s.height);

	for (int x1 = 0; x1 < s.width; ++x1)
		for (int y1 = 0; y1 < s.height; ++y1)
		{
			auto r = makeRay(glm::vec3(x1 / s.width, y1 / s.height, 0), glm::vec3(0, 0, 1.0f));
		//	auto process = std::bind(processObjectsWithRay, r

		}		
}




#endif
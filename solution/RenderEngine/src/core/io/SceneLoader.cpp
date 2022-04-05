#include "SceneLoader.h"
#include <iostream>

#define RYML_SINGLE_HDR_DEFINE_NOW
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

namespace SceneLoader
{

void load(Scene* scene)
{
	char yml_buf[] = "{foo: 1, bar: [2, 3], john: doe}";
	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yml_buf));

	ryml::NodeRef bar = tree["bar"];
	ryml::NodeRef john = tree["john"];
	std::cout << "bar[0] = " << bar[0].val() << std::endl;
	std::cout << "john = " << john.val() << std::endl;
}

void save(Scene* scene)
{

}

} // namespace SceneLoader

} // namespace sre

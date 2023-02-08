#ifndef BLOG
#define BLOG

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include "ros/this_node.h"

std::string gen_random(const int len);
void blog(std::string msg);

#endif
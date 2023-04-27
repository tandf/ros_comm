#include "ros/behavior_logging.h"
#include <boost/stacktrace.hpp>

static std::string fileName = "";
static std::ofstream blog_file;

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

void blog(std::string msg)
{
    char *enable = nullptr;
    if (!(enable = std::getenv("ROS_ENABLE_BLOG")))
        return;
    else if (std::string(enable) == "")
        return;

    if (fileName == "")
    {
        // Get log dir from env
        std::string dir = "/home/yunpeng/robotics/gt-logging/out/";
        if (char *env = std::getenv("ROS_BLOG"))
            dir = env;

        // Generate random file name
        srand(std::chrono::system_clock::now().time_since_epoch().count() *
              getpid());
        std::string random_str = gen_random(12);
        fileName = dir + random_str + ".txt";

        std::cout << "Blog file name: " << fileName << std::endl;
        blog_file.open(fileName, std::ios::out | std::ios::app);
        blog_file << ros::this_node::getName() << " (cpp) open file" << std::endl;
    }

    if (!blog_file.is_open())
    {
        // create file
        blog_file.open(fileName, std::ios::out | std::ios::app);
    }

    // Timestamp
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                         std::chrono::system_clock::now().time_since_epoch())
                         .count();
    std::string ts_str = "[" + std::to_string(timestamp) + "]";

    // Node name
    std::string nodeName = ros::this_node::getName();

    // Add prefixes
    msg = ts_str + " " + nodeName + " " + msg;

    std::cout << msg << std::endl;
    blog_file << msg << std::endl;
    blog_file << boost::stacktrace::stacktrace();
}

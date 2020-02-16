#include <boost/serialization/string.hpp>

#define MAX_SIZE 10000

class info
{
    public:
        info (unsigned int x = 0, std::string i = std::to_string(getpid()), int l = -1, std::string n = "")
            : action(x), clientId(i), logLevel(l), message(n)
        {};

        unsigned int action;
        std::string clientId;
        int logLevel;
        std::string message;

    private:
        friend class boost::serialization::access;

        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & action;
                ar & clientId;
                ar & logLevel;
                ar & message;
            }
};

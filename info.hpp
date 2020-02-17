#include <boost/serialization/string.hpp>

#define MAX_SIZE 1000

class info
{
    public:
        info (unsigned int x = 0, std::string i = std::to_string(getpid()), int l = -1, std::string n = "")
            : action(x), clientId(i), logLevel(l), message(n)
        {};

        // Action can either be 0, 1, or 2 (log, dump, clear)
        unsigned int action;

        // ClientId is currently the process ID
        std::string clientId;

        // The log level will specify what the level of the log is (0 - info,
        // 1 - warning, 2 - error). The default is -1 for actions that do not
        // include a log level
        int logLevel;

        // The message included in a log
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

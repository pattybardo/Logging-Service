#include <boost/serialization/string.hpp>

#define MAX_SIZE 1000

class info
{
    public:
        info (int i = 0, std::string n = "")
            : id(i), name(n)
        {};

        int id;
        std::string name;

    private:
        friend class boost::serialization::access;

        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & id;
                ar & name;
            }
};

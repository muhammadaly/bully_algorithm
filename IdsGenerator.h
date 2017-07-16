#ifndef IDSGENERATOR_H
#define IDSGENERATOR_H

#include <map>
#include <cstdlib>

class IdsGenerator
{
private:

    static IdsGenerator *instance;
    std::map<int,bool> Ids;
public :
    static IdsGenerator *getInstance()
    {
        if(!instance)
            instance = new IdsGenerator;
        return instance;
    }

    int getUniqueId()
    {
        int num;
        do{
             num = (std::rand() %100) + 1;
        }
        while(Ids[num] == true);
        Ids[num] = true;
        return num;
    }
};

IdsGenerator* IdsGenerator::instance = 0;

#endif // IDSGENERATOR_H

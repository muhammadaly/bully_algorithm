#ifndef IDSGENERATOR_H
#define IDSGENERATOR_H

#include <map>
#include <cstdlib>

class IdsGenerator
{
private:

    static IdsGenerator *sngl_Instance;
    std::map<int,bool> Ids;
public :
    static IdsGenerator *getInstance()
    {
        if(!sngl_Instance)
            sngl_Instance = new IdsGenerator;
        return sngl_Instance;
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

#endif // IDSGENERATOR_H

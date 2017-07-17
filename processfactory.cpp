#include "ProcessFactory.h"

ProcessFactory::ProcessFactory()
{

}

void ProcessFactory::createNewProcess()
{
    BullyProcess* newThread = new BullyProcess();
    MessageRouter::getInstance()->attach(newThread);
    newThread->start();
}

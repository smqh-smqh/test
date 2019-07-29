#include "mylog.h"
#include <iostream>

int main()
{
    std::cout << "Hello world" << std::endl;
    LogInfo("info",__FILE__,__FUNCTION__,__LINE__);
    LogWarn("warn",__FILE__,__FUNCTION__,__LINE__);
    LogDebug("debug",__FILE__,__FUNCTION__,__LINE__);
    LogError("error",__FILE__,__FUNCTION__,__LINE__);
    LogDestroy();
    return 0;
}


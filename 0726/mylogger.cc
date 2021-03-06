#include <stdio.h>
#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
using namespace log4cpp;
using std::cout;

class Mylogger
{
public:
    static Mylogger * getInstance()
    {
        if(_pMylogger==nullptr){
            _pMylogger=new Mylogger();
        }
        return _pMylogger;
    }
    
    static void destroy()
    {
        if(_pMylogger){
            Category::shutdown();
            delete _pMylogger;
        }
    }

    void warn(const char * msg)
    {
        _mycategory.warn(msg);  
    }

    void error(const char * msg)
    {
        _mycategory.error(msg);
    }

    void debug(const char * msg)
    {
        _mycategory.debug(msg);
    }

    void info(const char * msg)
    {
        _mycategory.info(msg);
    }

private:
    Mylogger()
    :_mycategory(Category::getRoot().getInstance("mycategory"))
    {
        PatternLayout * ptnLayout1=new PatternLayout();
        ptnLayout1->setConversionPattern("%d [%p] %m%n");

        PatternLayout * ptnLayout2=new PatternLayout();
        ptnLayout1->setConversionPattern("%d [%p] %m%n");

        OstreamAppender * ostreamAppender=new OstreamAppender(
        "ostreamAppender",
        &cout);
        ostreamAppender->setLayout(ptnLayout1);

        FileAppender * fileAppender=new FileAppender(
        "fileAppender",
        "mylog.log"
        );
        fileAppender->setLayout(ptnLayout2);
        
        _mycategory.setPriority(Priority::DEBUG);
        _mycategory.addAppender(ostreamAppender);
        _mycategory.addAppender(fileAppender);
    }

    ~Mylogger(){}
    Category & _mycategory;
    static Mylogger * _pMylogger;
};

Mylogger * Mylogger::_pMylogger=nullptr;

#define LogError(msg) {Mylogger * plog=Mylogger::getInstance(); plog->error(msg);Mylogger::destroy();}
#define LogWarn(msg) {Mylogger * plog=Mylogger::getInstance(); plog->warn(msg);Mylogger::destroy();}
#define LogDebug(msg) {Mylogger * plog=Mylogger::getInstance(); plog->debug(msg);Mylogger::destroy();}
#define LogInfo(msg) {Mylogger * plog=Mylogger::getInstance(); plog->info(msg);Mylogger::destroy();}
int main()
{
    Mylogger * plog=Mylogger::getInstance();
    
    plog->error("this is error");
    plog->warn("this is warn");
    plog->debug("this is debug");
    plog->info("this is info");

    Mylogger::destroy();
    return 0;
}


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

    void warn(const char * msg,const char* file,const char* func,int line)
    {
        _mycategory.warn("[file:%s func:%s line:%d]%s",file,func,line,msg);  
    }

    void error(const char * msg,const char* file,const char* func,int line)
    {
        _mycategory.error("[file:%s func:%s line:%d]%s",file,func,line,msg);
    }

    void debug(const char * msg,const char* file,const char* func,int line)
    {
        _mycategory.debug("[file:%s func:%s line:%d]%s",file,func,line,msg);
    }

    void info(const char * msg,const char* file,const char* func,int line)
    {
        _mycategory.info("[file:%s func:%s line:%d]%s",file,func,line,msg);
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


Mylogger * plog=Mylogger::getInstance();
#define LogError(msg,file,func,line) {plog->error(msg,file,func,line);}
#define LogWarn(msg,file,func,line) {plog->warn(msg,file,func,line);}
#define LogDebug(msg,file,func,line) {plog->debug(msg,file,func,line);}
#define LogInfo(msg,file,func,line) {plog->info(msg,file,func,line);}
#define LogDestroy() {Mylogger::destroy();}



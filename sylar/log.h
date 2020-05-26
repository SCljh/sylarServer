//
// Created by acmery on 2020/5/26.
//

#ifndef SYLARSERVER_LOG_H
#define SYLARSERVER_LOG_H

#include <string>
#include <stdint.h>
#include <memory>
#include <list>

namespace sylar {

//在每个日志生成出来的时候定义为LogEvent, 把所有要用的字段和属性都放在里面
//日志事件
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
private:
    const char* m_file = nullptr;   //文件名
    uint32_t m_line = 0;            //行号
    uint32_t m_elapse = 0;          //程序启动开始到现在的毫秒数
    uint32_t m_threadId = 0;        //线程号
    uint32_t m_fiberId = 0;         //协程号
    u_int64_t m_time;               //时间戳
    std::string m_content;          //内容
};


//日志输出地
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender();

    void log(LogLevel::Level level, LogEvent::ptr event);
private:
    LogLevel::Level m_level;            //针对哪些日志定义的级别
};

//日志格式器
class LogFormater{
public:
    typedef  std::shared_ptr<LogFormater> ptr;
    //将LogEvent格式化为字符串
    std::string format(LogEvent::ptr event);
private:

};

//日志级别
class LogLevel {
public :
    enum Level {      //日志级别
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
};

//日志器
class Logger{
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root") {};
    void log(LogLevel::Level level, const LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level val) {m_level = val;}
private:
    std::string m_name;                         //日志名称
    std::list<LogAppender::ptr> m_appenders;    //输出到的appender集合
    LogLevel::Level m_level;                    //定义日志器的日志级别，大于此级别的日志才被输出

};

//输出的控制台的appender
class StdoutAppender : public LogAppender {

};

//输出到文件的appender
class FileAppender : public LogAppender {

};

}

#endif //SYLARSERVER_LOG_H

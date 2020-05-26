//
// Created by acmery on 2020/5/26.
//

#include "log.h"

namespace sylar{
Logger::Logger(const std::string &name)
    :m_name(name){

}
void Logger::addAppender(sylar::LogAppender::ptr appender) {
    m_appenders.push_back(appender);
}
void Logger::delAppender(sylar::LogAppender::ptr appender) {
    for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it){
        if (*it == appender){
            m_appenders.erase(it);
            break;
        }
    }
}
void Logger::log(sylar::LogLevel::Level level, const sylar::LogEvent::ptr event) {
    if (level >= m_level){
        for (auto& i : m_appenders){            //遍历每个appender，并输出日志。
            i->log(level, event);
        }
    }
}
void Logger::debug(LogEvent::ptr event){
    log(LogLevel::DEBUG, event);
}
void Logger::info(LogEvent::ptr event){
    log(LogLevel::INFO, event);
}
void Logger::warn(LogEvent::ptr event){
    log(LogLevel::WARN, event);
}
void Logger::error(LogEvent::ptr event){
    log(LogLevel::ERROR, event);
}
void Logger::fatal(LogEvent::ptr event){
    log(LogLevel::FATAL, event);
}

}
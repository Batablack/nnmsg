//
// Created by Administrator on 2022/11/10.
//

#ifndef NNMSG_SUB_LOGGER_H
#define NNMSG_SUB_LOGGER_H


#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging
#include <string>

using namespace spdlog;
using std::string;

class logger
{
public:
    logger(){}
    logger(string _loggerName, string _loggerPath, int _loggerSize, int _maxLogNum):
            loggerName(_loggerName), loggerPath(_loggerPath), loggerSize(_loggerSize), maxLogNum(_maxLogNum){}
    void logger_init(string _loggerName, string _loggerPath, int _loggerSize, int _maxLogNum)
    {
        loggerName = _loggerName;
        loggerPath = _loggerPath;
        loggerSize = _loggerSize;
        maxLogNum = _maxLogNum;

        log = spdlog::rotating_logger_mt(loggerName, loggerPath,loggerSize, maxLogNum);
        log->set_level(spdlog::level::info);
        log->flush_on(spdlog::level::trace);
    }
    std::shared_ptr<spdlog::logger> log;
private:
    string loggerName;
    string loggerPath;
    int loggerSize;
    int maxLogNum;
};



#endif //NNMSG_SUB_LOGGER_H

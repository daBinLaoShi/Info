#ifndef INFO_INFO_H
#define INFO_INFO_H
#include "QSettings"

class Info {

public:
    Info();

    ~Info();

    const QString &cpuType();

    const QString dCard();

    int memory();

    const QString &osVersion();

    void GetOpenGLVersion();

    void test();
};

#endif //INFO_INFO_H
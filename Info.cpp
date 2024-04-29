#include "Info.h"
#include <Windows.h>
#include <QProcess>
#include <iostream>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

Info::Info() {}

Info::~Info() {}

const QString &Info::cpuType() {
    QSettings *CPU = new QSettings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                                   QSettings::NativeFormat);
    auto m_cpuDescribe = CPU->value("ProcessorNameString").toString();
    delete CPU;
    return m_cpuDescribe;
}

const QString Info::dCard() {
    QProcess process;
    process.start("cmd.exe", QStringList() << "/c" << "wmic path win32_videocontroller get name");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());

    QStringList lines = output.split("\r\r\n");
    QStringList items = lines.at(1).trimmed().split("  ");
    QString gpuName = items.at(0);
    return gpuName;

}

int Info::memory() {
    int MB = 1024 * 1024;
    MEMORYSTATUSEX memoryStateEx;
    memoryStateEx.dwLength = sizeof(memoryStateEx);
    GlobalMemoryStatusEx(&memoryStateEx);
    int allMemory = memoryStateEx.ullTotalPhys / MB;
    return allMemory;
}

const QString &Info::osVersion() {
    QString productType = QSysInfo::prettyProductName();
    return productType;
}

void Info::GetOpenGLVersion(){
    QOffscreenSurface surf;
    surf.create();
    QOpenGLContext ctx;
    ctx.create();
    ctx.makeCurrent(&surf);
    std::cout << "OpenGL Version:" << (const char *)ctx.functions()->glGetString(GL_VERSION) << std::endl;
    ctx.doneCurrent();
};

void Info::test() {
    QString dcard = dCard();
    std::cout << "Renderer: " << dcard.toStdString() << std::endl;
    int mem = memory();
    std::cout << "RAM: " << mem << "MB" << std::endl;
    QString os = osVersion();
    std::cout << "Operation system: " << os.toStdString() << std::endl;
    QString cpu = cpuType();
    std::cout << "Processor: " << cpu.toStdString() << std::endl;
    GetOpenGLVersion();
}
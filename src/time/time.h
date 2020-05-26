/* This file countains code made by theCherno */
#pragma once

#include <string>
#include <chrono>
#include <fstream>

#define TIME_INIT_SESSION(name) const std::string str_name(name); \
Instrumentor::Get().BeginSession(name)

#define TIME_END_SESSION Instrumentor::Get().EndSession()
#define TIME(name) InstrumentationTimer timer(name)

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
public:
    Instrumentor();

    void BeginSession(const std::string& name, const std::string& filepath = "times.json");
    void EndSession();

    void WriteProfile(const ProfileResult& result);
    void WriteHeader();
    void WriteFooter();

    static Instrumentor& Get();

private:
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
};

class InstrumentationTimer
{
public:
    InstrumentationTimer(const char* name);
    ~InstrumentationTimer();

    void Stop();

private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};

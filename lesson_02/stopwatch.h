#pragma once

#include <chrono>
#include <string>

inline std::string period_description(std::micro) { return std::string("microsecods"); }
inline std::string period_description(std::milli) { return std::string("milliseconds"); }
inline std::string period_description(std::nano) { return std::string("nanoseconds"); }

template<typename Period, typename BaseType = double>
class StopWatch
{
  public:
    using base_t = BaseType;
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using Duration = std::chrono::duration<base_t, Period>;

    StopWatch() {}
    std::string period() const { return period_description(Period()); }

    void start() { t0 = Clock::now(); }
    base_t stop() { return Duration(Clock::now() - t0).count(); }

  private:
    TimePoint t0;
};

using stop_watch_t = StopWatch<std::milli, double>;

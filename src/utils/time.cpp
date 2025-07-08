#include <chrono>
#include <cstdint>

/* Return the current timestamp */
std::int64_t getCurrentTimestamp()
{
    using namespace std::chrono;
    return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}
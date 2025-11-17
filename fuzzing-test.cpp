#include "real48.hpp"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>

namespace
{

template <class T>
bool test(const std::uint8_t* data)
{
    try
    {
        T input {};
        std::memcpy(&input, data, sizeof(input));
        math::Real48 r48 {input};
        const auto epsilon = std::numeric_limits<T>::epsilon();
        const auto a = input;
        const auto b = T {r48};
        using std::fabs;
        return fabs(a - b) <=
               ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
    }
    catch (const std::overflow_error& err)
    {
    }
    return false;
}

} // namespace

extern "C" int
LLVMFuzzerTestOneInput(const std::uint8_t* data, std::size_t size)
{
    if (size < sizeof(float))
    {
    }
    else if (size < sizeof(double))
    {
        return test<float>(data);
    }
    else
    {
        return test<double>(data);
    }
    return 0;
}

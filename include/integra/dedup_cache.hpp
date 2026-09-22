#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace integra
{

/// Fixed-capacity FIFO cache of recently-seen ids, used to detect a
/// retransmission of something already processed. Allocates nothing; the
/// oldest entry is overwritten once the cache is full.
template<std::size_t CAPACITY>
class DedupCache
{
    static_assert(CAPACITY > 0U, "CAPACITY must be at least 1");

public:
    DedupCache() = default;

    [[nodiscard]] bool Contains(std::uint32_t id) const
    {
        for (std::size_t i = 0U; i < m_count; ++i)
        {
            if (m_entries[i] == id)
            {
                return true;
            }
        }
        return false;
    }

    void Insert(std::uint32_t id)
    {
        m_entries[m_writeIdx] = id;
        m_writeIdx            = (m_writeIdx + 1U) % CAPACITY;
        if (m_count < CAPACITY)
        {
            ++m_count;
        }
    }

private:
    std::array<std::uint32_t, CAPACITY> m_entries{};
    std::size_t m_writeIdx{0U};
    std::size_t m_count{0U};
};

} // namespace integra

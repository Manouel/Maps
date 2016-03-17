#ifndef FLAGGEDMAP_H
#define FLAGGEDMAP_H

#include <map>
#include <vector>
#include <initializer_list>
#include <algorithm>

template<typename Key, typename Value>
class FlaggedMap : public std::map<Key, Value>
{
    private:

        std::vector<Key> m_flags;

        virtual std::vector<Key> getSimpleKeys(const Key& composedKey) const;

    public:

        FlaggedMap() : : std::map<Key, Value>() {}
        FlaggedMap(const std::vector<Key>& flags) : std::map<Key, Value>(), m_flags(flags) {}
        FlaggedMap(const std::initializer_list<Key>& flags) : std::map<Key, Value>(), m_flags(flags) {}
        virtual ~FlaggedMap() {}

        virtual std::map<Key, Value*> getSubSets(const Key& composedKey);

        virtual std::map<Key, const Value*> getSubSets(const Key& composedKey) const;

        virtual Value& operator[](const Key& k);
};

// ==============================
// ==============================

template<typename Key, typename Value>
std::vector<Key> FlaggedMap<Key, Value>::getSimpleKeys(const Key& composedKey) const
{
    std::vector<Key> simpleKeys;

    if (m_flags.empty())
        simpleKeys.push_back(composedKey);
    else
    {
        for (Key key : m_flags)
        {
            if (composedKey & key)
                simpleKeys.push_back(key);
        }
    }

    return simpleKeys;
}

// ==============================
// ==============================

template<typename Key, typename Value>
std::map<Key, Value*> FlaggedMap<Key, Value>::getSubSets(const Key& composedKey)
{
    std::vector<Key> keys = getSimpleKeys(composedKey);
    std::map<Key, Value*> subSets;

    typename std::map<Key, Value>::iterator it;

    for (Key k : keys)
    {
        it = this->find(k);
        if (it != this->end())
            subSets[k] = &(it->second);
    }

    return subSets;
}

// ==============================
// ==============================

template<typename Key, typename Value>
std::map<Key, const Value*> FlaggedMap<Key, Value>::getSubSets(const Key& composedKey) const
{
    std::vector<Key> keys = getSimpleKeys(composedKey);
    std::map<Key, const Value*> subSets;

    typename std::map<Key, Value>::const_iterator it;

    for (Key k : keys)
    {
        it = this->find(k);
        if (it != this->end())
            subSets[k] = &(it->second);
    }

    return subSets;
}

// ==============================
// ==============================

template<typename Key, typename Value>
Value& FlaggedMap<Key, Value>::operator[](const Key& k)
{
    if (!m_flags.empty() && std::find(m_flags.begin(), m_flags.end(), k) == m_flags.end())
        throw std::out_of_range("Invalid key");

    return std::map<Key, Value>::operator[](k);
}

#endif

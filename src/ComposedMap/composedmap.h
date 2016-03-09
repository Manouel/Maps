#ifndef COMPOSEDMAP_H
#define COMPOSEDMAP_H

#include <map>

template<typename Key, typename V>
class ComposedMap : public std::map<Key, V>
{
    private:

        template<bool IsConst = false>
        class base_iterator
        {
            protected:

                typedef typename std::conditional<IsConst, typename std::map<Key, V>::const_iterator, typename std::map<Key, V>::iterator>::type ContainerIterator;
                typedef typename std::conditional<IsConst, typename std::map<Key, V>::mapped_type::const_iterator, typename std::map<Key, V>::mapped_type::iterator>::type ElementIterator;

                typedef typename std::conditional<IsConst, const std::map<Key, V>&, std::map<Key, V>&>::type MapType;

                template <class Value>
                struct Extract
                {
                    typedef Value type;
                };

                template <class First, class Second>
                struct Extract <std::pair<First,Second> >
                {
                    typedef Second type;
                };

                template <class Value>
                inline Value& extract(Value& v) const { return v; }

                template <class Value>
                inline const Value& extract(const Value& v) const { return v; }

                template <class First, class Second>
                inline Second& extract(std::pair<First, Second>& pair) const { return pair.second; }

                template <class First, class Second>
                inline const Second& extract(const std::pair<First, Second>& pair) const { return pair.second; }

                typedef typename std::conditional<IsConst, const typename Extract<typename std::map<Key, V>::mapped_type::value_type>::type*,
                                                                typename Extract<typename std::map<Key, V>::mapped_type::value_type>::type*>::type ElementPointer;
                typedef typename std::conditional<IsConst, const typename Extract<typename std::map<Key, V>::mapped_type::value_type>::type&,
                                                                typename Extract<typename std::map<Key, V>::mapped_type::value_type>::type&>::type ElementReference;


                ContainerIterator m_Begin;
                ContainerIterator m_End;
                ContainerIterator m_CurrentContainer;
                ElementIterator m_It;


                base_iterator() {}

                base_iterator(MapType m, const typename std::map<Key, V>::const_iterator& it) : m_Begin(m.begin()), m_End(m.end()), m_CurrentContainer(it)
                {
                    if (m_CurrentContainer != m_End)
                    {
                        if (!m_CurrentContainer->second.empty())
                            m_It = m_CurrentContainer->second.begin();
                        else
                            operator++();
                    }
                }

                base_iterator(MapType m, const typename std::map<Key, V>::iterator& it) : m_Begin(m.begin()), m_End(m.end()), m_CurrentContainer(it)
                {
                    if (m_CurrentContainer != m_End)
                    {
                        if (!m_CurrentContainer->second.empty())
                            m_It = m_CurrentContainer->second.begin();
                        else
                            operator++();
                    }
                }

                base_iterator(MapType m, const typename std::map<Key, V>::const_iterator& contIt, const typename std::map<Key, V>::mapped_type::const_iterator& it)
                    : m_Begin(m.begin()), m_End(m.end()), m_CurrentContainer(contIt)
                {
                    if (m_CurrentContainer != m_End)
                    {
                        m_It = it;

                        if (m_CurrentContainer->second.empty() || m_It == m_CurrentContainer->second.end())
                            operator++();
                    }
                }

                base_iterator(MapType m, const typename std::map<Key, V>::iterator& contIt, const typename std::map<Key, V>::mapped_type::iterator& it)
                    : m_Begin(m.begin()), m_End(m.end()), m_CurrentContainer(contIt)
                {
                    if (m_CurrentContainer != m_End)
                    {
                        m_It = it;

                        if (m_CurrentContainer->second.empty() || m_It == m_CurrentContainer->second.end())
                            operator++();
                    }
                }

            public:

                base_iterator(MapType m) : m_Begin(m.begin()), m_End(m.end()), m_CurrentContainer(m_Begin)
                {
                    if (m_CurrentContainer != m_End)
                    {
                        if (!m_CurrentContainer->second.empty())
                            m_It = m_CurrentContainer->second.begin();
                        else
                            operator++();
                    }
                }

                virtual ElementReference operator*() const
                {
                    return extract(*m_It);
                }

                virtual ElementPointer operator->() const
                {
                    return &(extract(*m_It));
                }

                virtual bool operator==(const base_iterator& other) const
                {
                    return (m_CurrentContainer == m_End && other.m_CurrentContainer == other.m_End) || (m_It == other.m_It);
                }

                virtual bool operator==(const typename std::map<Key, V>::mapped_type::const_iterator& other) const
                {
                    return m_CurrentContainer != m_End && m_It == other;
                }

                virtual bool operator==(const typename std::map<Key, V>::mapped_type::iterator& other) const
                {
                    return m_CurrentContainer != m_End && m_It == other;
                }

                virtual bool operator!=(const base_iterator& other) const
                {
                    return !(*this == other);
                }

                virtual bool operator!=(const typename std::map<Key, V>::mapped_type::const_iterator& other) const
                {
                    return !(*this == other);
                }

                virtual bool operator!=(const typename std::map<Key, V>::mapped_type::iterator& other) const
                {
                    return !(*this == other);
                }

                virtual base_iterator& operator=(const base_iterator& it)
                {
                    m_Begin = it.m_Begin;
                    m_End = it.m_End;
                    m_CurrentContainer = it.m_CurrentContainer;
                    m_It = it.m_It;

                    return *this;
                }

                virtual base_iterator& operator++()
                {
                    if (m_CurrentContainer != m_End)
                    {
                        if (m_CurrentContainer->second.empty() || m_It == m_CurrentContainer->second.end() || ++m_It == m_CurrentContainer->second.end())
                        {
                            while (++m_CurrentContainer != m_End && m_CurrentContainer->second.empty())
                            {
                            }

                            if (m_CurrentContainer != m_End)
                               m_It = m_CurrentContainer->second.begin();
                        }
                    }

                    return *this;
                }

                virtual base_iterator& operator--()
                {
                    if (m_CurrentContainer == m_End || m_It == m_CurrentContainer->second.begin())
                    {
                        if (m_CurrentContainer != m_Begin)
                        {
                            do
                            {
                                --m_CurrentContainer;
                            }
                            while (m_CurrentContainer != m_Begin && m_CurrentContainer->second.empty());

                            if (m_CurrentContainer->second.empty())
                                operator++();
                            else
                            {
                                m_It = m_CurrentContainer->second.end();
                                --m_It;
                            }
                        }
                    }
                    else
                        --m_It;

                    return *this;
                }
        };

    public:

        class iterator;

        class const_iterator : public base_iterator<true>
        {
            friend class ComposedMap;

            private:

                const_iterator(const std::map<Key, V>& m, const typename std::map<Key, V>::const_iterator& it)
                    : base_iterator<true>(m, it)
                {}

                const_iterator(const std::map<Key, V>& m, const typename std::map<Key, V>::const_iterator& contIt, const typename std::map<Key, V>::mapped_type::const_iterator& it)
                    : base_iterator<true>(m, contIt, it)
                {}

            public:

                const_iterator(const std::map<Key, V>& m) : base_iterator<true>(m)
                {}

                const_iterator(const iterator& it) : base_iterator<true>()
                {
                   this->m_Begin = it.m_Begin;
                   this->m_End = it.m_End;
                   this->m_CurrentContainer = it.m_CurrentContainer;
                   this->m_It = it.m_It;
                }

                virtual ~const_iterator() {}

                virtual bool operator==(const const_iterator& other) const
                {
                    return base_iterator<true>::operator==(other);
                }

                virtual bool operator==(const typename std::map<Key, V>::mapped_type::const_iterator& other) const
                {
                    return base_iterator<true>::operator==(other);
                }

                virtual bool operator!=(const const_iterator& other) const
                {
                    return base_iterator<true>::operator!=(other);
                }

                virtual bool operator!=(const typename std::map<Key, V>::mapped_type::const_iterator& other) const
                {
                    return base_iterator<true>::operator!=(other);
                }

                virtual const_iterator& operator=(const const_iterator& it)
                {
                    base_iterator<true>::operator=(it);
                    return *this;
                }

                virtual const_iterator& operator++()
                {
                    base_iterator<true>::operator++();
                    return *this;
                }

                virtual const_iterator& operator++(int)
                {
                    return operator++();
                }

                virtual const_iterator& operator--()
                {
                    base_iterator<true>::operator--();
                    return *this;
                }

                virtual const_iterator& operator--(int)
                {
                    return operator--();
                }
        };

        class iterator : public base_iterator<>
        {
            friend class ComposedMap;

            private:

                iterator(std::map<Key, V>& m, const typename std::map<Key, V>::const_iterator& it) : base_iterator<>(m, it)
                {}

                iterator(std::map<Key, V>& m, const typename std::map<Key, V>::iterator& it) : base_iterator<>(m, it)
                {}

                iterator(std::map<Key, V>& m, const typename std::map<Key, V>::const_iterator& contIt, const typename std::map<Key, V>::mapped_type::const_iterator& it)
                    : base_iterator<>(m, contIt, it)
                {}

                iterator(std::map<Key, V>& m, const typename std::map<Key, V>::iterator& contIt, const typename std::map<Key, V>::mapped_type::iterator& it)
                    : base_iterator<>(m, contIt, it)
                {}

            public:

                iterator(std::map<Key, V>& m) : base_iterator<>(m)
                {}

                virtual ~iterator() {}

                virtual iterator& operator=(const iterator& it)
                {
                    base_iterator<>::operator=(it);
                    return *this;
                }

                virtual iterator& operator++()
                {
                    base_iterator<>::operator++();
                    return *this;
                }

                virtual iterator& operator++(int)
                {
                    return operator++();
                }

                virtual iterator& operator--()
                {
                    base_iterator<>::operator--();
                    return *this;
                }

                virtual iterator& operator--(int)
                {
                    return operator--();
                }
        };

        ComposedMap() : std::map<Key, V>() {}
        virtual ~ComposedMap() {}

        virtual iterator begin() { return iterator(*this); }
        virtual const_iterator begin() const { return const_iterator(*this); }

        virtual iterator end() { return iterator(*this, std::map<Key, V>::end()); }
        virtual const_iterator end() const { return const_iterator(*this, std::map<Key, V>::end()); }

        virtual const_iterator cbegin() const { return begin(); }
        virtual const_iterator cend() const { return end(); }

        virtual bool empty() const
        {
            for (auto it = std::map<Key, V>::begin(); it != std::map<Key, V>::end(); ++it)
            {
                if (!it->second.empty())
                    return false;
            }

            return true;
        }

        virtual bool empty(Key k) const
        {
            if (!this->count(k))
                throw std::out_of_range("Invalid key");

            return this->at(k).empty();
        }

        virtual unsigned int elementsCount() const
        {
            unsigned int count = 0;

            for (auto it = std::map<Key, V>::begin(); it != std::map<Key, V>::end(); ++it)
                count += it->second.size();

            return count;
        }

        virtual iterator erase(iterator position)
        {
            if (position != end())
            {
                auto nextElement = position.m_CurrentContainer->second.erase(position.m_It);
                return iterator(*this, position.m_CurrentContainer, nextElement);
            }

            return end();
        }

        virtual typename std::map<Key, V>::size_type erase(const Key& k)
        {
            return std::map<Key, V>::erase(k);
        }

        virtual iterator erase(iterator first, iterator last)
        {
            iterator prev = last;

            while (prev != first)
            {
                prev = last;
                --prev;
                last = erase(prev);
            }

            return last;
        }

        virtual typename std::map<Key, V>::iterator erase(typename std::map<Key, V>::const_iterator position)
        {
            return std::map<Key, V>::erase(position);
        }

        virtual typename std::map<Key, V>::iterator erase(typename std::map<Key, V>::const_iterator first, typename std::map<Key, V>::const_iterator last)
        {
            return std::map<Key, V>::erase(first, last);
        }

        virtual void clear() { std::map<Key, V>::clear(); }
        virtual void clear(Key k) { this->at(k).clear(); }
};

#endif  // COMPOSEDMAP_H

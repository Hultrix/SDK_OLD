#pragma once

#include <list>

namespace Ht {
    template<typename T>
    class HList {
    public:
        void pop_back();
        void pop_front();
        void push_back(const T& value);
        void push_front(const T& value);
        void prepend(const T& value);
        typename std::list<T>::iterator begin();
        typename std::list<T>::iterator end();
        std::size_t size() const;
        bool empty() const;
    private:
        std::list<T> m_list;
    };

    template<typename T>
    void HList<T>::pop_back() {
        m_list.pop_back();
    }

    template<typename T>
    void HList<T>::pop_front() {
        m_list.pop_front();
    }

    template<typename T>
    void HList<T>::push_back(const T& value) {
        m_list.push_back(value);
    }

    template<typename T>
    void HList<T>::push_front(const T& value) {
        m_list.push_front(value);
    }

    template<typename T>
    void HList<T>::prepend(const T& value) {
        m_list.push_front(value);
    }
    
    template<typename T>
    typename std::list<T>::iterator HList<T>::begin() {
        return m_list.begin();
    }

    template<typename T>
    typename std::list<T>::iterator HList<T>::end() {
        return m_list.end();
    }

    template<typename T>
    std::size_t HList<T>::size() const {
        return m_list.size();
    }

    template<typename T>
    bool HList<T>::empty() const {
        return m_list.empty();
    }
}


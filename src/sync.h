// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin developers
// Copyright (c) 2017-2018 The PIVX developers
<<<<<<< Updated upstream
=======
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SYNC_H
#define BITCOIN_SYNC_H

#include "threadsafety.h"

<<<<<<< Updated upstream
#include <condition_variable>
#include <thread>
#include <mutex>
=======
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>
>>>>>>> Stashed changes


/////////////////////////////////////////////////
//                                             //
// THE SIMPLE DEFINITION, EXCLUDING DEBUG CODE //
//                                             //
/////////////////////////////////////////////////

/*
CCriticalSection mutex;
<<<<<<< Updated upstream
    std::recursive_mutex mutex;

LOCK(mutex);
    std::unique_lock<std::recursive_mutex> criticalblock(mutex);

LOCK2(mutex1, mutex2);
    std::unique_lock<std::recursive_mutex> criticalblock1(mutex1);
    std::unique_lock<std::recursive_mutex> criticalblock2(mutex2);

TRY_LOCK(mutex, name);
    std::unique_lock<std::recursive_mutex> name(mutex, std::try_to_lock_t);
=======
    boost::recursive_mutex mutex;

LOCK(mutex);
    boost::unique_lock<boost::recursive_mutex> criticalblock(mutex);

LOCK2(mutex1, mutex2);
    boost::unique_lock<boost::recursive_mutex> criticalblock1(mutex1);
    boost::unique_lock<boost::recursive_mutex> criticalblock2(mutex2);

TRY_LOCK(mutex, name);
    boost::unique_lock<boost::recursive_mutex> name(mutex, boost::try_to_lock_t);
>>>>>>> Stashed changes

ENTER_CRITICAL_SECTION(mutex); // no RAII
    mutex.lock();

LEAVE_CRITICAL_SECTION(mutex); // no RAII
    mutex.unlock();
 */

///////////////////////////////
//                           //
// THE ACTUAL IMPLEMENTATION //
//                           //
///////////////////////////////

/**
 * Template mixin that adds -Wthread-safety locking
 * annotations to a subset of the mutex API.
 */
template <typename PARENT>
class LOCKABLE AnnotatedMixin : public PARENT
{
public:
    void lock() EXCLUSIVE_LOCK_FUNCTION()
    {
        PARENT::lock();
    }

    void unlock() UNLOCK_FUNCTION()
    {
        PARENT::unlock();
    }

    bool try_lock() EXCLUSIVE_TRYLOCK_FUNCTION(true)
    {
        return PARENT::try_lock();
    }
};

#ifdef DEBUG_LOCKORDER
void EnterCritical(const char* pszName, const char* pszFile, int nLine, void* cs, bool fTry = false);
void LeaveCritical();
std::string LocksHeld();
void AssertLockHeldInternal(const char* pszName, const char* pszFile, int nLine, void* cs);
void DeleteLock(void* cs);
#else
void static inline EnterCritical(const char* pszName, const char* pszFile, int nLine, void* cs, bool fTry = false) {}
void static inline LeaveCritical() {}
void static inline AssertLockHeldInternal(const char* pszName, const char* pszFile, int nLine, void* cs) {}
void static inline DeleteLock(void* cs) {}
#endif
#define AssertLockHeld(cs) AssertLockHeldInternal(#cs, __FILE__, __LINE__, &cs)

/**
<<<<<<< Updated upstream
 * Wrapped mutex: supports recursive locking, but no waiting
 * TODO: We should move away from using the recursive lock by default.
 */
class CCriticalSection : public AnnotatedMixin<std::recursive_mutex>
=======
 * Wrapped boost mutex: supports recursive locking, but no waiting
 * TODO: We should move away from using the recursive lock by default.
 */
class CCriticalSection : public AnnotatedMixin<boost::recursive_mutex>
>>>>>>> Stashed changes
{
public:
    ~CCriticalSection() {
        DeleteLock((void*)this);
    }
};

<<<<<<< Updated upstream
/** Wrapped mutex: supports waiting but not recursive locking */
typedef AnnotatedMixin<std::mutex> CWaitableCriticalSection;

/** Just a typedef for std::condition_variable, can be wrapped later if desired */
typedef std::condition_variable CConditionVariable;

/** Just a typedef for std::unique_lock, can be wrapped later if desired */
typedef std::unique_lock<std::mutex> WaitableLock;
=======
/** Wrapped boost mutex: supports waiting but not recursive locking */
typedef AnnotatedMixin<boost::mutex> CWaitableCriticalSection;

/** Just a typedef for boost::condition_variable, can be wrapped later if desired */
typedef boost::condition_variable CConditionVariable;
>>>>>>> Stashed changes

#ifdef DEBUG_LOCKCONTENTION
void PrintLockContention(const char* pszName, const char* pszFile, int nLine);
#endif

<<<<<<< Updated upstream
/** Wrapper around std::unique_lock<CCriticalSection> */
class SCOPED_LOCKABLE CCriticalBlock
{
private:
    std::unique_lock<CCriticalSection> lock;
=======
/** Wrapper around boost::unique_lock<CCriticalSection> */
template <typename Mutex>
class SCOPED_LOCKABLE CMutexLock
{
private:
    boost::unique_lock<Mutex> lock;
>>>>>>> Stashed changes

    void Enter(const char* pszName, const char* pszFile, int nLine)
    {
        EnterCritical(pszName, pszFile, nLine, (void*)(lock.mutex()));
#ifdef DEBUG_LOCKCONTENTION
        if (!lock.try_lock()) {
            PrintLockContention(pszName, pszFile, nLine);
#endif
            lock.lock();
#ifdef DEBUG_LOCKCONTENTION
        }
#endif
    }

    bool TryEnter(const char* pszName, const char* pszFile, int nLine)
    {
        EnterCritical(pszName, pszFile, nLine, (void*)(lock.mutex()), true);
        lock.try_lock();
        if (!lock.owns_lock())
            LeaveCritical();
        return lock.owns_lock();
    }

public:
<<<<<<< Updated upstream
    CCriticalBlock(CCriticalSection& mutexIn, const char* pszName, const char* pszFile, int nLine, bool fTry = false) EXCLUSIVE_LOCK_FUNCTION(mutexIn) : lock(mutexIn, std::defer_lock)
=======
    CMutexLock(Mutex& mutexIn, const char* pszName, const char* pszFile, int nLine, bool fTry = false) EXCLUSIVE_LOCK_FUNCTION(mutexIn) : lock(mutexIn, boost::defer_lock)
>>>>>>> Stashed changes
    {
        if (fTry)
            TryEnter(pszName, pszFile, nLine);
        else
            Enter(pszName, pszFile, nLine);
    }

<<<<<<< Updated upstream
    CCriticalBlock(CCriticalSection* pmutexIn, const char* pszName, const char* pszFile, int nLine, bool fTry = false) EXCLUSIVE_LOCK_FUNCTION(pmutexIn)
    {
        if (!pmutexIn) return;

        lock = std::unique_lock<CCriticalSection>(*pmutexIn, std::defer_lock);
=======
    CMutexLock(Mutex* pmutexIn, const char* pszName, const char* pszFile, int nLine, bool fTry = false) EXCLUSIVE_LOCK_FUNCTION(pmutexIn)
    {
        if (!pmutexIn) return;

        lock = boost::unique_lock<Mutex>(*pmutexIn, boost::defer_lock);
>>>>>>> Stashed changes
        if (fTry)
            TryEnter(pszName, pszFile, nLine);
        else
            Enter(pszName, pszFile, nLine);
    }

<<<<<<< Updated upstream
    ~CCriticalBlock() UNLOCK_FUNCTION()
=======
    ~CMutexLock() UNLOCK_FUNCTION()
>>>>>>> Stashed changes
    {
        if (lock.owns_lock())
            LeaveCritical();
    }

    operator bool()
    {
        return lock.owns_lock();
    }
};

<<<<<<< Updated upstream
=======
typedef CMutexLock<CCriticalSection> CCriticalBlock;

>>>>>>> Stashed changes
#define PASTE(x, y) x ## y
#define PASTE2(x, y) PASTE(x, y)

#define LOCK(cs) CCriticalBlock PASTE2(criticalblock, __COUNTER__)(cs, #cs, __FILE__, __LINE__)
#define LOCK2(cs1, cs2) CCriticalBlock criticalblock1(cs1, #cs1, __FILE__, __LINE__), criticalblock2(cs2, #cs2, __FILE__, __LINE__)
#define TRY_LOCK(cs, name) CCriticalBlock name(cs, #cs, __FILE__, __LINE__, true)

#define ENTER_CRITICAL_SECTION(cs)                            \
    {                                                         \
        EnterCritical(#cs, __FILE__, __LINE__, (void*)(&cs)); \
        (cs).lock();                                          \
    }

#define LEAVE_CRITICAL_SECTION(cs) \
    {                              \
        (cs).unlock();             \
        LeaveCritical();           \
    }

class CSemaphore
{
private:
<<<<<<< Updated upstream
    std::condition_variable condition;
    std::mutex mutex;
    int value;

public:
    explicit CSemaphore(int init) : value(init) {}

    void wait()
    {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [&]() { return value >= 1; });
=======
    boost::condition_variable condition;
    boost::mutex mutex;
    int value;

public:
    CSemaphore(int init) : value(init) {}

    void wait()
    {
        boost::unique_lock<boost::mutex> lock(mutex);
        while (value < 1) {
            condition.wait(lock);
        }
>>>>>>> Stashed changes
        value--;
    }

    bool try_wait()
    {
<<<<<<< Updated upstream
        std::lock_guard<std::mutex> lock(mutex);
=======
        boost::unique_lock<boost::mutex> lock(mutex);
>>>>>>> Stashed changes
        if (value < 1)
            return false;
        value--;
        return true;
    }

    void post()
    {
        {
<<<<<<< Updated upstream
            std::lock_guard<std::mutex> lock(mutex);
=======
            boost::unique_lock<boost::mutex> lock(mutex);
>>>>>>> Stashed changes
            value++;
        }
        condition.notify_one();
    }
};

/** RAII-style semaphore lock */
class CSemaphoreGrant
{
private:
    CSemaphore* sem;
    bool fHaveGrant;

public:
    void Acquire()
    {
        if (fHaveGrant)
            return;
        sem->wait();
        fHaveGrant = true;
    }

    void Release()
    {
        if (!fHaveGrant)
            return;
        sem->post();
        fHaveGrant = false;
    }

    bool TryAcquire()
    {
        if (!fHaveGrant && sem->try_wait())
            fHaveGrant = true;
        return fHaveGrant;
    }

    void MoveTo(CSemaphoreGrant& grant)
    {
        grant.Release();
        grant.sem = sem;
        grant.fHaveGrant = fHaveGrant;
<<<<<<< Updated upstream
        fHaveGrant = false;
    }

    CSemaphoreGrant() : sem(nullptr), fHaveGrant(false) {}

    explicit CSemaphoreGrant(CSemaphore& sema, bool fTry = false) : sem(&sema), fHaveGrant(false)
=======
        sem = NULL;
        fHaveGrant = false;
    }

    CSemaphoreGrant() : sem(NULL), fHaveGrant(false) {}

    CSemaphoreGrant(CSemaphore& sema, bool fTry = false) : sem(&sema), fHaveGrant(false)
>>>>>>> Stashed changes
    {
        if (fTry)
            TryAcquire();
        else
            Acquire();
    }

    ~CSemaphoreGrant()
    {
        Release();
    }

<<<<<<< Updated upstream
    operator bool() const
=======
    operator bool()
>>>>>>> Stashed changes
    {
        return fHaveGrant;
    }
};

#endif // BITCOIN_SYNC_H

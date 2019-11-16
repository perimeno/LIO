#ifndef MYSIGNAL_H
#define MYSIGNAL_H
#include <condition_variable>
#include <mutex>
#include <chrono>
/**
 * @brief The MySignal helper class that handles spurious wakeup
 */
class MySignal{
private:
    std::mutex m;
    std::condition_variable c;
    bool indicator{false};
public:
    enum class sig_status{timeout,no_timeout};
    void wait();
    template<typename _Rep, typename _Period>
    sig_status wait_for(const std::chrono::duration<_Rep, _Period>& timeout){
        auto stop=std::chrono::steady_clock::now()+timeout;
        std::unique_lock<std::mutex>lck(m);
        while (true) {
            c.wait_until(lck,stop,[&]{return indicator;});
            if(indicator){
                indicator=false;
                return sig_status::no_timeout;
            }
            else if(std::chrono::steady_clock::now()>stop){
                indicator=false;
                return sig_status::timeout;
            }
        }

    }
    void signal();

};
#endif

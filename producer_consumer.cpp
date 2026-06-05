#include <mutex>
#include <condition_variable>
#include <queue>

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;

public:
    // 生产者调用：往队列扔数据
    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
        cv_.notify_one(); // 唤醒正在等待的消费者
    }

    // 消费者调用：从队列拿数据
    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        // 如果队列空了，消费者就在这里睡大觉，直到被唤醒
        cv_.wait(lock, [this]() { return !queue_.empty(); });
        
        T value = queue_.front();
        queue_.pop();
        return value;
    }
};

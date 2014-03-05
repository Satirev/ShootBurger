#ifndef QUEUE_H_
#define QUEUE_H_

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename T>
class Queue {
public:
	Queue() {
	}

	void pop(T& item) {
		std::unique_lock < std::mutex > lock(m_mutex);
		if (!m_queue.empty()) {

			item = m_queue.front();
			m_queue.pop();

		}
		lock.unlock();
	}

	void push(const T item) {
		std::unique_lock < std::mutex > lock(m_mutex);
		m_queue.push(item);
		lock.unlock();
		m_cond.notify_one();
	}

	void push(T&& item) {
		std::unique_lock < std::mutex > lock(m_mutex);
		m_queue.push(std::move(item));
		lock.unlock();
		m_cond.notify_one();
	}

private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cond;
};

#endif /* QUEUE_H_ */

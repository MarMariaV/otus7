#pragma once

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>

class Subscriber {
public:
    virtual ~Subscriber() = default;

    virtual void update() = 0;
};

class Publisher {
public:
    virtual ~Publisher() = default;

    virtual void subscribe(const std::shared_ptr<Subscriber>& obs) = 0;
};

class CommandPrinterPublisher : public Publisher {
public:
    void subscribe(const std::shared_ptr<Subscriber>& obs) override {
        m_subs.emplace_back(obs);
    }

    void setBulk(std::vector<std::string>* bulk) {
        m_bulk = bulk;
        notify();
    }

    std::vector<std::string>* getBulk() {
        return m_bulk;
    }

    void notify() {
        auto iter = m_subs.begin();
        while(iter != m_subs.end()) {
            auto ptr = iter->lock();
            if (ptr) {
                ptr->update();
                ++iter;
            } else {
                m_subs.erase(iter++);
            }
        }
    }

    std::vector<std::string>* m_bulk;
    std::list<std::weak_ptr<Subscriber>> m_subs;
};

class ConsolePrinter : public Subscriber, public std::enable_shared_from_this<ConsolePrinter> {
public:
    static std::shared_ptr<ConsolePrinter> create(CommandPrinterPublisher* publ) {
        auto ptr = std::shared_ptr<ConsolePrinter>{new ConsolePrinter{}};
        ptr->init(publ);
        return ptr;
    }

    void update() override {
        std::cout << "bulk: ";
        const auto& bulk = m_publisher->getBulk();
        for (const auto& cmd : *bulk) {
            std::cout << cmd << (&cmd != &bulk->back() ? ", " : "");
        }
        std::cout << "\n";
    }

private:
    ConsolePrinter() = default;

    void init(CommandPrinterPublisher* publ) {
        m_publisher = publ;
        m_publisher->subscribe(shared_from_this());
    }

    CommandPrinterPublisher *m_publisher{};
};

class FilePrinter : public Subscriber, public std::enable_shared_from_this<FilePrinter> {
public:
    static std::shared_ptr<FilePrinter> create(CommandPrinterPublisher* publ) {
        auto ptr = std::shared_ptr<FilePrinter>{new FilePrinter{}};
        ptr->init(publ);
        return ptr;
    }

    void update() override {
        std::ofstream fout;
        const auto& bulk = m_publisher->getBulk();
        auto time = std::chrono::system_clock::now();
        fout.open("bulk" + std::to_string(time.time_since_epoch().count()) + ".log", std::ios_base::out);
        fout << "bulk: ";
        for (const auto& cmd : *bulk) {
            fout << cmd << (&cmd != &bulk->back() ? ", " : "");
        }
        fout.close();
    }

private:
    FilePrinter() = default;

    void init(CommandPrinterPublisher* publ) {
        m_publisher = publ;
        m_publisher->subscribe(shared_from_this());
    }

    CommandPrinterPublisher *m_publisher{};
};
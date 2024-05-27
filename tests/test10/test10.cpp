#include "HServerApplication.h"

namespace Ht {

class MyApplication : public HServerApplication {
public:
    MyApplication() {}
    virtual ~MyApplication() {}

protected:
    virtual void initializeApplication() override {
        std::cout << "Initializing MyApplication" << std::endl;
    }

    virtual void uninitializeApplication() override {
        std::cout << "Uninitializing MyApplication" << std::endl;
    }

    virtual void defineApplicationOptions() override {
        std::cout << "Defining MyApplication options" << std::endl;
    }

    virtual int main(const std::vector<HString>& args) override {
        std::cout << "MyApplication running with arguments:" << std::endl;
        for (const auto& arg : args) {
            std::cout << arg << std::endl;
        }
        return 0;
    }
};

} // namespace Ht

int main(int argc, char** argv) {
    Ht::MyApplication app;
    app.initialize();
    app.defineOptions();
    int result = app.run(argc, argv);
    app.uninitialize();
    return result;
}


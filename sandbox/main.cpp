#include "context.hpp"
#include <ctime>
#include <filesystem>

int main(int argc, char** argv) {
    Context::Init();
    Context& ctx = Context::GetInst();

    while (!ctx.ShouldExit()) {
        ctx.Update();
    }
    
    Context::Destroy();

    return 0;
}

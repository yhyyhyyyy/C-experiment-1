#pragma once

#include "Executor.hpp"

namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;
    ~ExecutorImpl() override = default;

    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

    void Execute(const std::string& commands) noexcept override;
    Pose Query() const noexcept override;

private:
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;

    class MoveCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept
        {
            executor.Move();
        }
    };

private:
    Pose pose{0, 0, '?'};
};
}  // namespace adas
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

    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual void DoOperate(ExecutorImpl& executor) const noexcept = 0;
    };

    class MoveCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            executor.Move();
        }
    };

    class TurnLeftCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            executor.TurnLeft();
        }
    };

    class TurnRightCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            executor.TurnRight();
        }
    };

private:
    Pose pose{0, 0, '?'};
};

}  // namespace adas
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

public:
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;

    void Fast() noexcept;
    bool IsFast() const noexcept;

private:
    Pose pose{0, 0, '?'};
    bool fast{false};
};
}  // namespace adas
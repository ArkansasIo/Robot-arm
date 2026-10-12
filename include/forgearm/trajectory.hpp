#pragma once
namespace forgearm {
struct MotionLimits { double max_velocity{1.0}; double max_acceleration{1.0}; };
struct TrajectorySample { double time{}; double position{}; double velocity{}; double acceleration{}; };
class TrapezoidalTrajectory {
public:
 TrapezoidalTrajectory(double start,double finish,MotionLimits limits);
 [[nodiscard]] double duration() const noexcept;
 [[nodiscard]] TrajectorySample sample(double time) const noexcept;
 [[nodiscard]] double start() const noexcept;
 [[nodiscard]] double finish() const noexcept;
private:
 double start_{},finish_{},distance_{},direction_{1.0},accel_{},velocity_{},accel_time_{},cruise_time_{},total_time_{},accel_distance_{};
};
} // namespace forgearm

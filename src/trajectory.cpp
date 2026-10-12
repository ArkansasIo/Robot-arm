#include "forgearm/trajectory.hpp"
#include <cmath>
#include <stdexcept>
namespace forgearm {
TrapezoidalTrajectory::TrapezoidalTrajectory(double start,double finish,MotionLimits limits)
 :start_(start),finish_(finish),distance_(std::abs(finish-start)),direction_(finish>=start?1.0:-1.0) {
 if(!std::isfinite(start)||!std::isfinite(finish)||!std::isfinite(limits.max_velocity)||!std::isfinite(limits.max_acceleration)||limits.max_velocity<=0.0||limits.max_acceleration<=0.0)
  throw std::invalid_argument("Trajectory endpoints and positive motion limits must be finite.");
 if(distance_==0.0) return;
 accel_=limits.max_acceleration;
 const double full_distance=limits.max_velocity*limits.max_velocity/accel_;
 if(distance_<=full_distance) {
  velocity_=std::sqrt(distance_*accel_); accel_time_=velocity_/accel_; cruise_time_=0.0; accel_distance_=distance_/2.0;
 } else {
  velocity_=limits.max_velocity; accel_time_=velocity_/accel_; accel_distance_=0.5*accel_*accel_time_*accel_time_;
  cruise_time_=(distance_-2.0*accel_distance_)/velocity_;
 }
 total_time_=2.0*accel_time_+cruise_time_;
}
double TrapezoidalTrajectory::duration() const noexcept{return total_time_;}
double TrapezoidalTrajectory::start() const noexcept{return start_;}
double TrapezoidalTrajectory::finish() const noexcept{return finish_;}
TrajectorySample TrapezoidalTrajectory::sample(double t) const noexcept {
 if(distance_==0.0||t<=0.0)return {0.0,start_,0.0,0.0};
 if(t>=total_time_)return {total_time_,finish_,0.0,0.0};
 double p{},v{},a{};
 if(t<accel_time_){p=0.5*accel_*t*t;v=accel_*t;a=accel_;}
 else if(t<accel_time_+cruise_time_){p=accel_distance_+velocity_*(t-accel_time_);v=velocity_;}
 else {const double td=total_time_-t;p=distance_-0.5*accel_*td*td;v=accel_*td;a=-accel_;}
 return {t,start_+direction_*p,direction_*v,direction_*a};
}
} // namespace forgearm

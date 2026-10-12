#include "forgearm/collision.hpp"
#include <algorithm>
#include <cmath>
namespace forgearm {
namespace {
double cross(Vec2 a,Vec2 b)noexcept{return a.x*b.y-a.y*b.x;}
bool on_segment(Vec2 p,Segment2D s,double e)noexcept{return p.x>=std::min(s.a.x,s.b.x)-e&&p.x<=std::max(s.a.x,s.b.x)+e&&p.y>=std::min(s.a.y,s.b.y)-e&&p.y<=std::max(s.a.y,s.b.y)+e;}
}
bool segments_intersect(Segment2D a,Segment2D b,double e)noexcept{
 const Vec2 r=a.b-a.a,s=b.b-b.a,d=b.a-a.a;const double den=cross(r,s);
 if(std::abs(den)<=e){if(std::abs(cross(d,r))>e)return false;return on_segment(a.a,b,e)||on_segment(a.b,b,e)||on_segment(b.a,a,e)||on_segment(b.b,a,e);}
 const double t=cross(d,s)/den,u=cross(d,r)/den;return t>=-e&&t<=1.0+e&&u>=-e&&u<=1.0+e;
}
double point_segment_distance(Vec2 p,Segment2D s)noexcept{
 const Vec2 v=s.b-s.a;const double len2=v.dot(v);if(len2<=1e-18)return distance(p,s.a);
 const double t=std::clamp((p-s.a).dot(v)/len2,0.0,1.0);return distance(p,s.a+v*t);
}
bool segment_intersects_circle(Segment2D s,CircleObstacle c,double clearance)noexcept{
 if(!std::isfinite(c.radius)||c.radius<0.0||!std::isfinite(clearance)||clearance<0.0)return true;
 return point_segment_distance(c.center,s)<=c.radius+clearance;
}
std::array<Vec2,4> link_points(const ArmConfig& c,const JointAngles& q)noexcept{
 const double a=q.q[0],b=a+q.q[1],d=b+q.q[2];const auto& l=c.link_lengths;
 return {{{0,0},{l[0]*std::cos(a),l[0]*std::sin(a)},
 {l[0]*std::cos(a)+l[1]*std::cos(b),l[0]*std::sin(a)+l[1]*std::sin(b)},
 {l[0]*std::cos(a)+l[1]*std::cos(b)+l[2]*std::cos(d),l[0]*std::sin(a)+l[1]*std::sin(b)+l[2]*std::sin(d)}}};
}
bool arm_intersects_obstacles(const ArmConfig& c,const JointAngles& q,const std::vector<CircleObstacle>& obs,double radius)noexcept{
 if(!std::isfinite(radius)||radius<0.0)return true;const auto p=link_points(c,q);
 for(std::size_t i=0;i<3;++i)for(const auto& o:obs)if(segment_intersects_circle({p[i],p[i+1]},o,radius))return true;
 return false;
}
} // namespace forgearm

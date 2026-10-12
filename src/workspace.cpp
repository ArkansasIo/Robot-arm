#include "forgearm/workspace.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace forgearm {
Workspace::Workspace(const ArmConfig& c){
 double sum=0.0,longest=0.0;
 for(double l:c.link_lengths){if(!std::isfinite(l)||l<=0.0)throw std::invalid_argument("Workspace requires positive finite link lengths.");sum+=l;longest=std::max(longest,l);}
 maximum_radius_=sum;minimum_radius_=std::max(0.0,2.0*longest-sum);
}
WorkspaceEnvelope Workspace::radial_envelope()const noexcept{return {minimum_radius_,maximum_radius_};}
bool Workspace::inside_radial_envelope(Vec2 p,double tol)const noexcept{const double r=p.length();return r>=minimum_radius_-tol&&r<=maximum_radius_+tol;}
bool Workspace::inside_bounding_box(Vec2 p,double tol)const noexcept{return std::abs(p.x)<=maximum_radius_+tol&&std::abs(p.y)<=maximum_radius_+tol;}
bool Workspace::pose_has_ik(const Kinematics& k,const Pose2D& p)const{return k.inverse(p).success;}
} // namespace forgearm

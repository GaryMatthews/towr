/**
 @file    nlp_optimizer_node.cc
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Jul 21, 2016
 @brief   Declares the ROS interface to motion optimizer.
 */

#ifndef XPP_OPT_INCLUDE_XPP_ROS_NLP_OPTIMIZER_NODE_H_
#define XPP_OPT_INCLUDE_XPP_ROS_NLP_OPTIMIZER_NODE_H_

#include <string>

#include <ros/publisher.h>
#include <ros/subscriber.h>
#include <rosbag/bag.h>

#include <xpp_msgs/RobotStateCartesian.h>
#include <xpp_msgs/RobotStateCartesianTrajectory.h>
#include <xpp_msgs/OptParameters.h>
#include <xpp_msgs/UserCommand.h>    // receive from user

#include <xpp/motion_optimizer_facade.h>
#include <xpp/nlp.h>
#include <xpp/robot_state_cartesian.h>

namespace xpp {
namespace ros {

class NlpOptimizerNode {
public:
  using MotionOptimizerFacade = xpp::opt::MotionOptimizerFacade;

public:
  NlpOptimizerNode ();
  virtual ~NlpOptimizerNode () {};

private:

  void OptimizeMotion();
  void CurrentStateCallback(const xpp_msgs::RobotStateCartesian&);
  void UserCommandCallback(const xpp_msgs::UserCommand&);

  ::ros::Subscriber user_command_sub_;
  ::ros::Subscriber current_state_sub_;
  ::ros::Publisher cart_trajectory_pub_;
  ::ros::Publisher opt_parameters_pub_;

  MotionOptimizerFacade motion_optimizer_;
  double dt_; ///< discretization of output trajectory (1/TaskServoHz)
  std::string rosbag_name_; ///< folder to save bags

  xpp_msgs::UserCommand user_command_msg_;

  xpp_msgs::RobotStateCartesianTrajectory BuildTrajectoryMsg() const;

  void SaveOptimizationAsRosbag() const;
  void SaveTrajectoryInRosbag (rosbag::Bag&, const std::vector<RobotStateCartesian>& traj,
                               const std::string& topic) const;
  xpp_msgs::OptParameters BuildOptParametersMsg() const;
};

} /* namespace ros */
} /* namespace xpp */

#endif /* XPP_OPT_INCLUDE_XPP_ROS_OPTIMIZER_NODE_H_ */

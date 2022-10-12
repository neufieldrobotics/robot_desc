#include <ros/ros.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include <string>

#include <dynamic_reconfigure/server.h>
#include <robot_desc/dynamic_paramsConfig.h>
double tx, ty, tz, rx, ry, rz;

using namespace std;
void callback(robot_desc::dynamic_paramsConfig &config, uint32_t level) {
  ROS_INFO("Reconfigure Request: %f %f %f %f %f %f", 
            config.rx, config.ry, config.rz, config.tx, config.ty, config.tz);
  tx = config.tx;
  ty = config.ty;
  tz = config.tz;
  rx = config.rx;
  ry = config.ry;
  rz = config.rz;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "dynamic_tf");
  ros::NodeHandle private_node("");
  dynamic_reconfigure::Server<robot_desc::dynamic_paramsConfig> server;
  dynamic_reconfigure::Server<robot_desc::dynamic_paramsConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  ros::Rate ros_rate(50);
  tf2_ros::TransformBroadcaster tf_bcast{};
  ROS_INFO_STREAM("*** PARAMETER SETTINGS ***");
  string parent, child;
  private_node.getParam("lidar_frame", parent);
    
  ROS_INFO_STREAM("  parent frame: " << parent);

  private_node.getParam("cam_frame", child);
    
  ROS_INFO_STREAM("  child frame: " << child);
  while(ros::ok()){
     
 // ROS_INFO("pUblishing static transform");

     geometry_msgs::TransformStamped transformStamped;
  
     transformStamped.header.stamp = ros::Time::now();
     transformStamped.header.frame_id = parent;     //"os1_lidar";
     transformStamped.child_frame_id =  child;            //"cam_2_optical_frame";
     transformStamped.transform.translation.x = tx;
     transformStamped.transform.translation.y = ty;
     transformStamped.transform.translation.z = tz;
     tf2::Quaternion q;
     q.setRPY(rx, ry, rz);
     transformStamped.transform.rotation.x = q.x();
     transformStamped.transform.rotation.y = q.y();
     transformStamped.transform.rotation.z = q.z();
     transformStamped.transform.rotation.w = q.w();

     tf_bcast.sendTransform(transformStamped);
     ros::spinOnce();
     ros_rate.sleep();
  }
  
  
  return 0;
}


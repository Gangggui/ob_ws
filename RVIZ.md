#### 交互球（interactive_marker）
>https://www.jianshu.com/p/d51003fbeb26

```c++
void processFeedback( const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback )

{

std::ostringstream s;

s << "Feedback from marker '" << feedback->marker_name << "' "

<< " / control '" << feedback->control_name << "'";

  

std::ostringstream mouse_point_ss;

if( feedback->mouse_point_valid )

{

mouse_point_ss << " at " << feedback->mouse_point.x

<< ", " << feedback->mouse_point.y

<< ", " << feedback->mouse_point.z

<< " in frame " << feedback->header.frame_id;

}

  

switch ( feedback->event_type )

{

case visualization_msgs::InteractiveMarkerFeedback::BUTTON_CLICK:

ROS_INFO_STREAM( s.str() << ": button click" << mouse_point_ss.str() << "." );

break;

  

case visualization_msgs::InteractiveMarkerFeedback::MENU_SELECT:

ROS_INFO_STREAM( s.str() << ": menu item " << feedback->menu_entry_id << " clicked" << mouse_point_ss.str() << "." );

break;

  

case visualization_msgs::InteractiveMarkerFeedback::POSE_UPDATE:

ROS_INFO_STREAM( s.str() << ": pose changed"

<< "\nposition = "

<< feedback->pose.position.x

<< ", " << feedback->pose.position.y

<< ", " << feedback->pose.position.z

<< "\norientation = "

<< feedback->pose.orientation.w

<< ", " << feedback->pose.orientation.x

<< ", " << feedback->pose.orientation.y

<< ", " << feedback->pose.orientation.z

<< "\nframe: " << feedback->header.frame_id

<< " time: " << feedback->header.stamp.sec << "sec, "

<< feedback->header.stamp.nsec << " nsec" );

break;

  

case visualization_msgs::InteractiveMarkerFeedback::MOUSE_DOWN:

ROS_INFO_STREAM( s.str() << ": mouse down" << mouse_point_ss.str() << "." );

break;

  

case visualization_msgs::InteractiveMarkerFeedback::MOUSE_UP:

ROS_INFO_STREAM( s.str() << ": mouse up" << mouse_point_ss.str() << "." );

break;

}

  

server->applyChanges();

}
```
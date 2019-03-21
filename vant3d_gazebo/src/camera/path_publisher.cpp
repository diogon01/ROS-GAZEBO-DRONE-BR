//
// Created by Daniel on 21/03/19.
//

#include "gazebo/gazebo.hh"
#include "gazebo/common/common.hh"
#include "gazebo/math/Vector3.hh"
#include "gazebo/transport/transport.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/msgs/msgs.hh"

using namespace gazebo;

int main(int _argc, char *_argv[]){

    msgs::PoseAnimation msg;

    msg.set_model_name("box") /// Alterar para nome do modelo em SDF a ser movimentado
    msgs::Pose *p = msg.add_pose();
    msgs::Set(p, ignition::math::Pose3d(5,-5,0,0,0,0))
    p = msg.add_pose();
    msgs::Set(p, ignition::math::Pose3d(5,-5,0,0,0,0))
    p = msg.add_pose();
    msgs::Set(p, ignition::math::Pose3d(5,-5,0,0,0,0))

    transport::init();
    transport::run();
    transport::NodePtr node(new gazebo::transport::Node());
    node->Init("default");

    /// modelmove_world é o nome do arquivo teste .world
    /// alterar quando for criar mundo de teste
    const std::string topicName = "/gazebo/modelmove_world" + msg.model_name() + "/camera_move";
    gazebo::transport::PublisherPtr pathPub = node-><msgs::PoseAnimation>Advertise(topicName);

    std::cout << "Waiting for connection in" << topicName << std::endl;
    pathPub->WaitForConnection();
    pathPub->Publish(msg);

    std::cout << "Path published!" <std::endl;

    gazebo::transport::fini();
    return 0;
}
/*
 * Copyright (C) 2012 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#include <gazebo/gazebo.hh>
#include <ignition/math.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>

namespace gazebo {
    class AnimatedCamera : public ModelPlugin {


    public:
        void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/) {
            // Store the pointer to the model
            this->_model = _parent;
            this->_link = _parent->GetLinks()[0];
            this->world_ = _parent->GetWorld();


            std::cerr << "\nO plugin do labmetro da camera acessou o  [" <<
                      _link->GetName() << "]\n";
            std::cerr << "\nO A posicao da camera  [" <<
                      _model->GetWorldPose() << "]\n";


            this->connections.push_back(event::Events::ConnectWorldUpdateBegin(
                    std::bind(&AnimatedCamera::OnUpdate, this, std::placeholders::_1)));







            // create the animation
            gazebo::common::PoseAnimationPtr anim(
                    // name the animation "test",
                    // make it last 10 seconds,
                    // and set it on a repeat loop
                    new gazebo::common::PoseAnimation("test", 450, false));

            gazebo::common::PoseKeyFrame *key;


            float frame = 0;
            float pos_z = 0;
            float pos_x = -7.272;

            // set starting location of the box
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));

            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x += 1.818, 0, pos_z));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));

            // set starting location of the box
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x += 1.818, 0, pos_z));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));

            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x += 1.818, 0, pos_z));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));

            // set starting location of the box
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x += 1.818, 0, pos_z));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));

            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x += 1.818, 0, pos_z));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            // set starting location of the box
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x += 1.818, 0, pos_z));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));

            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x += 1.818, 0, pos_z));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z -= 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            // set starting location of the box
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x += 1.818, 0, pos_z));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));
            key = anim->CreateKeyFrame(frame += 5);
            key->Translation(ignition::math::Vector3d(pos_x, 0, pos_z += 2));
            key->Rotation(ignition::math::Quaterniond(0, 0, 0));






            // set the animation
            _parent->SetAnimation(anim);
        }

    public:
        void
        OnUpdate(const common::UpdateInfo &_info) {
            // Time delta
            std::cerr << "\nO A posicao da camera  [" <<
                      _info.simTime << "]\n";
        }

        // Pointer to the model
    private:
        physics::ModelPtr _model;
        // Pointer to the model
    private:
        physics::LinkPtr _link;
    private:
        // World
        physics::WorldPtr world_;
    private: std::vector<event::ConnectionPtr> connections;

        // Pointer to the update event connection
    private:
        event::ConnectionPtr updateConnection;
    };

// Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(AnimatedCamera)
}

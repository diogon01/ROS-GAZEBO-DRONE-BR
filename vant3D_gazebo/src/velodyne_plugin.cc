//
// Created by vant3d on 27/02/19.
//

#ifndef _VELODYNE_PLUGIN_HH_
#define _VELODYNE_PLUGIN_HH_

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"


namespace gazebo {
    /// O plugin que controla o Sensor Velodine.
    class VelodynePlugin : public ModelPlugin {

        /// Um nodo usado pelo ROS para transport
    private:
        std::unique_ptr<ros::NodeHandle> rosNode;
        /// Ponteiro do modelo
    private:
        physics::ModelPtr model;
        /// Ponteiro do joint do modelo
    private:
        physics::JointPtr joint;
        /// UM controller PID do joint
    private:
        common::PID pid;

        /// Construtor da classe
    public:
        VelodynePlugin() {}

        /// \brief A função load é chamada pelo Gazebo quando o plugin é
        ///  inserido na simulação
        /// \param[in] _model Um ponteiro para o modelo que este plugin
        /// está anexado.
        /// \param[in] _sdf Um ponteiro para o elemento SDF do plug-in.
    public:
        virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) {
            // Just output a message for now
            std::cerr << "\nO plugin do velodyne é anexado ao modelo [" <<
                      _model->GetName() << "]\n";
            /// Checando se o modelo é correto
            if (_model->GetJointCount() == 0) {
                std::cerr << "Número incorreto de juntas";
                return;
            }
            /// Armazene o ponteiro do modelo por conveniência.
            this->model = _model;

            /// Pegue a primeira junta. Estamos fazendo uma suposição sobre o modelo
            /// tendo uma articulação que é a articulação rotacional.
            this->joint = _model->GetJoints()[0];

            /// Setup um P-controller tenho que ver melhor depois como funciona
            this->pid = common::PID(0.1, 0, 0);

            /// Aplica o controler P no Joint 0
            this->model->GetJointController()->SetVelocityPID(
                    this->joint->GetScopedName(), this->pid);

            /// Defina a velocidade alvo da junta(JOINT). Esta velocidade alvo é apenas
            /// para fins de demonstração.
            this->model->GetJointController()->SetVelocityTarget(
                    this->joint->GetScopedName(), 10.0);

        }

    };
    // Informe o Gazebo sobre este plugin, para que o Gazebo possa chamar o Load neste plugin.
    GZ_REGISTER_MODEL_PLUGIN(VelodynePlugin)
}
#endif
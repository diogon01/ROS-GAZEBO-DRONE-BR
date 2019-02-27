//
// Created by vant3d on 27/02/19.
//

#ifndef _VELODYNE_PLUGIN_HH_
#define _VELODYNE_PLUGIN_HH_

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
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

        ///@brief Um ponteiro do transporte Nodo
    private:
        transport::NodePtr node;

        ///@brief Um assinante de um tópico nomeado
    private:
        transport::SubscriberPtr sub;


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


            /// Atribuindo a velocidade como zero por default
            double velocidade = 0;

            /// Verifica se o elemento velocidade existe no arquivo e le o parametro
            /// de velocidade
            if (_sdf->HasElement("velocidade"))
                velocidade = _sdf->Get<double>("velocidade");

            /// Defina a velocidade alvo da junta(JOINT). Esta velocidade alvo é apenas
            /// para fins de demonstração.
            this->model->GetJointController()->SetVelocityTarget(
                    this->joint->GetScopedName(), velocidade);

            ///Criando o Nodo
            this->node = transport::NodePtr(new transport::Node());

#if GAZEBO_MAJOR_VERSION < 8

            this->node->Init(this->model->GetWorld()->GetName());
#else
            this->node->Init(this->model->GetWorld()->Name());
#endif
            /// Criando o nome do topico
            std::string nomeTopico = "~/" + this->model->GetName() + "/vel_cmd";

            /// Assine o tópico e registre um retorno de chamada
            this->sub = this->node->Subscribe(nomeTopico,
                                              &VelodynePlugin::OnMsg, this);


        }

        /// @brief Ajusta a velocidade do velodyne dinamicamente
        /// @param _vel Adiciona nova velocidade ao Velodine
    public:
        void SetarVelocidade(const double &_vel) {
            /// Seta na junta(JOINT) a velocidade
            this->model->GetJointController()->SetVelocityTarget(
                    this->joint->GetScopedName(), _vel);
        }

        /// \brief Handle incoming message
        /// \param[in] _msg Repurpose a vector3 message. This function will
        /// only use the x component.
    private:
        void OnMsg(ConstVector3dPtr &_msg) {
            this->SetarVelocidade(_msg->x());
        }

    };

    // Informe o Gazebo sobre este plugin, para que o Gazebo possa chamar o Load neste plugin.
    GZ_REGISTER_MODEL_PLUGIN(VelodynePlugin)
}
#endif
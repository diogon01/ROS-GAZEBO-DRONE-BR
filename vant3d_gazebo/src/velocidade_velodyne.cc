#include <gazebo/gazebo_config.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>

/// A API do Gazebo mudou entre os seus lançamentos.
/// Essas mudanças são tratadas com #if e #endif
#if GAZEBO_MAJOR_VERSION < 6
#include <gazebo/gazebo.hh>
#else

#include <gazebo/gazebo_client.hh>

#endif

int main(int _argc, char **_argv) {
    /// Carrega o cliente do Gazebo
#if GAZEBO_MAJOR_VERSION < 6
    gazebo::setupClient(_argc, _argv);
#else
    gazebo::client::setup(_argc, _argv);
#endif
    /// Criando seu Nó(node) de comunicação
    gazebo::transport::NodePtr node(new gazebo::transport::Node());
    node->Init();

    /// Publicando o topico do velodyne
    gazebo::transport::PublisherPtr pub =
            node->Advertise<gazebo::msgs::Vector3d>("~/velodyne_labmetro/comando_velocidade");

    /// Aguarda ate o momeento que um assinante(Subscriber) se conecte a esse editor
    pub->WaitForConnection();

    /// Crie uma mensagem do tipo vector3D
    gazebo::msgs::Vector3d msg;

    /// Ajustando a velocidade da junta no Eixo X
#if GAZEBO_MAJOR_VERSION < 6
    gazebo::msgs::Set(&msg, gazebo::math::Vector3(std::atof(_argv[1]), 0, 0));
#else
    gazebo::msgs::Set(&msg, ignition::math::Vector3d(std::atof(_argv[1]), 0, 0));
#endif

    /// Enviando a mensagem
    pub->Publish(msg);

    /// Finalizando o cliente do GAZEBO
#if GAZEBO_MAJOR_VERSION < 6
    gazebo::shutdown();
#else
    gazebo::client::shutdown();
#endif

}
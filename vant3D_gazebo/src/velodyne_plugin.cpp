//
// Created by vant3d on 27/02/19.
//

#ifndef _VELODYNE_PLUGIN_HH_
#define _VELODYNE_PLUGIN_HH_

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>

namespace gazebo {
    /// O plugin que controla o Sensor Velodine.
    class PluginVelodine : public ModelPlugin {
        /// Construtor da classe
    public:
        PluginVelodine() {}

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

        }

    };
    // Informe o Gazebo sobre este plugin, para que o Gazebo possa chamar o Load neste plugin.
    GZ_REGISTER_MODEL_PLUGIN(PluginVelodine)
}
#endif
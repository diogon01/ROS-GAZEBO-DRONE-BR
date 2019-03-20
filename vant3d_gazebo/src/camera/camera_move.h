/*
 * Copyright (C) 2019 Labmetro UFSC
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

#ifndef VANT3D_GAZEBO_CAMERA_MOVE_H
#define VANT3D_GAZEBO_CAMERA_MOVE_H

#include <gazebo/msgs/pose_animation.pb.h>
#include <vector>

namespace gazebo {
    /// @brief Plugin para transportar um modelo de ponto a ponto usando Pose Animation
    class CameraMove : public ModelPlugin {

        /// @brief Ponteiro do modelo definido no plugin
    private:
        physics::ModelPtr model;
        /// @brief Ponteiro para a animação de movimento para executar
    private:
        gazebo::common::PoseAnimationPtr anim;
        /// @brief Nó de transporte usado para se comunicar com o sistema de transporte
    private:
        transport::NodePtr node;
        /// @brief Assinante(Subscriber) para obter mensagens de caminho
    private:
        transport::SubscriberPtr pathSubscriber;
        ///  @brief Ponto de partida da trajetória  a seguir
    private:
        math::Vector3 startPosition;
        /// @brief Caminho a seguir
    private:
        std::vector<math::Pose> pathGoals

        /// @brief Construtor da classe
    public:
        CameraMove();

        /// @brief Realize o movimento do modelo
        /// @param[in] _start ponto de partida
        /// @param[in] _end ponto final
        /// @param[in, out] _translation tradução feita antes do início
    private:
        void Move(const math::Vector3 &_start, const math::Vector3 &_end, math::Vector3 &_translation);

        /// @brief Analisar trajetória definidas no SDF
        /// @param[in] _sdf ponteiro sdf correspondente ao elemento de trajetórias
        /// @return True(verdadeiro) se a análise foi bem sucedida ou não
    private:
        bool LoadGoalsFromSDF(const sdf::ElementPtr _sdf);

        /// @brief preparar o movimento do modelo.
        /// Inicializa a animação e as variáveis ​​relacionadas
        /// Chama o metodo Moce para cada trajetória
    public:
        void InitiateMove();

        /// @brief Retorno de chamada(callback) a ser executado quando receber uma mensagem de caminho.
        /// @param[in] _msg mensagem de caminho recebida para animar.
    public:
        void OnPathMsg(ConstPoseAnimationPtr &_msg);

        /// @brief Função Load do PLugin
        /// @param[in] _parent Ponteiro do Model do modelo é definido no plugin
        /// @param[in] _sdf ponteiro para o SDF do modelo
    public:
        void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);

    };
}

#endif //VANT3D_GAZEBO_CAMERA_MOVE_H

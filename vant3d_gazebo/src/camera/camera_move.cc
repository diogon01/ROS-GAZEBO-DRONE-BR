/*
 * Copyright (C) 2019 Labmetro UFSC | Diogo Henrique
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
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/transport/transport.hh>
#include <ignition/math/Vector3.hh>
#include <ignition/math/Pose3.hh>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#include "camera_move.h"

using namespace gazebo;


/// Registrando o plugin CameraMove no gazebo
GZ_REGISTER_MODEL_PLUGIN(CameraMove);

/// Criando Contrutor da Classe sem parametros
CameraMove::CameraMove() {

}

void CameraMove::Move(const math::Vector3 &_start, const math::Vector3 &_end, math::Vector3 &_translation) {

    int duration = floor(_start.Distance(_end.x, _end.y, _end.z));
    math::Vector3 diff = _end - _start;
    float xStep = diff.x / duration;
    float yStep = diff.y / duration;
    float zStep = diff.z / duration;
    int currFrame = this->anim->GetKeyFrameCount();

    for (int j = 0; j <= duration; ++j) {

        gazebo::common::PoseKeyFrame *key = this->anim->CreateKeyFrame(j + currFrame);

        key->Translation(ignition::math::Vector3d(
                _translation.x + xStep * j,
                _translation.y + yStep * j,
                _translation.z + zStep * j));

    }
}

void CameraMove::InitiateMove() {

    /// Recebendo distância inicial até objetivo
    float pathLength = this->startPosition.Distance(this->pathGoals[0].pos);

    /// Calculando distancia total e adicionando distancia até o objetivo
    for (unsigned int j = 0; j < this->pathGoals.size(); ++j) {
        pathLength += this->pathGoals[j].pos.Distance(this->pathGoals[j + 1].pos);
    }

    /// Criando Animação
    this->anim = gazebo::common::PoseAnimationPtr(
            new gazebo::common::PoseAnimation("test", pathLength + 1, false));

    gazebo::common::PoseKeyFrame *key;

    /// Define local de inicio dentro de uma caixa

    key  = this->anim->CreateKeyFrame(0);
    key->Translation(ignition::math::Vector3d(0,0,0));
    key->Rotation(ignition::math::Quaterniond(0,0,0));

    math::Vector3 translation = math::Vector3(0,0,0);

    /// move do ponto inicial ao primeiro objetivo
    this->Move(this->startPosition, this->pathGoals[0].pos, translation);

    for (unsigned int k = 0; k < this->pathGoals.size() ; ++k) {
        this->Move(this->pathGoals[k].pos, this->pathGoals[k+1].pos, translation);
    }

    /// Define animação
    this->model->SetAnimation(this->anim);

}

void CameraMove::OnPathMsg(ConstPoseAnimationPtr &_msg){
    gzmsg << "[model_move] Received path message" << std::endl;

    // Store message poses into the pathGoals and launch movement
    for (unsigned int i = 0; i < _msg->pose_size(); ++i)
        this->pathGoals.push_back(gazebo::msgs::ConvertIgn(_msg->pose(i)));

    this->InitiateMove();
}

bool CameraMove::LoadGoalsFromSDF(const sdf::ElementPtr _sdf) {

    gzmsg << "[camera_move] Processando trajetoria definida pelo arquivo SDF" << std::endl;
    GZ_ASSERT(_sdf, "_sdf elemento é nulo");

    /// Verifica se arquivo SDF possui elementos de pose para trajetória

    if(!_sdf -> HasElement("pose")){

        gzerr << "[camera_move] SDF com tag de trajetoria mas sem pose/s element/s" << std::endl;
        return false;
    }
    /// Salva em variavel o numero de elementos de pose
    sdf::ElementPtr poseElem = _sdf->GetElement("pose");


    while(poseElem){
        this->pathGoals.push_back(poseElem->Get<math::Pose>());
        poseElem = poseElem->GetNextElement("pose");
    }

    GZ_ASSERT(this->pathGoals.size() > 0, "pathGoals nao deve ser zero");

    return true;
}

void CameraMove::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {

    /// Armazena pontero para o modelo
    this->model = _parent;
    this->node = transport::NodePtr(new transport::Node());
    this->node->Init(this->model->GetWorld()->GetName());

    /// Recebe parametros do SDF se disponivel
    if(_sdf->HasElement("goals")){

        if(this->LoadGoalsFromSDF(_sdf->GetElement("goals"))){

            /// Pronto para inicializar o movimento, Armazena pose inicial do modelo
            /// e chama initiateMove
            ignition::math::Vector3d sdfPose =
                    _sdf->GetParent()->GetElement("pose")
                    ->Get<ignition::math::Pose3d>().Pos();

            this->startPosition = math::Vector3(sdfPose.X(), sdfPose.Y(), sdfPose.Z());

            this->InitiateMove();
        }
        else{
            gzerr << "[camera_move] Problema ao carregar trajetoria do SDF"
                    << "Impossivel Fazer o movimento" <<std::endl;
            }
    }

    /// Desenvolvendo Inscrição
    std::string pathTopicName = std::string("~/") + _parent->GetName() + "/camera_move";
    this->pathSubscriber = node->Subscribe(pathTopicName, &CameraMove::OnPathMsg, this);
    gzmsg << "[camera_move] Inscrito para receber caminhos em: " << pathTopicName << std::endl;

}

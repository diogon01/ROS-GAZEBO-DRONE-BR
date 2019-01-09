## Estrutura e requisitos do modelo
### Visão Geral
O Gazebo é capaz de carregar dinamicamente modelos em simulação, seja de forma programática ou através da interface gráfica. Este documento descreve a estrutura de diretórios do modelo do Gazebo e os arquivos necessários em um diretório de modelos.

### O repositório do banco de dados de modelo
O banco de dados oficial de "models" do GAZEBO é um repositório bitbucket encontrado [nesse link](https://bitbucket.org/osrf/gazebo_models).
Você pode clonar o repositório usando:
```
hg clone https://bitbucket.org/osrf/gazebo_models
```

### Arquitetura de um Modelo (models) no GAZEBO
Um modelo deve obedecer a um diretório e uma estrutura de arquivos específicos. A raiz de um modelo, contém um diretório para cada model e um arquivo `config` com informações sobre o modelo. Cada metadata model possui também model `model.config` que contém metadados sobre o modelo. Um arquivo de modelo também contém o SDF para o modelo e os materiais, malhas e plug-ins.

A estrutura é a seguinte (neste exemplo, o banco de dados possui apenas um modelo chamado plataforma_47):

Model
- database.config: Metadados sobre o banco de dados. Agora isso é preenchido automaticamente a partir do `CMakeLists.txt`
- plataforma_47: Diretorio dos arquivos do Modelo
    - model.config: Meta-dados(XML) escificando o modelo
    - model.SDF: Descrição [SDF](http://sdformat.org/) do modelo
    - /meshes: Diretório contendo todos os arquivos COLLADA e STL
    - /materials: Diretório que deve conter apenas os subdiretórios de `texturas` e `scripts`
        - /textures: Diretório para arquivos de imagem (jpg, png, etc).
        - /scripts: Diretório para scripts de material OGRE
    -/plugins: Diretório para arquivos de fonte e cabeçalho de plug-in

### Diretório(pasta) de Plugins
Este é um diretório opcional que contém todos os plugins do modelo.
### Diretório(pasta) de malhas 
Este é um diretório opcional que contém todos os arquivos COLLADA e / ou STL para o modelo.
### Diretório(pasta) de Material
Este é um diretório opcional que contém todas as texturas, imagens e scripts [OGRE](http://wiki.ogre3d.org/Basic+Ogre+Framework) para o modelo. As imagens de textura devem ser colocadas no subdiretório textures e nos arquivos de script [OGRE](http://wiki.ogre3d.org/Basic+Ogre+Framework) no diretório de scripts.
### Database Config
Este é o arquivo database.config na raiz do banco do modelo. Este arquivo contém informações de licença para os modelos, um nome para o banco de dados e uma lista de todos os modelos válidos.

Nota: O arquivo `database.config` é necessário apenas para repositórios online. Um diretório cheio de modelos no seu computador local não precisa de um arquivo `database.config`.

O formato deste `database.config` é:
```xml
<?xml version='1.0'?>
<database>
  <name>nome_do_modelo_usado</name>
  <license>Creative Commons Attribution 3.0 Unported</license>
  <models>
    <uri>file://diretorio_do_modelo</uri>
  </models>
</database>
```
- `<name>`: O nome do modelo. Isso é usado pela interface gráfica do GAZEBO e outras ferramentas.
- `<license>`: Tipo de licença do modelo no repositório. O Gazebo recomenda explícitamente a licença [Creative Commons Attribution 3.0 Unported](https://creativecommons.org/licenses/by/3.0/).
- `<models>`: Uma listagem de todos os URIs(endereços) do modelos usados
   - `<uri>`: The URI for a model, this should be `file://diretorio_do_modelo`

### Configuração do modelo
Cada modelo deve ter um arquivo `model.config` no diretório raiz do modelo que contém informações meta sobre o modelo.

O formato deste `model.config` é:

```xml
<?xml version="1.0"?>

<model>
  <name>Plataforma_47</name>
  <version>1.0</version>
  <sdf version='1.5'>model.sdf</sdf>

  <author>
    <name>Seu nome</name>
    <email>nome@seu.email</email>
  </author>

  <description>
   Uma descrição do modelo
  </description>
</model>
```

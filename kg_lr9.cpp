#include <osg/Geode>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>

int main()
{
// Создать объект viewer
osgViewer::Viewer* viewer = new osgViewer::Viewer();

//Создать граф для объектов
osg::Group* root = new osg::Group();

// Создать узел
osg::Node* cessna = osgDB::readNodeFile("cessna.osg");
root->addChild(cessna);

//отправить данные сцены в viewer
viewer->setSceneData(root);

//создать окно
viewer->realize();

//Начать отрисовку
viewer->run();

return 0;
}

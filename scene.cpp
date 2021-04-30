#include "scene.h"
#include "widget.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>



Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    setUpPillarTimer();
    koniec = 1;

}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(":/zasoby/birdup.png"));
    addItem(bird);
}


void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout, [=](){
        PillarItem *pillarItem = new PillarItem();
        connect(pillarItem,&PillarItem::collideFail,[=](){
            pillarTimer->stop();
            freezeBirdAndPillars();
        });
        addItem(pillarItem);
    });

    pillarTimer->start(1000);
}

void Scene::freezeBirdAndPillars()
{
    bird->freeze();
    QList<QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        PillarItem *pillar = dynamic_cast<PillarItem *>(item);
        if(pillar){
            pillar->freezeP();
        }
    }
    koniec = 2;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(koniec != 2){
        if(event->key() == Qt::Key_Space){
            bird->shootUp();
        }
        QGraphicsScene::keyPressEvent(event);
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(koniec != 2){
        if(event->button() == Qt::LeftButton){
            bird->shootUp();
        }
        QGraphicsScene::mousePressEvent(event);
    }
}

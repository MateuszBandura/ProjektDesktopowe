#include "pillaritem.h"
#include "birditem.h"
#include <QRandomGenerator>
#include <QGraphicsScene>

PillarItem::PillarItem() :
    topPillar(new QGraphicsPixmapItem(QPixmap(":/zasoby/pillar.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/zasoby/pillar.png")))
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2, topPillar->boundingRect().height() +60));

    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2, 60));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this,"x",this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260 + xRandomizer);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);
    xAnimation->start();

    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        scene()->removeItem(this);
        delete this;
    });



}

PillarItem::~PillarItem()
{

}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::freezeP()
{
    xAnimation->stop();
}

void PillarItem::setX(qreal x)
{
    m_x = x;
    if(collidesWithBird()){
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x,yPos));
}

bool PillarItem::collidesWithBird()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());

    foreach(QGraphicsItem *item, collidingItems)
    {
        BirdItem *birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem){
            return true;
        }
    }
    return false;
}

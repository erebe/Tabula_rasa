#ifndef LIAISONPICTO_HPP
#define LIAISONPICTO_HPP
#include <QGraphicsItem>

class AncreItem;

class LiaisonItem : public QGraphicsPathItem
{
public:
        enum { Type = UserType + 8 };
    LiaisonItem( AncreItem* parent = 0, AncreItem* enfant = 0 );
    virtual int type() const { return Type; }

    void updatePath();

protected:
    AncreItem* parent_;
    AncreItem* child_;
    QPainterPath path_;
};

#endif // LIAISONPICTO_HPP

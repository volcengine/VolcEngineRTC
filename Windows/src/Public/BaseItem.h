#ifndef BASEITEM_H
#define BASEITEM_H

class BaseItem{
public:
    BaseItem(){

    }

    virtual ~BaseItem(){

    }

    virtual void showItem() = 0;
    virtual void hideItem() = 0;
};


#endif // BASEITEM_H

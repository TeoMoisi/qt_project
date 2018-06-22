#ifndef COAT_MODEL_H
#define COAT_MODEL_H
#include <QAbstractItemModel>
#include "controller.h"


class coat_model: public QAbstractItemModel
{

private:
    Controller &_ctrl;
public:
    coat_model(Controller &ctrl): _ctrl(ctrl) {};
    ~coat_model();
};

#endif // COAT_MODEL_H

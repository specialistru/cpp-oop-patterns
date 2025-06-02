#pragma once
#include "AbstractGOFactory.h"

class BWGOFactory : public AbstractGOFactory {
public:
    BWPoint* createPoint() override;
    Circle* createCircle() override;
};

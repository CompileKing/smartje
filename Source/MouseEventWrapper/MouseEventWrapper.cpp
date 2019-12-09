/*
  ==============================================================================

    MouseEventWrapper.cpp
    Created: 9 Dec 2019 12:03:32pm
    Author:  Sem Shimla

  ==============================================================================
*/

#include "MouseEventWrapper.h"

MouseEventWrapper::MouseEventWrapper(const MouseEvent& e, const MouseEvent* last)
: mods(e.mods)
, _e(e)
, _last(last)
, _iterNum(0)
, _totalNumIter(1) {
    if (!last)
        return;

    _totalNumIter = getTotalNumIter();
}

int MouseEventWrapper::getDeltaX() const {
    return _last ? _e.getDistanceFromDragStartX() - _last->getDistanceFromDragStartX() : 0;
}

int MouseEventWrapper::getDeltaY() const {
    return _last ? _e.getDistanceFromDragStartY() - _last->getDistanceFromDragStartY() : 0;
}

int MouseEventWrapper::getStepSize() const {
    return 1;
}

int MouseEventWrapper::getTotalNumIter() const {
    const double delta = getDeltaX();
    const double stepSize = getStepSize();
    return static_cast<int>(abs(delta / stepSize));
}

int MouseEventWrapper::getOffsetX() const {
    const double delta = getDeltaX();
    const double total = jmax(1, getTotalNumIter());
    return static_cast<int>(delta / total * (_iterNum + 1));
}

int MouseEventWrapper::getOffsetY() const {
    const double delta = getDeltaY();
    const double total = jmax(1, getTotalNumIter());
    return static_cast<int>(delta / total * (_iterNum + 1));
}

Point<int> MouseEventWrapper::getMouseDownPosition() const {
    return _e.getMouseDownPosition();
}

int MouseEventWrapper::getDistanceFromDragStartX() const {
    return _last ? _last->getDistanceFromDragStartX() + getOffsetX() : _e.getDistanceFromDragStartX();
}

Point<int> MouseEventWrapper::getOffsetFromDragStart() const {
    auto p = _e.getOffsetFromDragStart();
    p.addXY(getOffsetX(), getOffsetY());
    return p;
}

int MouseEventWrapper::getMouseDownY() const {
    return _e.getMouseDownY();
}

MouseEventWrapper::operator bool() const {
    return _iterNum < _totalNumIter;
}

void MouseEventWrapper::operator++(int) {
    _iterNum++;
}

/*
    Copyright (c) 2018 James McLean

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#ifndef CONTROL_WRAPPER_HPP
#define CONTROL_WRAPPER_HPP

#include <iostream>
#include <memory>

#include <QObject>
#include <QWidget>

#include <vcap.h>

class ControlWrapper : public QObject
{
    Q_OBJECT

public:
    explicit ControlWrapper(vcap_device* vd, vcap_control_info info);
    virtual ~ControlWrapper() {}

    virtual void check() = 0;
    virtual void update() = 0;

    virtual QWidget* widget() = 0;

signals:
    void changed();

public slots:
    virtual void setValue(int value);

protected:
    vcap_device* vd_;
    vcap_control_info info_;
};

#endif // CONTROLWRAPPER_HPP

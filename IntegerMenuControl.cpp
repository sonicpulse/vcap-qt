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

#include "IntegerMenuControl.hpp"
#include "Iterator.hpp"

#include <QDebug>
#include "Utils.hpp"

IntegerMenuControl::IntegerMenuControl(vcap_device *vd, vcap_control_info info) : ControlWrapper(vd, info)
{
    vcap_menu_item item;
    IteratorPtr itr(vcap_menu_iterator(vd, info.id));

    while (vcap_next_menu_item(itr.get(), &item))
    {
        comboBox_.addItem(QString::number(item.label.num));
    }

    if (vcap_iterator_error(itr.get()))
        throw std::runtime_error(vcap_get_error(vd_));

    update();

    connect(&comboBox_, SIGNAL(currentIndexChanged(int)), this, SLOT(setValue(int)));
}

void IntegerMenuControl::check()
{
    vcap_control_status status;

    if (vcap_get_control_status(vd_, info_.id, &status) != VCAP_OK)
        throw std::runtime_error(vcap_get_error(vd_));

    bool enabled = comboBox_.isEnabled();

    if (!status.read_only && !status.write_only && !status.disabled && !status.inactive)
    {
        if (!enabled)
            update();

        comboBox_.setDisabled(false);
    }
    else
    {
        comboBox_.setDisabled(true);
    }
}

void IntegerMenuControl::update()
{
    int32_t value;

    if (vcap_get_control(vd_, info_.id, &value) != VCAP_OK)
        throw std::runtime_error(vcap_get_error(vd_));

    comboBox_.blockSignals(true);
    comboBox_.setCurrentIndex(value);
    comboBox_.blockSignals(false);
}

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

#include "BooleanControl.hpp"

BooleanControl::BooleanControl(vcap_device* vd, vcap_control_info info) : ControlWrapper(vd, info)
{
    update();
    connect(&checkBox_, SIGNAL(clicked(bool)), this, SLOT(setValue(bool)));
}

void BooleanControl::setValue(bool value)
{
    if (vcap_set_control(vd_, info_.id, value) != VCAP_OK)
        throw std::runtime_error(vcap_get_error(vd_));
    else
        emit changed();
}

void BooleanControl::check()
{
    vcap_control_status status;

    if (vcap_get_control_status(vd_, info_.id, &status) != VCAP_OK)
        throw std::runtime_error(vcap_get_error(vd_));

    bool enabled = checkBox_.isEnabled();

    if (!status.read_only && !status.write_only && !status.disabled && !status.inactive)
    {
        if (!enabled)
            update();

        checkBox_.setDisabled(false);
    } else {
        checkBox_.setDisabled(true);
    }
}

void BooleanControl::update()
{
    int32_t value;

    if (vcap_get_control(vd_, info_.id, &value) != VCAP_OK)
        throw std::runtime_error(vcap_get_error(vd_));

    checkBox_.blockSignals(true);
    checkBox_.setChecked(!!value);
    checkBox_.blockSignals(false);
}

// license:BSD-3-Clause
// copyright-holders:Carl
#ifndef MAME_MACHINE_M24_KBD_H
#define MAME_MACHINE_M24_KBD_H

#pragma once

#include "cpu/mcs48/mcs48.h"


class m24_keyboard_device :  public device_t
{
public:
	m24_keyboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	auto out_data_handler() { return m_out_data.bind(); }

	DECLARE_WRITE_LINE_MEMBER(clock_w);
	DECLARE_WRITE_LINE_MEMBER(data_w);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param) override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

private:
	required_ioport_array<16> m_rows;
	required_ioport m_mousebtn;
	uint8_t m_p1;
	bool m_keypress, m_kbcdata;
	devcb_write_line m_out_data;
	required_device<i8049_device> m_mcu;
	emu_timer *m_reset_timer;

	void bus_w(uint8_t data);
	uint8_t p1_r();
	void p1_w(uint8_t data);
	uint8_t p2_r();
	DECLARE_READ_LINE_MEMBER(t0_r);
	DECLARE_READ_LINE_MEMBER(t1_r);
};

DECLARE_DEVICE_TYPE(M24_KEYBOARD, m24_keyboard_device)

#endif // MAME_MACHINE_M24_KBD_H

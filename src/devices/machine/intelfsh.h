// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*
    Intel Flash ROM emulation
*/

#ifndef MAME_MACHINE_INTELFSH_H
#define MAME_MACHINE_INTELFSH_H

#pragma once

class intelfsh_device : public device_t,
						public device_nvram_interface
{
public:
	enum
	{
		// 8-bit variants
		FLASH_INTEL_28F016S5 = 0x0800,
		FLASH_FUJITSU_29F160TE,
		FLASH_FUJITSU_29F016A,
		FLASH_FUJITSU_29DL164BD,
		FLASH_FUJITSU_29LV002TC,
		FLASH_FUJITSU_29LV800B,
		FLASH_ATMEL_29C010,
		FLASH_AMD_29F010,
		FLASH_AMD_29F040,
		FLASH_AMD_29F080,
		FLASH_AMD_29F400T,
		FLASH_AMD_29F800T,
		FLASH_AMD_29F800B_16BIT,
		FLASH_AMD_29LV200T,
		FLASH_CAT28F020,
		FLASH_SHARP_LH28F016S,
		FLASH_SHARP_LH28F016S_16BIT,
		FLASH_INTEL_E28F008SA,
		FLASH_MACRONIX_29L001MC,
		FLASH_MACRONIX_29LV160TMC,
		FLASH_PANASONIC_MN63F805MNP,
		FLASH_SANYO_LE26FV10N1TS,
		FLASH_SST_28SF040,
		FLASH_SST_39SF040,
		FLASH_SST_39VF020,
		FLASH_SST_49LF020,
		FLASH_TMS_29F040,

		// 16-bit variants
		FLASH_SHARP_LH28F400 = 0x1000,
		FLASH_INTEL_E28F400B,
		FLASH_INTEL_TE28F160,
		FLASH_SHARP_LH28F160S3,
		FLASH_INTEL_TE28F320,
		FLASH_SHARP_LH28F320BF,
		FLASH_INTEL_28F320J3D,
		FLASH_SPANSION_S29GL064S,
		FLASH_INTEL_28F320J5,
		FLASH_SST_39VF400A,
		FLASH_ATMEL_49F4096
	};

	uint8_t *base() { return &m_data[0]; }

protected:
	// construction/destruction
	intelfsh_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t variant);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param) override;

	// device_nvram_interface overrides
	virtual void nvram_default() override;
	virtual void nvram_read(emu_file &file) override;
	virtual void nvram_write(emu_file &file) override;

	// derived helpers
	uint32_t read_full(uint32_t offset);
	void write_full(uint32_t offset, uint32_t data);

	optional_memory_region   m_region;

	// configuration state
	uint32_t                   m_type;
	int32_t                    m_size;
	uint8_t                    m_bits;
	uint32_t                   m_addrmask;
	uint16_t                   m_device_id;
	uint8_t                    m_maker_id;
	bool                     m_sector_is_4k;
	bool                     m_sector_is_16k;
	bool                     m_top_boot_sector;
	bool                     m_bot_boot_sector;
	uint8_t                    m_page_size;

	// internal state
	std::unique_ptr<uint8_t[]> m_data;
	uint8_t                    m_status;
	int32_t                    m_erase_sector;
	int32_t                    m_flash_mode;
	bool                     m_flash_master_lock;
	emu_timer *              m_timer;
	int32_t                    m_bank;
	uint8_t                    m_byte_count;
};


// ======================> intelfsh8_device

class intelfsh8_device : public intelfsh_device
{
public:
	// public interface
	uint8_t read(offs_t offset) { return read_full(offset); }
	void write(offs_t offset, uint8_t data) { write_full(offset, data); }

	uint8_t read_raw(offs_t offset) { return m_data[offset]; }
	void write_raw(offs_t offset, uint8_t data) { m_data[offset] = data; }

protected:
	// construction/destruction
	intelfsh8_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t variant);
};


// ======================> intelfsh16_device

class intelfsh16_device : public intelfsh_device
{
public:
	// public interface
	uint16_t read(offs_t offset) { return read_full(offset); }
	void write(offs_t offset, uint16_t data) { write_full(offset, data); }

	uint16_t read_raw(offs_t offset) { return m_data[offset*2] | (m_data[offset*2+1] << 8); }
	void write_raw(offs_t offset, uint16_t data) { m_data[offset*2] = data; m_data[offset*2+1] = data >> 8; }

protected:
	// construction/destruction
	intelfsh16_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t variant);
};


// ======================> trivial variants

// 8-bit variants
class intel_28f016s5_device : public intelfsh8_device
{
public:
	intel_28f016s5_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class fujitsu_29f160te_device : public intelfsh8_device
{
public:
	fujitsu_29f160te_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class fujitsu_29f016a_device : public intelfsh8_device
{
public:
	fujitsu_29f016a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class fujitsu_29dl164bd_device : public intelfsh8_device
{
public:
	fujitsu_29dl164bd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class fujitsu_29lv002tc_device : public intelfsh8_device
{
public:
	fujitsu_29lv002tc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class fujitsu_29lv800b_device : public intelfsh16_device
{
public:
	fujitsu_29lv800b_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class atmel_29c010_device : public intelfsh8_device
{
public:
	atmel_29c010_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class amd_29f010_device : public intelfsh8_device
{
public:
	amd_29f010_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class amd_29f040_device : public intelfsh8_device
{
public:
	amd_29f040_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class amd_29f080_device : public intelfsh8_device
{
public:
	amd_29f080_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class amd_29f400t_device : public intelfsh8_device
{
public:
	amd_29f400t_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class amd_29f800t_device : public intelfsh8_device
{
public:
	amd_29f800t_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class amd_29f800b_16bit_device : public intelfsh16_device
{
public:
	amd_29f800b_16bit_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class amd_29lv200t_device : public intelfsh8_device
{
public:
	amd_29lv200t_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sharp_lh28f016s_device : public intelfsh8_device
{
public:
	sharp_lh28f016s_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sharp_lh28f016s_16bit_device : public intelfsh16_device
{
public:
	sharp_lh28f016s_16bit_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class intel_e28f008sa_device : public intelfsh8_device
{
public:
	intel_e28f008sa_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class macronix_29l001mc_device : public intelfsh8_device
{
public:
	macronix_29l001mc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class macronix_29lv160tmc_device : public intelfsh8_device
{
public:
	macronix_29lv160tmc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class panasonic_mn63f805mnp_device : public intelfsh8_device
{
public:
	panasonic_mn63f805mnp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sanyo_le26fv10n1ts_device : public intelfsh8_device
{
public:
	sanyo_le26fv10n1ts_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sst_28sf040_device : public intelfsh8_device
{
public:
	sst_28sf040_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sst_39sf040_device : public intelfsh8_device
{
public:
	sst_39sf040_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sst_39vf020_device : public intelfsh8_device
{
public:
	sst_39vf020_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sst_49lf020_device : public intelfsh8_device
{
public:
	sst_49lf020_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class tms_29f040_device : public intelfsh8_device
{
public:
	tms_29f040_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

// 16-bit variants
class sharp_lh28f400_device : public intelfsh16_device
{
public:
	sharp_lh28f400_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class intel_te28f160_device : public intelfsh16_device
{
public:
	intel_te28f160_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sharp_lh28f160s3_device : public intelfsh16_device
{
public:
	sharp_lh28f160s3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class intel_te28f320_device : public intelfsh16_device
{
public:
	intel_te28f320_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class spansion_s29gl064s_device : public intelfsh16_device
{
public:
	spansion_s29gl064s_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class intel_e28f400b_device : public intelfsh16_device
{
public:
	intel_e28f400b_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sharp_lh28f320bf_device : public intelfsh16_device
{
public:
	sharp_lh28f320bf_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class intel_28f320j3d_device : public intelfsh16_device
{
public:
	intel_28f320j3d_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class intel_28f320j5_device : public intelfsh16_device
{
public:
	intel_28f320j5_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class sst_39vf400a_device : public intelfsh16_device
{
public:
	sst_39vf400a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class atmel_49f4096_device : public intelfsh16_device
{
public:
	atmel_49f4096_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};

class cat28f020_device : public intelfsh8_device
{
public:
	cat28f020_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);
};


// device type definition
DECLARE_DEVICE_TYPE(INTEL_28F016S5,        intel_28f016s5_device)
DECLARE_DEVICE_TYPE(SHARP_LH28F016S,       sharp_lh28f016s_device)
DECLARE_DEVICE_TYPE(SHARP_LH28F016S_16BIT, sharp_lh28f016s_16bit_device)
DECLARE_DEVICE_TYPE(ATMEL_29C010,          atmel_29c010_device)
DECLARE_DEVICE_TYPE(AMD_29F010,            amd_29f010_device)
DECLARE_DEVICE_TYPE(AMD_29F040,            amd_29f040_device)
DECLARE_DEVICE_TYPE(AMD_29F080,            amd_29f080_device)
DECLARE_DEVICE_TYPE(AMD_29F400T,           amd_29f400t_device)
DECLARE_DEVICE_TYPE(AMD_29F800T,           amd_29f800t_device)
DECLARE_DEVICE_TYPE(AMD_29F800B_16BIT,     amd_29f800b_16bit_device)
DECLARE_DEVICE_TYPE(AMD_29LV200T,          amd_29lv200t_device)
DECLARE_DEVICE_TYPE(FUJITSU_29F160TE,      fujitsu_29f160te_device)
DECLARE_DEVICE_TYPE(FUJITSU_29F016A,       fujitsu_29f016a_device)
DECLARE_DEVICE_TYPE(FUJITSU_29DL164BD,     fujitsu_29dl164bd_device)
DECLARE_DEVICE_TYPE(FUJITSU_29LV002TC,     fujitsu_29lv002tc_device)
DECLARE_DEVICE_TYPE(FUJITSU_29LV800B,      fujitsu_29lv800b_device)
DECLARE_DEVICE_TYPE(INTEL_E28F400B,        intel_e28f400b_device)
DECLARE_DEVICE_TYPE(MACRONIX_29L001MC,     macronix_29l001mc_device)
DECLARE_DEVICE_TYPE(MACRONIX_29LV160TMC,   macronix_29lv160tmc_device)
DECLARE_DEVICE_TYPE(TMS_29F040,            tms_29f040_device)

DECLARE_DEVICE_TYPE(PANASONIC_MN63F805MNP, panasonic_mn63f805mnp_device)
DECLARE_DEVICE_TYPE(SANYO_LE26FV10N1TS,    sanyo_le26fv10n1ts_device)
DECLARE_DEVICE_TYPE(SST_28SF040,           sst_28sf040_device)
DECLARE_DEVICE_TYPE(SST_39SF040,           sst_39sf040_device)
DECLARE_DEVICE_TYPE(SST_39VF020,           sst_39vf020_device)
DECLARE_DEVICE_TYPE(SST_49LF020,           sst_49lf020_device)

DECLARE_DEVICE_TYPE(SHARP_LH28F400,        sharp_lh28f400_device)
DECLARE_DEVICE_TYPE(INTEL_E28F008SA,       intel_e28f008sa_device)
DECLARE_DEVICE_TYPE(INTEL_TE28F160,        intel_te28f160_device)
DECLARE_DEVICE_TYPE(SHARP_LH28F160S3,      sharp_lh28f160s3_device)
DECLARE_DEVICE_TYPE(INTEL_TE28F320,        intel_te28f320_device)
DECLARE_DEVICE_TYPE(SPANSION_S29GL064S,    spansion_s29gl064s_device)
DECLARE_DEVICE_TYPE(SHARP_LH28F320BF,      sharp_lh28f320bf_device)
DECLARE_DEVICE_TYPE(INTEL_28F320J3D,       intel_28f320j3d_device)
DECLARE_DEVICE_TYPE(INTEL_28F320J5,        intel_28f320j5_device)
DECLARE_DEVICE_TYPE(SST_39VF400A,          sst_39vf400a_device)
DECLARE_DEVICE_TYPE(ATMEL_49F4096,         atmel_49f4096_device)
DECLARE_DEVICE_TYPE(CAT28F020,             cat28f020_device)

#endif // MAME_MACHINE_INTELFSH_H

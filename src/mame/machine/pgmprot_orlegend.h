// license:BSD-3-Clause
// copyright-holders:Olivier Galibert, iq_132
/* for machine/pgmprot_orlegend.c type games */

class pgm_asic3_state : public pgm_state
{
public:
	pgm_asic3_state(const machine_config &mconfig, device_type type, const char *tag)
		: pgm_state(mconfig, type, tag) {
	}

	void init_orlegend();
//缘来是你
//========== mamep ============>>>
	void init_orld112c();
	void init_orld111c();
	void init_orld111t();
	void init_orlegendk();    	

	void pgm_asic3_reset();	
//=============================>>>	
	void pgm_asic3(machine_config &config);

private:
	// ASIC 3 (oriental legends protection)
	u8         m_asic3_reg = 0;
	u8         m_asic3_latch[3]{};
	u8         m_asic3_x = 0;
	u16        m_asic3_hilo = 0;
	u16        m_asic3_hold = 0;

	void asic3_compute_hold(int,int);
	u16 pgm_asic3_r();
	void pgm_asic3_w(offs_t offset, u16 data);
};

INPUT_PORTS_EXTERN( orlegend );
INPUT_PORTS_EXTERN( orlegendt );
INPUT_PORTS_EXTERN( orlegendk );
//缘来是你
//========== mamep ============>>>
INPUT_PORTS_EXTERN( orld112c );
INPUT_PORTS_EXTERN( orld111c );
INPUT_PORTS_EXTERN( orld111t );
//=============================>>>
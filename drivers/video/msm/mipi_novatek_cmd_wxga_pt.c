/*
 * This software is contributed or developed by KYOCERA Corporation.
 * (C) 2012 KYOCERA Corporation
 *
 * drivers/video/msm/mipi_novatek_cmd_wxga_pt.c
 *
 * Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
*/
#include "msm_fb.h"
#include "mipi_dsi.h"
#include "mipi_novatek_wxga.h"

static struct msm_panel_info pinfo;

static struct mipi_dsi_phy_ctrl dsi_cmd_mode_phy_db = {
  /* 720*1024, RGB888, 3 Lane 60 fps command mode */
  /* regulator */
  {0x03, 0x0a, 0x04, 0x00, 0x20},
  /* timing */
  {0x79, 0x25, 0x12, 0x00, 0x36, 0x40, 0x16, 0x29, 0x20, 0x03, 0x04, 0xa0},
  /* phy ctrl */
  {0x5f, 0x00, 0x00, 0x10},
  /* strength */
  {0xff, 0x00, 0x06, 0x00},
  /* pll control */
  {0x00, 0x7f, 0x01, 0x1a, 0x00, 0x50, 0x48, 0x63, 0x41, 0x0f, 0x01,
   0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};

static int __init mipi_command_novatek_wxga_pt_init(void)
{
	int ret;

	if (msm_fb_detect_client("mipi_cmd_novatek_wxga")) {
		return 0;
	}

	pinfo.xres = 720;
	pinfo.yres = 1280;
	pinfo.type = MIPI_CMD_PANEL;
	pinfo.pdest = DISPLAY_1;
	pinfo.wait_cycle = 0;
	pinfo.bpp = 24;
	pinfo.lcdc.h_back_porch = 50;
	pinfo.lcdc.h_front_porch = 50;
	pinfo.lcdc.h_pulse_width = 20;
	pinfo.lcdc.v_back_porch = 11;
	pinfo.lcdc.v_front_porch = 10;
	pinfo.lcdc.v_pulse_width = 5;
	pinfo.lcdc.border_clr = 0;	/* blk */
	pinfo.lcdc.underflow_clr = 0xff;	/* blue */
	pinfo.lcdc.hsync_skew = 0;
	pinfo.bl_max = 255;
	pinfo.bl_min = 1;
	pinfo.fb_num = 2;
	pinfo.clk_rate = 454000000;

	pinfo.mipi.mode = DSI_CMD_MODE;
	pinfo.mipi.dst_format = DSI_CMD_DST_FORMAT_RGB888;
	pinfo.mipi.vc = 0;
	pinfo.mipi.data_lane0 = TRUE;
	pinfo.mipi.data_lane1 = TRUE;
	pinfo.mipi.data_lane2 = TRUE;
	pinfo.mipi.t_clk_post = 0x22;
	pinfo.mipi.t_clk_pre = 0x3f;
	pinfo.mipi.stream = 0;	/* dma_p */
	pinfo.mipi.mdp_trigger = DSI_CMD_TRIGGER_NONE;
	pinfo.mipi.dma_trigger = DSI_CMD_TRIGGER_SW;
	pinfo.mipi.te_sel = 1; /* TE from vsycn gpio */
	pinfo.mipi.interleave_max = 1;
	pinfo.mipi.insert_dcs_cmd = TRUE;
	pinfo.mipi.wr_mem_continue = 0x3c;
	pinfo.mipi.wr_mem_start = 0x2c;
	pinfo.mipi.dsi_phy_db = &dsi_cmd_mode_phy_db;
	pinfo.mipi.esc_byte_ratio = 2;
	pinfo.mipi.frame_rate = 60;
	pinfo.mipi.crc_check = 1;

	pinfo.lcd.refx100 = 6000; /* adjust refx100 to prevent tearing */
	pinfo.lcd.v_back_porch = 8;
	pinfo.lcd.v_front_porch = 8;
	pinfo.lcd.v_pulse_width = 355;

    pinfo.lcd.vsync_enable = TRUE;
	pinfo.lcd.hw_vsync_mode = TRUE;

  ret = mipi_novatek_wxga_device_register(&pinfo, MIPI_DSI_PRIM,
						MIPI_DSI_PANEL_WXGA);
	if (ret) {
		pr_err("%s: failed to register device!\n", __func__);
	}

	return ret;
}

module_init(mipi_command_novatek_wxga_pt_init);

/*
 *  (C) Copyright 2010,2011
 *  NVIDIA Corporation <www.nvidia.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __TEGRA11X_COMMON_H
#define __TEGRA11X_COMMON_H
#include <asm/sizes.h>

/*
 * QUOTE(m) will evaluate to a string version of the value of the macro m
 * passed in.  The extra level of indirection here is to first evaluate the
 * macro m before applying the quoting operator.
 */
#define QUOTE_(m)	#m
#define QUOTE(m)	QUOTE_(m)

/* FDT support */
#define CONFIG_OF_LIBFDT	/* Device tree support */
#define CONFIG_OF_CONTROL	/* Use the device tree to set up U-Boot */

/* Embed the device tree in U-Boot, if not otherwise handled */
#ifndef CONFIG_OF_SEPARATE
#define CONFIG_OF_EMBED
#endif

/*
 * High Level Configuration Options
 */
#define CONFIG_ARMCORTEXA15		/* This is an ARM V7 CPU core */
#define CONFIG_TEGRA11X			/* in a NVidia Tegra11x core */
#define CONFIG_MACH_TEGRA_GENERIC	/* which is a Tegra generic machine */
#define CONFIG_BOOTSTAGE		/* Record boot time */
#define CONFIG_BOOTSTAGE_REPORT		/* Print a boot time report */
#define CONFIG_ARCH_CPU_INIT		/* Fire up the A15 core */
#define CONFIG_ALIGN_LCD_TO_SECTION	/* Align LCD to 1MB boundary */
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_MISC_INIT_R		/* misc init */

#include <asm/arch/tegra.h>		/* get chip and board defs */

#define CACHE_LINE_SIZE			32

/*
 * Display CPU and Board information
 */
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_SKIP_LOWLEVEL_INIT

#define CONFIG_CMDLINE_TAG		/* enable passing of ATAGs */
#define CONFIG_INITRD_TAG		/* enable initrd ATAG */

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(4 << 20)	/* 4MB  */

/*
 * PllX Configuration
 */
#define CONFIG_SYS_CPU_OSC_FREQUENCY	2000000	/* Set CPU clock to 2GHz */

/*
 * NS16550 Configuration
 */
#define CONFIG_SERIAL_MULTI
#define CONFIG_NS16550_BUFFER_READS
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)

#ifdef CONFIG_OF_CONTROL
#define CONFIG_COMPAT_STRING		"nvidia,tegra11x"
#else
#if defined(CONFIG_SYS_PLLP_BASE_IS_408MHZ)
#define V_NS16550_CLK			408000000	/* 408MHz PLLP_OUT0 */
#else
#define V_NS16550_CLK			216000000	/* 216MHZ PLLP_OUT0 */
#endif
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK

/*
 * select serial console configuration
 */
#define CONFIG_CONS_INDEX	1
#endif /* CONFIG_OF_CONTROL ^^^^^ not defined */

#define CONFIG_ENV_SIZE         SZ_4K

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600,\
					115200}
#if t11x_port
#else
/*
 * USB Host.
 */
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_TEGRA

/* Tegra requires USB buffers to be aligned to a 32-byte boundary */
#define CONFIG_USB_EHCI_DATA_ALIGN	32

/*
 * This parameter affects a TXFILLTUNING field that controls how much data is
 * sent to the latency fifo before it is sent to the wire. Without this
 * parameter, the default (2) causes occasional Data Buffer Errors in OUT
 * packets depending on the buffer address and size.
 */
#define CONFIG_USB_EHCI_TXFIFO_THRESH	10

#define CONFIG_EHCI_IS_TDI
#define CONFIG_EHCI_DCACHE
#define CONFIG_USB_STORAGE
#define CONFIG_USB_STOR_NO_RETRY

#define CONFIG_CMD_USB		/* USB Host support		*/

/* partition types and file systems we want */
#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION
#define CONFIG_CMD_EXT2

/* support USB ethernet adapters */
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#endif
/* include default commands */
#include <config_cmd_default.h>

/* remove unused commands */
#undef CONFIG_CMD_FLASH		/* flinfo, erase, protect */
#undef CONFIG_CMD_FPGA		/* FPGA configuration support */
#undef CONFIG_CMD_IMI
#undef CONFIG_CMD_IMLS
#undef CONFIG_CMD_NFS		/* NFS support */

#define CONFIG_CMD_CACHE
#define CONFIG_CMD_TIME

/*
 * Ethernet support
 */
#define CONFIG_CMD_NET
#define CONFIG_NET_MULTI
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP

/*
 * BOOTP / TFTP options
 */
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_TFTP_TSIZE
#define CONFIG_TFTP_SPEED

#define CONFIG_IPADDR		10.0.0.2
#define CONFIG_SERVERIP		10.0.0.1
#define CONFIG_BOOTFILE		vmlinux.uimg

/*
 * We decorate the nfsroot name so that multiple users / boards can easily
 * share an NFS server:
 *   user - username, e.g. 'frank'
 *   board - board, e.g. 'seaboard'
 *   dhcpserial - serial number, e.g. '1234'
 */
#define CONFIG_ROOTPATH	"/export/nfsroot-${user}-${board}-${dhcpserial#}"
#define CONFIG_TFTPPATH	"/tftpboot/uImage-${user}-${board}-${dhcpserial#}"

/*
 * NET retry control
 * outer loop: "yes", "no", "once", or a counter (in form of a string)
 * inner loop: a counter
 */
#define CONFIG_NET_RETRY_CONTROL	"1"	/* outer loop */
#define CONFIG_NET_RETRY_COUNT		5	/* inner loop */

/* turn on command-line edit/hist/auto */
#define CONFIG_CMDLINE_EDITING
#define CONFIG_COMMAND_HISTORY
#define CONFIG_AUTOCOMPLETE

#define CONFIG_SYS_NO_FLASH

#ifdef CONFIG_TEGRA2_LP0
#define TEGRA_LP0_ADDR			0x9C406000
#define TEGRA_LP0_SIZE			SZ_8K
#define TEGRA_LP0_VEC \
	"lp0_vec=" QUOTE(TEGRA_LP0_SIZE) "@" QUOTE(TEGRA_LP0_ADDR) " "
#else
#define TEGRA_LP0_VEC
#endif

/* Environment information */
#define CONFIG_EXTRA_ENV_SETTINGS_COMMON \
	CONFIG_STD_DEVICES_SETTINGS \
	"console=ttyS0,115200n8\0" \
	"smpflag=smp\0" \
	"user=user\0" \
	"dhcpserial#=1\0" \
	"tftpserverip=172.22.72.144\0" \
	"nfsserverip=172.22.72.144\0" \
	"netretry="CONFIG_NET_RETRY_CONTROL"\0" \
	"extra_bootargs=" \
		"usbcore.old_scheme_first=1 " \
		"core_edp_mv=1300 " \
		CONFIG_EXTRA_BOOTARGS \
	"videospec=tegrafb\0" \
	"lp0_args=" TEGRA_LP0_VEC "\0" \
	"mmcdev=" TEGRA_MMC_DEFAULT_DEVICE "\0" \
	"dev_extras=\0" \
	\
	"regen_all="\
		"setenv common_bootargs console=${console} " \
		"${lp0_args} video=${videospec} ${platform_extras} " \
		"${dev_extras} noinitrd; " \
		"setenv bootargs ${common_bootargs} ${extra_bootargs} " \
		"${bootdev_bootargs}\0" \
	"regen_net_bootargs=setenv bootdev_bootargs " \
		"dev=/dev/nfs4 rw nfsroot=${nfsserverip}:${rootpath} " \
		"ip=dhcp; " \
		"run regen_all\0" \
	\
	"dhcp_setup=setenv tftppath " CONFIG_TFTPPATH "; " \
		"setenv rootpath " CONFIG_ROOTPATH "; " \
		"setenv autoload n; " \
		"run regen_net_bootargs\0" \
	"dhcp_boot=run dhcp_setup; " \
		"bootp; tftpboot ${loadaddr} ${tftpserverip}:${tftppath}; " \
		"bootm ${loadaddr}\0" \
	\
	"mmc_setup=setenv bootdev_bootargs " \
		"root=/dev/mmcblk${mmcdev}p3 rw rootwait; " \
		"run regen_all\0" \
	"mmc_boot=run mmc_setup; " \
		"mmc rescan ${mmcdev}; " \
		"ext2load mmc ${mmcdev}:3 ${loadaddr} /boot/${bootfile}; " \
		"bootm ${loadaddr}\0" \
	"mmc0_boot=setenv mmcdev 0; " \
		"run mmc_boot\0" \
	"mmc1_boot=setenv mmcdev 1; " \
		"run mmc_boot\0" \
	\
	"usb_setup=setenv bootdev_bootargs root=/dev/sda3 rw rootwait; " \
		"run regen_all\0" \
	"usb_boot=run usb_setup; " \
		"ext2load usb 0:3 ${loadaddr} /boot/${bootfile};" \
		"bootm ${loadaddr}\0" \

#define CONFIG_BOOTCOMMAND \
	"usb start; "\
	"if test ${ethact} != \"\"; then "\
		"run dhcp_boot ; " \
	"fi ; " \
	"run usb_boot ; " \
	\
	"run mmc1_boot ; " \
	"run mmc0_boot ; "

/* default location for kernel */
#define CONFIG_LOADADDR		0x80408000
#define CONFIG_BOOTDELAY	3		/* -1 to disable auto boot */

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER		/* use "hush" command parser */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_PROMPT		V_PROMPT
/*
 * Increasing the size of the IO buffer as default nfsargs size is more
 *  than 256 and so it is not possible to edit it
 */
#define CONFIG_SYS_CBSIZE		(256 * 2) /* Console I/O Buffer Size */
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		32	/* max number of command args */
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		(CONFIG_SYS_CBSIZE)

#define CONFIG_SYS_MEMTEST_START	(TEGRA_SDRC_CS0 + 0x600000)
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x100000)

#define CONFIG_SYS_LOAD_ADDR		(NV_PA_SDRAM_BASE + 0xA00800)
#define CONFIG_SYS_HZ			1000

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKBASE	(NV_PA_SDRAM_BASE + 0x2800000)	/* 40MB */
#define CONFIG_STACKSIZE	SZ_128K		/* 128K regular stack*/

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	1
#define PHYS_SDRAM_1		NV_PA_SDRAM_BASE

/* Below should be (NV_PA_SDRAM_BASE + 0x00E08000), but ld errors out */
#define CONFIG_SYS_TEXT_BASE	0x80108000
#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM_1

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_STACKBASE
#define CONFIG_SYS_INIT_RAM_SIZE	CONFIG_SYS_MALLOC_LEN
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
						CONFIG_SYS_INIT_RAM_SIZE - \
						GENERATED_GBL_DATA_SIZE)

/* kernel Device tree booting support */
#define CONFIG_FIT	1
#define CONFIG_CMD_IMI	1

/*
 * 32M is what it takes for u-boot to allocate enough room for the kernel
 * loader to inflate the kernel and keep a copy of the device tree handy.
 */
#define CONFIG_SYS_BOOTMAPSZ	SZ_32M

#endif /* __TEGRA11X_COMMON_H */

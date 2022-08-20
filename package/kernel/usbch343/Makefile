#
# Copyright (C) 2008-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=usbch343
PKG_RELEASE:=3
PKG_VERSION:=1.0
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk

define KernelPackage/$(PKG_NAME)
  CATEGORY := Liangfeng Package
  SUBMENU := Drivice Testing modules
  TITLE := liangfeng mydrv driver
  FILES := $(PKG_BUILD_DIR)/$(PKG_NAME).ko
  KCONFIG := 
  DEPENDS := +kmod-usb-core
  MAINTAINER := liangfeng(846399316@qq.com)
  AUTOLOAD := $(call AutoLoad,30,$(PKG_NAME),1)
endef

define KernelPackage/$(PKG_NAME)/description
  If you can't figure out what this program does, you're probably \
  brain-dead and need immediate medical attention.
endef

EXTRA_KCONFIG:= \
	CONFIG_MYDRV=m

EXTRA_CFLAGS:= \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=m,%,$(filter %=m,$(EXTRA_KCONFIG)))) \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=y,%,$(filter %=y,$(EXTRA_KCONFIG)))) \

MAKE_OPTS:= \
	$(KERNEL_MAKE_FLAGS) \
	SUBDIRS="$(PKG_BUILD_DIR)" \
	EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
	$(EXTRA_KCONFIG)

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules
endef

$(eval $(call KernelPackage,$(PKG_NAME)))



include $(TOPDIR)/rules.mk

PKG_NAME:=mqtt_nossl
PKG_VERSION:=1.0
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
define Package/mqtt_nossl
	SECTION:=base
	CATEGORY:=Utilities
	TITLE:=nossl mqtt test bylf 2021119
	DEPENDS:=+libmosquitto
endef

define Package/mqtt_nossl/description
	u can choose mqtt - nossl
	mqtt nossl.
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/mqtt_nossl/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mqtt_nossl $(1)/bin/
endef

$(eval $(call BuildPackage,mqtt_nossl))

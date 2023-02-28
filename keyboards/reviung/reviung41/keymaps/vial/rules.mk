VIA_ENABLE = yes
VIAL_ENABLE = yes

CONSOLE_ENABLE = no
LTO_ENABLE = yes

ifndef CONVERT_TO
	# Disable QMK Settings when using a ProMicro to reduce size:
	QMK_SETTINGS = no
else
	# Enable Mouse Keys when when not using a ProMicro as there will be space:
	MOUSEKEY_ENABLE = yes
endif
